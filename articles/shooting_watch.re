
= 連射測定ゲーム
この章は連射測定ゲーム（アプリ名称はshooting_watch）について書きます。

== ゲーム概要説明
連射測定ゲームは1980年代に少年・少女の間で流行した
@<href>{https://ja.wikipedia.org/wiki/%E3%82%B7%E3%83%A5%E3%82%A6%E3%82%A9%E3%83%83%E3%83%81,【シュウォッチ】}
を再現させるべくつくったゲームです。

本家のシュウォッチは連射測定に加え時計・ストップウォッチ機能が付いていますが今回のゲームは連射測定機能のみの実装です。


== プレイ画面
シェルに接続し、連射測定ゲームのアプリ名（shooting_watch）を入力します。
連射測定ゲームのバイナリはSDカードに格納しています。
つぎのコマンドでSDカードの中身を確認します。
shooting_watchが連射測定ゲームのコマンド名です。

//cmd{
nsh> ls /mnt/sd0
/mnt/sd0:
 System Volume Information/
 .fseventsd/
 BIN/
 AUDIO/
 PLAYLIST/
 .TemporaryItems/
 .Spotlight-V100/
 electric_guitar
 shooting_watch
 .Trashes/
//}

つぎのコマンドでSDカードに保存しているアプリを実行します。

//cmd{
nsh> /mnt/sd0/shooting_watch
Hello, shooting_watch!!!
----- Press SW2 to start the game. When the game starts, shoot SW1 continuously.-----
----- Press SW1 and SW2 to end the game.-----
//}

つぎの情報が表示されます。

 * SW2押下でゲームがスタートし、SW1で連射すること
 * SW1とSW2押下でゲームが終了すること

メッセージのとおりSW2を押下します。

カウントダウン表示と連射開始のメッセージが表示されます。
//cmd{
3...2...1...
Shooting!!!!!
//}

10秒間SW1の押下回数を測定します。10秒後にSW1の連射回数が表示されます。

今回の連射測定結果は【70回/10秒】でした。
//cmd{
Shooting count = 70

----- Press SW2 to start the game. When the game starts, shoot SW1 continuously.-----
----- Press SW1 and SW2 to end the game.-----
//}


== 環境構築
連射測定ゲームの環境構築について書きます。
@<chapref>{development_environment}は完了している前提とします。

=== ハードウェア構成
連射測定ゲームは追加で必要なハードウェアはありません。
@<hd>{concept|ハードウェア}に書いたハードウェアでプレイできます。

== ソースコード解説
連射測定ゲームのソースコードについて解説します。
ざっくり分類するとつぎになります。

 * GPIO初期化（割り込み設定、割り込み有効化）
 * メインループ 停止状態
 * メインループ 連射準備状態
 * メインループ 連射状態
 * 連射測定中待機
 * SW1割り込みハンドラ（SW1押下回数測定）
 * SW2割り込みハンドラ（ゲーム開始判定・ゲーム終了判定）
 * GPIO終了処理（割り込み無効化）

=== main関数
対象ソースコードファイル名はshooting_watch_main.cです。
@<list>{main_list}は連射測定装置のmain関数です。
少ない行数なのですべて掲載しました。

//listnum[main_list][main関数]{
int main(int argc, FAR char *argv[])
{
  int one_time_counter = 0;
  int game_coundown; 

  shooting_watch_gpio_create();

  printf("Hello, shooting_watch!!!\n");

  while(exit_shooting_watch != true) {
    switch (game_state) {
    case STOP:
      if (one_time_counter == 0) {
        printf("----- Press SW2 to start the game. When the game starts, shoot SW1 continuously.-----\n");
        printf("----- Press SW1 and SW2 to end the game.-----\n");
        one_time_counter = 1;

        board_gpio_write(USER_LED_1, USER_LED_TURN_OFF);
        board_gpio_write(USER_LED_2, USER_LED_TURN_OFF);
      }

      if (next_state) {
        next_state = false;

        if (board_gpio_int(SWITCH_2, false) < 0) {
          printf("board_gpio_int(switch_2) failure.\n");
        }  

        game_state = PRE_SHOOTING;
      }
      break;

    case PRE_SHOOTING:
      for (game_coundown = 3; game_coundown > 0; game_coundown--) {
        printf("%d...", game_coundown);
        fflush(stdout);
        sleep(1);
      }
      printf("\n");
      shooting_count = 0;
      game_state = SHOOTING;
      break;

    case SHOOTING:
      printf("Shooting!!!!!\n");
      shooting_process(10);

      printf("Shooting count = %ld\n", shooting_count);
      printf("\n");

      if (board_gpio_int(SWITCH_2, true) < 0) {
        printf("board_gpio_int(switch_2) failure.\n");
      }  

      one_time_counter = 0;
      game_state = STOP;
      break;

    default:
      break;
    }
  }

  exit_shooting_watch = false;
  shooting_watch_gpio_destroy();

  return 0;
}
//}


=== GPIO初期化（割り込み設定、割り込み有効化）
対象ソースコードファイル名はshooting_watch_gpio.cです。
GPIOの初期化で割り込み設定、割り込み有効化します。

@<list>{shooting_watch_gpio_create_list}はGPIO初期化関数です。
SW1は連射測定用にしようと思いました。
SW1・SW2はプルアップされており押下したときに0になり、リリースすると1に戻ります。
SW1押下の回数を測定したいため割り込みは立ち下がりエッジに設定しました。
その他の設定は椅子取りゲームの@<hd>{musical_chairs|GPIO初期化}と同じです。

//listnum[shooting_watch_gpio_create_list][GPIO初期化]{
void shooting_watch_gpio_create(void)
{
  /* 割り込み設定 */
  board_gpio_intconfig(SWITCH_1, INT_FALLING_EDGE,    true, shooting_watch_gpio_switch_1_handler); 
  board_gpio_intconfig(SWITCH_2, INT_FALLING_EDGE,    true, shooting_watch_gpio_switch_2_handler); 

  if (board_gpio_int(SWITCH_1, true) < 0) { 
    message("gpio_create board_gpio_int(switch_1) failure.\n");
  }

  if (board_gpio_int(SWITCH_2, true) < 0) {
    message("gpio_create board_gpio_int(switch_2) failure.\n");
  }  

  return;
}
//}

=== メインループ 停止状態
ゲームが起動するとGPIO初期化実行後に停止状態になります。
@<list>{main_stop_list}のswitchケース【STOP】に該当します。
停止状態になるとSW1・SW2の操作説明文をprintし、USER_LED1・USER_LED2を消灯します。
その後はSW2が押下されるまで待ちます。

SW2が押下されるとSW2割り込みハンドラでnext_stateがtrueになります。
メインループでnext_state == trueを検出できたらSW2割り込みを無効にしたのち連射準備状態に遷移します。
SW2を割り込み無効にするのは連射測定中にSW2の割り込みが発生しSW1押下の連射測定を邪魔したくないからです。

//listnum[main_stop_list][main関数 停止状態]{
int main(int argc, FAR char *argv[])
{
  // 省略    

  while(exit_shooting_watch != true) {
    switch (game_state) {
    case STOP:
      if (one_time_counter == 0) {
        printf("----- Press SW2 to start the game. When the game starts, shoot SW1 continuously.-----\n");
        printf("----- Press SW1 and SW2 to end the game.-----\n");
        one_time_counter = 1;

        board_gpio_write(USER_LED_1, USER_LED_TURN_OFF);
        board_gpio_write(USER_LED_2, USER_LED_TURN_OFF);
      }

      if (next_state) {
        next_state = false;

        if (board_gpio_int(SWITCH_2, false) < 0) {
          printf("board_gpio_int(switch_2) failure.\n");
        }  

        game_state = PRE_SHOOTING;
      }
      break;

    // 省略 

    }
  }

  // 省略

  return 0;
}
//}


=== メインループ 連射準備状態
連射準備状態は@<list>{main_pre_shooting_list}のswitchケース【PRE_SHOOTING】に該当します。
連射準備状態をつくった意味は連射測定を開始するまでに少し【間】を用意したかったからです。
いきなり連射測定を開始してしまうとプレイヤーが慌ててしまうかも・・・と思ったからです。

連射準備状態になると3秒のカウントダウン表示を行います。
カウントダウン表示は遅延なく直ぐに画面表示して欲しいため【fflush(stdout);】しています。
カウントダウン表示終了で連射状態に遷移します。

//listnum[main_pre_shooting_list][main関数 連射準備状態]{
int main(int argc, FAR char *argv[])
{
  // 省略

  while(exit_shooting_watch != true) {
    switch (game_state) {
    case STOP:
      // 省略

    case PRE_SHOOTING:
      for (game_coundown = 3; game_coundown > 0; game_coundown--) {
        printf("%d...", game_coundown);
        fflush(stdout);
        sleep(1);
      }
      printf("\n");
      shooting_count = 0;
      game_state = SHOOTING;
      break;

    // 省略

    }
  }

  // 省略

  return 0;
}
//}


=== メインループ 連射状態
連射状態は@<list>{main_shooting_list}のswitchケース【SHOOTING】に該当します。
連射状態になるとshooting_process関数を呼び出し、10秒間この関数の中で待機します。
10秒経過しshooting_process関数から戻ると連射回数を表示します。
その後、SW2割り込みを有効にして停止状態に遷移します。

//listnum[main_shooting_list][main関数 連射状態]{
int main(int argc, FAR char *argv[])
{
  // 省略

  while(exit_shooting_watch != true) {
    switch (game_state) {
    case STOP:
      // 省略

    case PRE_SHOOTING:
      // 省略

    case SHOOTING:
      printf("Shooting!!!!!\n");
      shooting_process(10);

      printf("Shooting count = %ld\n", shooting_count);
      printf("\n");

      if (board_gpio_int(SWITCH_2, true) < 0) {
        printf("board_gpio_int(switch_2) failure.\n");
      }  

      one_time_counter = 0;
      game_state = STOP;
      break;

    default:
      break;
    }
  }

  // 省略

  return 0;
}
//}


=== 連射測定中待機
連射状態時に呼び出され@<list>{shooting_process_list}の中で10秒間待機します。
この待ち時間中にSW1の割り込みハンドラでSW1押下の連射を測定します。
連射測定中ということをわかりやすくするために10秒の間、500msごとにUSER_LED2を点滅します。

//listnum[shooting_process_list][連射測定中待機]{
void shooting_process(uint32_t play_time)
{
  /* Timer Start */
  time_t start_time;
  time_t cur_time;
  int shooting_indicator = 0;

  time(&start_time);

  do {
    usleep(500 * 1000);

    shooting_indicator ^= USER_LED_TURN_ON;
    board_gpio_write(USER_LED_2, shooting_indicator);

  } while((time(&cur_time) - start_time) < play_time);

  board_gpio_write(USER_LED_2, USER_LED_TURN_OFF);
}
//}

=== SW1割り込みハンドラ（SW1押下回数測定）
@<list>{gpio_switch_1_handler_list}はSW1の割り込みハンドラです。
SW1を押下時の立ち下がりエッジで割り込みが発生します。
SW1の役割は【SW1押下回数の更新のみ】です。

//listnum[gpio_switch_1_handler_list][SW1割り込みハンドラ]{
bool exit_shooting_watch = false;
bool next_state = false;

extern u_long shooting_count;

static int shooting_watch_gpio_switch_1_handler(int irq, FAR void *context, FAR void *arg)
{
  ++shooting_count;

  return 0;
}
//}


=== SW2割り込みハンドラ（ゲーム開始判定・ゲーム終了判定）
@<list>{gpio_switch_2_handler_list}はSW2の割り込みハンドラです。
SW2を押下時の立ち下がりエッジで割り込みが発生します。
SW2の役割はつぎの2つです。

 * ゲーム開始のトリガ
 * SW1とSW2同時押下検出でゲーム終了

//listnum[gpio_switch_2_handler_list][SW2割り込みハンドラ]{
bool exit_shooting_watch = false;
bool next_state = false;

extern u_long shooting_count;


static int shooting_watch_gpio_switch_2_handler(int irq, FAR void *context, FAR void *arg)
{
  int sw2_status = board_gpio_read(SWITCH_2);
  int sw1_status = board_gpio_read(SWITCH_1);

  if (sw1_status && !sw2_status) next_state = true;
  if (!sw1_status && !sw2_status) exit_shooting_watch = true;

  return 0;
}
//}


=== GPIO終了処理（割り込み無効化）
@<list>{shooting_watch_gpio_destroy_list}はGPIO終了処理です。
SW1とSW2の割り込み無効にします。

//listnum[shooting_watch_gpio_destroy_list][GPIO終了処理（割り込み無効化）]{
void shooting_watch_gpio_destroy(void)
{
  if (board_gpio_int(SWITCH_1, false) < 0) { 
    message("gpio_destroy board_gpio_int(switch_1) failure.\n");
  }

  if (board_gpio_int(SWITCH_2, false) < 0) {
    message("gpio_destroy board_gpio_int(switch_2) failure.\n");
  }  

  return;
}
//}


== Tips


== 課題
=== 連射測定残り時間がわかりにくい
現在のゲームだと連射測定中の残り時間がどこにも表示されていません。
こういう測定系のゲームの場合、残り時間がこれくらいだからラストもっと追い込め、みたいなシーンが盛り上がるポイントだと思います。
何処かに連射測定の残り時間を表示すると面白いかと思います。


