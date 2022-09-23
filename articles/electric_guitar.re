
= エレキギター
この章はエレキギター（アプリ名称はelectric_guitar）について書きます。

== ゲーム概要説明
//footnote[micto:bit_electric_guitar_book_url][@<href>{https://switch-education.com/books/microbit2/, 参考書籍URL}]
//footnote[micto:bit_electric_guitar_movie_url][@<href>{https://twitter.com/juraruming/status/1507704880709836800?s=20&t=Y3xCZY2bu22FQg0SiXlShA, micro:bit エレキギターの動画}]

エレキギターの元ネタはつぎの本です。

●micro:bitではじめるプログラミング第2版 親子で学べるプログラミングとエレクトロニクス@<fn>{micto:bit_electric_guitar_book_url}

・3-3　[使うモジュール]バングルモジュール　エレキギターを作る

これはmicro:bitの加速度センサーを使って、傾けると音が変わるギターです。

実際にmicro:bitでつくってみた動画はこちらです@<fn>{micto:bit_electric_guitar_movie_url}。

Spresenseには各種機能拡張用ボードが各社から販売されています。
ジャイロセンサーのボードをSpresenseに接続し、micro:bit版エレキギターと同じ動作を実現してみようと思ったのが開発の動機です。


== プレイ画面
シェルに接続し、連射測定ゲームのアプリ名（electric_guitar）を入力します。
連射測定ゲームのバイナリはSDカードに格納しています。
つぎのコマンドでSDカードの中身を確認します。
electric_guitarがエレキギターのコマンド名です。

//cmd{
nsh> ls /mnt/sd0/
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
nsh> /mnt/sd0/electric_guitar
//}

つぎの情報が表示されます。

//cmd{
----- If you tilt the board while pressing SW1, you will hear a do-re-mi sound.-----
----- Press SW1 and SW2 to end the game.-----
[16674] -747, 990, 286 / -13850, -470, 10578
dt=0.020000, gx=-45.593262, gy=60.424805, gz=17.456055, deg(x)=-7.868042, deg(y)=40.745850, deg(z)=-80.649109
//}

はじめの2行はつぎの内容です。
 * SW1押下し傾けるとド・レ・ミと発音すること
 * SW1とSW2押下で終了すること

3行目はBMI160（3軸加速度・3軸ジャイロ）から読み出したつぎの情報を表示しています。

 * センサータイム, ジャイロセンサ: x軸, ジャイロセンサ: y軸, ジャイロセンサ: z軸 / 加速度センサ: x軸, 加速度センサ: y軸, 加速度センサ: z軸

センサータイムはBMI160がカウントしているカウンターです。
@<hd>{reference_material|BMI160 Datasheet}の2.3.1 Sensor Timeに記載があります。

4行目はつぎの情報を表示しています。

 * 前回からの経過時間, 角速度: x軸, 角速度: y軸, 角速度: z軸, 角度: x軸, 角度: y軸, 角度: z軸

BMI160が接続されているSpresenseメインボードの傾きをつぎにするとドレミと発音します。

 * 0°以上20°未満: ドと発音
 * 35°以上55°未満: レと発音
 * 70°以上90°未満: ミと発音

動画はこちらの@<href>{https://youtube.com/shorts/mzNJ5q6-Ij4?feature=share,【リンク】}です。

SW1・SW2を同時に押下するとつぎのメッセージを表示し終了します。
//cmd{
Stop  AudioBeep example
Exit  AudioBeep example
//}


== 環境構築
エレキギターの環境構築について書きます。
@<chapref>{development_environment}は完了している前提とします。

=== ハードウェア構成
エレキーギターを実行するには@<hd>{concept|ハードウェア}で書いたハードウェアの他につぎのハードウェアが必要です。

 1. SPRESENSE用3軸加速度・3軸ジャイロ・気圧・温度センサ アドオンボード
 2. スピーカー

==== SPRESENSE用3軸加速度・3軸ジャイロ・気圧・温度センサ アドオンボード
//footnote[bmi160_addon_board_url][@<href>{https://www.switch-science.com/catalog/5258/, SPRESENSE用3軸加速度・3軸ジャイロ・気圧・温度センサ アドオンボード 参照先URL}]

Spresenseメインボードに接続可能なアドオンボードです。
Bosch Sensortec製のつぎのセンサー@<fn>{bmi160_addon_board_url}を搭載しています。

 * BMI160（3軸加速度・3軸ジャイロ）
 * BMP280（気圧・温度センサ）

==== スピーカー
音源を再生するために必要です。
Spresense拡張ボードに接続します。椅子取りゲームと同じ汎用スピーカーでOKです。


== ソースコード解説
エレキギターのソースコードについて解説します。
ざっくり分類するとつぎになります。

 * examples/audio_beepサンプルプログラム流用部分
 * APS学習基板GPIO初期化
 * SpresenseメインボードLED操作
 * examples/sixaxisサンプルプログラム流用部分
 * 角速度-角度算出
 * 角度指定でビープ音再生

=== examples/audio_beepサンプルプログラム流用部分
エレキギターはBMI160の傾きによりドレミのビープ音を発音します。
ビープ音の発音はexamples/audio_beepサンプルプログラムを流用しています。
具体的につぎの動作を流用しています。

 * ビープ音初期化
 * ビープ音再生
 * ビープ音終了処理

対象ソースコードはつぎになります。

 * /Users/ユーザー名/spresense/spresense_game-main/electric_guitar/audio_beep_main.cxx


==== ビープ音初期化
@<list>{audio_beep_create_list}はビープ音初期化のコードです。
examples/audio_beepサンプルプログラムのaudio_beep_main.cxxのmain関数に初期化コードが書いてあります。
その初期化コードをaudio_beep_create関数でラップし、エレキギターアプリケーションから呼び出すようにしました。

//listnum[audio_beep_create_list][ビープ音初期化]{
extern "C" int audio_beep_create(void) {
  /* Set I/O parameters for power on. */

  if (!app_power_on()) 
    {
      printf("Error: app_power_on() failure.\n");
      return 1;
    }

  /* Cancel output mute. */

  if (board_external_amp_mute_control(false) != OK)
    {
      printf("Error: board_external_amp_mute_control(false) failuer.\n");
      return 1;
    }

  printf("Start AudioBeep example\n");



  return 0;
}
//}

==== ビープ音再生
@<list>{audio_beep_list}はビープ再生のコードです。
関数内部ではapp_beep関数を呼び出しています。

//listnum[audio_beep_list][ビープ音再生（ラッパー関数）]{
extern "C" int audio_beep(int frequency) {
  bool beep_enable = true;

  if (!frequency) {
    beep_enable = false;
  } 

  if (!app_beep(beep_enable, -40, frequency)) {
      return 1;
  }

  return 0;
}
//}

@<list>{app_beep_list}はビープ音再生のコードです。
この関数呼び出しでビープ音が再生されます。

//listnum[app_beep_list][ビープ音再生]{
static bool app_beep(bool en = false, int16_t vol = 255, uint16_t freq = 0)
{
  if (!en)
    {
      /* Stop beep */

      if (cxd56_audio_stop_beep() != CXD56_AUDIO_ECODE_OK)
        {
          return false;
        }
    }

  if (0 != freq)
    {
      /* Set beep frequency parameter */

      if (cxd56_audio_set_beep_freq(freq) != CXD56_AUDIO_ECODE_OK)
        {
          return false;
        }
    }

  if (255 != vol)
    {
      /* Set beep volume parameter */

      if (cxd56_audio_set_beep_vol(vol) != CXD56_AUDIO_ECODE_OK)
        {
          return false;
        }
    }

  if (en)
    {
      /* Play beep */

      if (cxd56_audio_play_beep() != CXD56_AUDIO_ECODE_OK)
        {
          return false;
        }
    }

  return true;
}
//}

==== ビープ音終了処理
@<list>{audio_beep_destroy_list}はビープ音終了のコードです。
examples/audio_beepサンプルプログラムのaudio_beep_main.cxxのmain関数に終了処理が書いてあります。
その初期化コードをaudio_beep_destroy_list関数でラップし、エレキギターアプリケーションから呼び出すようにしました。

//listnum[audio_beep_destroy_list][ビープ音終了処理]{
extern "C" int audio_beep_destroy(void) {
  /* Beep off. */

  if (!app_beep())
    {
      printf("Error: app_beep() failuer.\n");
      return 1;
    }

  /* Set output mute. */

  if (board_external_amp_mute_control(true) != OK)
    {
      printf("Error: board_external_amp_mute_control(true) failuer.\n");
      return 1;
    }

  printf("Stop  AudioBeep example\n");

  /* Set I/O parameters for power off. */

  if (!app_power_off())
    {
      printf("Error: app_power_off() failure.\n");
      return 1;
    }

  printf("Exit  AudioBeep example\n");

  return 0;
}
//}


=== APS学習基板GPIO操作
エレキギターのAPS学習ボードはつぎの動作で使います。

 * SW1押下中にドレミのビープ音を発音する
 * SW1とSW2同時押下で終了する

SW1はポーリングによるGPIO読み出し、SW2は割り込みを使いました。

対象ソースコードはつぎになります。

 * /Users/ユーザー名/spresense/spresense_game-main/electric_guitar/electric_guitar_gpio.c

@<list>{electric_guitar_gpio_switch_2_handler_list}はSW2割り込みハンドラです。
SW1とSW2押下が検出できたら終了を意味する変数を設定します。

//listnum[electric_guitar_gpio_switch_2_handler_list][SW2割り込みハンドラ]{
static int electric_guitar_gpio_switch_2_handler(int irq, FAR void *context, FAR void *arg)
{
  int sw2_status = board_gpio_read(SWITCH_2);
  int sw1_status = board_gpio_read(SWITCH_1);

  if (!sw1_status && !sw2_status) exit_electric_guitar = true;

  return 0;
}
//}

@<list>{electric_guitar_gpio_create_list}はGPIO初期化です。
SW1はプルアップ・入力ポートとして設定しています。
SW2は立ち下がりエッジ割り込み、割り込みハンドラ登録、割り込みを有効しています。

//listnum[electric_guitar_gpio_create_list][GPIO初期化]{
void electric_guitar_gpio_create(void)
{
  board_gpio_config(SWITCH_1, 0, true, false, PIN_PULLUP);

  /* 割り込み設定 */
  board_gpio_intconfig(SWITCH_2, INT_FALLING_EDGE,    true, electric_guitar_gpio_switch_2_handler); 

  if (board_gpio_int(SWITCH_2, true) < 0) {
    message("gpio_create board_gpio_int(switch_2) failure.\n");
  }  

  return;
}
//}


@<list>{electric_guitar_gpio_destroy_list}はGPIO終了処理です。
SW2割り込みを禁止にします。

//listnum[electric_guitar_gpio_destroy_list][GPIO終了]{
void electric_guitar_gpio_destroy(void)
{
  if (board_gpio_int(SWITCH_2, false) < 0) {
    message("gpio_destroy board_gpio_int(switch_2) failure.\n");
  }  

  return;
}
//}


=== SpresenseメインボードLED初期化
エレキギターではドレミの発音に合わせてSpresenseメインボード上のLED0〜3を点灯・消灯します。
LED点灯・消灯パターンはつぎのとおりです。

 * ドの発音（0°以上20°未満）  : LED0を点灯
 * レの発音（35°以上55°未満） : LED1を点灯
 * ミの発音（70°以上90°未満） : LED2を点灯
 * ドレミ発音以外            : LED0, 1, 2, 3を点灯

@<list>{spresense_main_board_led_list}はSpresenseメインボードLED初期化のコードです。
SpresenseメインボードLED0〜3を出力に設定し、消灯しています。

PIN_LED*マクロの定義はつぎのファイルに定義されています。

 * /Users/ユーザー名/spresense/nuttx/arch/arm/include/cxd56xx/pin.h

Webドキュメント
@<href>{https://developer.sony.com/ja/develop/spresense/developer-tools/get-started-using-nuttx/nuttx-developer-guide#_pin_specification,11.2.3. Pin specification}
の表 3. SDK が制御できるピンのリストにLED0〜3のピン配置が書いてあります。

//listnum[spresense_main_board_led_list][SpresenseメインボードLED初期化]{

#define PIN_LED0  (PIN_I2S1_BCK)
#define PIN_LED1  (PIN_I2S1_LRCK)
#define PIN_LED2  (PIN_I2S1_DATA_IN)
#define PIN_LED3  (PIN_I2S1_DATA_OUT)

const int spresense_main_board_led_pin[4] = {
  PIN_LED0,
  PIN_LED1,
  PIN_LED2,
  PIN_LED3
};

#define SPRESENSE_MAIN_BOARD_LED_TURN_ON    (1)
#define SPRESENSE_MAIN_BOARD_LED_TURN_OFF   (0)

int main(int argc, FAR char *argv[])
{
  // 省略

  for (int i = 0; i < 4; i++) {
    board_gpio_config(spresense_main_board_led_pin[i], 0, true, true, PIN_FLOAT);
    board_gpio_write(spresense_main_board_led_pin[i], SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
  }

}
//}


=== examples/sixaxisサンプルプログラム流用部分
BMI160（3軸加速度・3軸ジャイロ）から加速度・角速度を取得するサンプルプログラムがexamples/sixaxisです。
examples/sixaxisはI2CでBMI160から加速度・角速度を取得し、シリアル通信で送信を繰り返します。
エレキギターでは角速度から角度を算出しています。
BMI160から加速度・角速度を取得する一連のロジックを流用しました。
BMI160を抽象化しファイルとして扱います。
@<list>{examples_sixaxis_list}がコードです。

//listnum[examples_sixaxis_list][examples/sixaxisサンプルプログラム流用部分抜粋]{
#define ACC_DEVPATH      "/dev/accel0"

int main(int argc, FAR char *argv[])
{
  int fd;
  struct accel_gyro_st_s data;

  fd = open(ACC_DEVPATH, O_RDONLY);
  if (fd < 0) {
      printf("Device %s open failure. %d\n", ACC_DEVPATH, fd);
      return -1;
  }

  for (; ; ) {
      int ret;

      ret = read(fd, &data, sizeof(struct accel_gyro_st_s));
      if (ret != sizeof(struct accel_gyro_st_s)) {
          fprintf(stderr, "Read failed.\n");
          break;
      }

      /* If sensing time has been changed, show 6 axis data. */
      if (prev != data.sensor_time) {

          ++print_display_count;
          if (print_display_count >= 100) {
            print_display_count = 0;

            printf("\033[2J");  // 画面クリア
            printf("\033[%d;%dH", 0, 0);  // 移動 高さ, 横

            printf("----- If you tilt the board while pressing SW1, you will hear a do-re-mi sound.-----\n");
            printf("----- Press SW1 and SW2 to end the game.-----\n");

            printf("[%" PRIu32 "] %d, %d, %d / %d, %d, %d\n",
                  data.sensor_time,
                  data.gyro.x, data.gyro.y, data.gyro.z,
                  data.accel.x, data.accel.y, data.accel.z);

            fflush(stdout);
          }

      }

      usleep(10000);

      if (exit_electric_guitar) break;
  }

  close(fd);

  return 0;
}
//}

==== open
openでBMI160にアクセスするためのファイルハンドルを取得しています。
この後のreadで取得したファイルハンドルでアクセスします。

==== read
read実行でBMI160から構造体accel_gyro_st_sのデータを読み込みます。
readのコードを追うとつぎの処理を実行していました。

 * /Users/ユーザー名/spresense/nuttx/drivers/sensors/bmi160.c bmi160_read関数

bmi160_read関数の中をみると@<list>{bmi160_read_bmi160_getregs_list}のコードでBMI160のレジスタ（BMI160_DATA_8）から15バイト読み出していました。

//list[bmi160_read_bmi160_getregs_list][加速度・角速度取得]{
  bmi160_getregs(priv, BMI160_DATA_8, (FAR uint8_t *)buffer, 15);
//}

レジスタ（BMI160_DATA_8）の定義を確認すると0x0Cでした。
@<hd>{reference_material|BMI160 Datasheet}のp49 Figure 20: BMI160 register mapに記載があります。
レジスタアドレス0x0C〜0x1Aまでの15バイトはつぎのデータです。

 * 0x0C, 0x0D: gyr_x_7_0, gyr_x_15_8 ジャイロセンサx軸 16bit
 * 0x0E, 0x0F: gyr_y_7_0, gyr_y_15_8 ジャイロセンサy軸 16bit
 * 0x10, 0x11: gyr_z_7_0, gyr_z_15_8 ジャイロセンサz軸 16bit
 * 0x12, 0x13: acc_x_7_0, acc_x_15_8 加速度センサx軸 16bit
 * 0x14, 0x15: acc_y_7_0, acc_y_15_8 加速度センサy軸 16bit
 * 0x16, 0x17: acc_z_7_0, acc_z_15_8 加速度センサz軸 16bit
 * 0x18, 0x19, 0x1A: sensor_time_7_0, sensor_time_15_8, sensor_time_23_16 センサータイム 24bit

BMI160 Datasheetのレジスタマップと@<list>{examples_sixaxis_list}のreadで使っている構造体（accel_gyro_st_s）メンバの定義が一致していました。

構造体はつぎのファイルに定義されています。

 * /Users/ユーザー名/spresense/nuttx/include/nuttx/sensors/bmi160.h

//list[bmi160.h_list][構造体（accel_gyro_st_s）定義]{
struct accel_t
{
  int16_t x;
  int16_t y;
  int16_t z;
};

struct gyro_t
{
  int16_t x;
  int16_t y;
  int16_t z;
};

struct accel_gyro_st_s
{
  struct gyro_t  gyro;
  struct accel_t accel;
  uint32_t sensor_time;
};
//}

==== close
openで取得したファイルハンドルをクローズします。


=== 角速度-角度算出
BMI160から取得した角速度から角度を算出します。
角速度を積分し角度を算出しています。
つぎを参考にさせていただき実装してみました。

 * @<hd>{reference_material|ジャイロ（角速度）から角度の算出方法}
 * @<hd>{reference_material|BMI160サンプルプログラム}

@<list>{calc_degree_list}がコードです。

//listnum[calc_degree_list][角速度-角度算出部分抜粋]{
int main(int argc, FAR char *argv[])
{
  int fd;
  struct accel_gyro_st_s data;
  uint32_t prev;

  volatile float dt;
  volatile float degree_x, degree_y, degree_z;
  volatile float gx, gy, gz;
  volatile float pre_gx, pre_gy, pre_gz;
  int print_display_count;


  fd = open(ACC_DEVPATH, O_RDONLY);
  if (fd < 0) {
      printf("Device %s open failure. %d\n", ACC_DEVPATH, fd);
      return -1;
  }

  prev = 0;
  degree_x = degree_y = degree_z = 0;
  dt = 0;
  pre_gx = pre_gy = pre_gz = 0;
  print_display_count = 0;

  for (; ; ) {
      int ret;

      ret = read(fd, &data, sizeof(struct accel_gyro_st_s));
      if (ret != sizeof(struct accel_gyro_st_s)) {
          fprintf(stderr, "Read failed.\n");
          break;
      }


      /* If sensing time has been changed, show 6 axis data. */
      if (prev != data.sensor_time) {
          dt = (abs(data.sensor_time - prev) * 10) / 1000.0;
          prev = data.sensor_time;

          gx = convertRawGyro(data.gyro.x);
          gy = convertRawGyro(data.gyro.y);
          gz = convertRawGyro(data.gyro.z);

          degree_x += (pre_gx + gx) * dt / 2;
          degree_y += (pre_gy + gy) * dt / 2;
          degree_z += (pre_gz + gz) * dt / 2;

          degree_x = fmodf(degree_x, 360.0);
          degree_y = fmodf(degree_y, 360.0);
          degree_z = fmodf(degree_z, 360.0);

          pre_gx = gx;
          pre_gy = gy;
          pre_gz = gz;

          ++print_display_count;
          if (print_display_count >= 100) {
            print_display_count = 0;

            printf("\033[2J");  // 画面クリア
            printf("\033[%d;%dH", 0, 0);  // 移動 高さ, 横

            printf("----- If you tilt the board while pressing SW1, you will hear a do-re-mi sound.-----\n");
            printf("----- Press SW1 and SW2 to end the game.-----\n");

            printf("[%" PRIu32 "] %d, %d, %d / %d, %d, %d\n",
                  data.sensor_time,
                  data.gyro.x, data.gyro.y, data.gyro.z,
                  data.accel.x, data.accel.y, data.accel.z);

            printf("dt=%f, gx=%f, gy=%f, gz=%f, deg(x)=%f, deg(y)=%f, deg(z)=%f\n", 
              dt, gx, gy, gz,
              degree_x, degree_y, degree_z);

            fflush(stdout);
          }

      }

      usleep(10000);

      play(fabsf(degree_z));

      if (exit_electric_guitar) break;
  }

  exit_electric_guitar = false;

  close(fd);


  return 0;
}
//}

play関数が角度に応じてドレミのビープ音を発音する関数です。
この関数にはz軸の角度のみを引数に指定しています。
これは今回の@<hd>{SPRESENSE用3軸加速度・3軸ジャイロ・気圧・温度センサ アドオンボード}の取り付け位置、
基板を傾ける方向・角度でジャイロのz軸が変化していることが実験でわかったためです。

@<img>{アドオンボード取り付け位置}はアドオンボードのz軸を明示した写真です。
//image[アドオンボード取り付け位置][z軸の定義]{ 
//}

実装が完了したらBMI160から取得した角速度、算出した角度を確認します。
BMI160から取得した角速度、算出した角度はシリアル送信しログをシリアルターミナルで可視化します。
確認しやすいようにつぎのようにしました。

 * ログが複数行になると確認しづらいと思ったので1セットのログごとに画面クリアし表示する
 * ログが高速に出力し続けると確認しづらいと思ったので1秒ごとにログを表示する


=== 角度指定でビープ音再生
@<list>{play_list}は引数に設定した角度でドレミを発音するコードです。
SW1が押下且つつぎの角度が設定されたときにドレミを発音します。
またドレミの発音によりLED0〜LED2のいずれかが点灯します。

 * 0°以上20°未満: ドと発音（LED0点灯）
 * 35°以上55°未満: レと発音（LED1点灯）
 * 70°以上90°未満: ミと発音（LED2点灯）


//listnum[play_list][角度指定でビープ音再生]{
#define SPRESENSE_MAIN_BOARD_LED_TURN_ON    (1)
#define SPRESENSE_MAIN_BOARD_LED_TURN_OFF   (0)

#define BEEP_FREQUENCY_DO (262)
#define BEEP_FREQUENCY_RE (294)
#define BEEP_FREQUENCY_MI (330)
#define BEEP_NONE         (0)

void play(float degree) {
  int i = 0;
  int sw1_status = board_gpio_read(SWITCH_1);  

  if (!sw1_status) {
    if (0 <= degree && degree < 20) {
      if (audio_beep(BEEP_FREQUENCY_DO) != 0) {
        printf("audio_beep(BEEP_FREQUENCY_DO) failure.\n");
      }

      board_gpio_write(PIN_LED0, SPRESENSE_MAIN_BOARD_LED_TURN_ON);
      board_gpio_write(PIN_LED1, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED2, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED3, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
    } else if (35 <= degree && degree < 55) {
      if (audio_beep(BEEP_FREQUENCY_RE) != 0) {
        printf("audio_beep(BEEP_FREQUENCY_RE) failure.\n");
      }

      board_gpio_write(PIN_LED0, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED1, SPRESENSE_MAIN_BOARD_LED_TURN_ON);
      board_gpio_write(PIN_LED2, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED3, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
    } else if (70 <= degree && degree < 90) {
      if (audio_beep(BEEP_FREQUENCY_MI) != 0) {
        printf("audio_beep(BEEP_FREQUENCY_MI) failure.\n");
      }

      board_gpio_write(PIN_LED0, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED1, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
      board_gpio_write(PIN_LED2, SPRESENSE_MAIN_BOARD_LED_TURN_ON);
      board_gpio_write(PIN_LED3, SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
    } else {
      for (i = 0; i < 4; i++) {
        board_gpio_write(spresense_main_board_led_pin[i], SPRESENSE_MAIN_BOARD_LED_TURN_ON);
      }
    }
  } else {
    if (audio_beep(BEEP_NONE) != 0) {
      printf("audio_beep(NONE) failure.\n");
    }
    for (i = 0; i < 4; i++) {
      board_gpio_write(spresense_main_board_led_pin[i], SPRESENSE_MAIN_BOARD_LED_TURN_OFF);
    }
  }
}
//}

ドレミの発音はシンプルでaudio_beep関数をドレミの周波数を引数に設定し呼び出します。

ドレミの周波数（Hz）は@<list>{beep_frequency_list}のとおりです。

//listnum[beep_frequency_list][ドレミの周波数]{
#define BEEP_FREQUENCY_DO (262) // ドを発音
#define BEEP_FREQUENCY_RE (294) // レを発音
#define BEEP_FREQUENCY_MI (330) // ミを発音
#define BEEP_NONE         (0)   // 発音なし
//}


== 課題
現状のエレキギターの課題です。

=== 基板の位置によってはドレミの発音ができない
プログラム実行後にドレミ発音するであろう角度に基板を傾けますがドレミが発音しなくなります。
現状、解決策はなくこのモードに入ったらリセットしています。
致命的な不具合なので解決が必要と考えています。

