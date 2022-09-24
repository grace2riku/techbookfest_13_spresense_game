
= 椅子取りゲーム
この章は椅子取りゲーム（アプリ名称はmusical_chairs）について書きます。

== ゲーム概要説明
一般的な椅子取りゲームの構成要素はつぎになると思います。

 1. 音源
 2. 音源を再生する装置
 3. 音源を任意の長さで一時停止⇄再生するしかけ
 4. 椅子: 1つ以上必要
 5. プレイヤー: （椅子の数 + 1）人

今回作ったSpresenseを使った椅子取りゲームは構成要素1, 2, 3の機能を持ちます。


== プレイ画面
椅子取りゲームを実行しているときの動画です。

 * @<href>{https://youtube.com/shorts/2DxOI-9-4do?feature=share,椅子取りゲーム実行中の動画}

以降にゲーム実行開始からの手順を書きます。

シェルに接続し、椅子取りゲームのアプリ名（musical_chairs）を入力します。
SW2押下で音楽が再生されること、SW1とSW2押下でゲームが終了するメッセージが表示されます。
ここでのSW1、SW2とはAPS学習ボードのタクトスイッチSW1、SW2です。

//cmd{
nsh> musical_chairs
Start musical_chairs.
----- Press SW2 to play music.-----
----- Press SW1 and SW2 to end the game.-----
//}

SW2押下でつぎの表示になります。
音楽ファイルが再生されます。
//cmd{
state:stop play_or_pause_trigger.
//}

任意の時間で再生が止まりつぎの表示になります。
音楽再生状態から一時停止の状態になったことを示しています。
//cmd{
state:play goto pause state.
//}

もう一度SW2を押下するとつぎの表示になり、音楽ファイルが再生されます。
【Attention】とエラーコードのような表示がでていますが音楽ファイルは再生されます。
表示されているメッセージはとくに調査していません。
音楽ファイルの最後まで再生⇄一時停止を繰り返します。
//cmd{
state:pause goto play state.
@<seqsplit>{Attention: module[11][0] attention id[1]/code[20] (components/decoder/decoder_component.cpp L511)}
@<seqsplit>{Attention!! components/decoder/dAttention: module[11][0] attention id[1]/code[20] (components/decoder/decoder_component.cpp L511)}
ecoder_comp L511 ecode 1 subcode 20
Attention!! components/decoder/decoder_comp L511 ecode 1 subcode 20
//}

音楽ファイルを最後まで再生すると停止し、つぎの表示になります。
//cmd{
state:play goto stop state.
//}

SW1とSW2を同時に押すとつぎのメッセージが表示され、ゲームを終了します。
//cmd{
exit switch pressed. goto exit.
Exit musical_chairs.
//}


== 環境構築
椅子取りゲームの環境構築について書きます。
@<chapref>{development_environment}は完了している前提とします。

=== ハードウェア構成
椅子取りゲームをプレイするには@<hd>{concept|ハードウェア}で書いたハードウェアの他につぎのハードウェアが必要です。

 1. スピーカー

==== スピーカー
音源を再生するために必要です。
Spresense拡張ボードに接続します。

=== その他
//footnote[audio_player_tutorial_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_%E3%83%93%E3%83%AB%E3%83%89%E3%83%AD%E3%83%BC%E3%83%89%E6%89%8B%E9%A0%86, Audio Player サンプルアプリケーション ビルド&ロード手順 参照先URL}]

椅子取りゲームの音楽ファイルを再生するためにつぎの準備が必要です。

 1. デコード処理を行うDSPバイナリ
 2. 音楽ファイル
 3. プレイリスト

こちらの準備はWebドキュメントのチュートリアル 4.1.1. ビルド&ロード手順の4〜6@<fn>{audio_player_tutorial_url}に書いてあります。


==== デコード処理を行うDSPバイナリ
音楽ファイル再生にはでコード処理を行うDSPバイナリが必要です。
こちらのバイナリファイルをアプリケーションで読み込み、音楽ファイルを再生します。
今回はMP3の音楽ファイルのデコードを行うDSPバイナリファイル（MP3DEC）をマイクロSDカードに保存します。

MP3のDSPバイナリはつぎのディレクトリに格納されています。

 * /Users/ユーザー名/spresense/sdk/modules/audio/dsp/MP3DEC

このファイルを前述したWebドキュメントのチュートリアル 4.1.1. ビルド&ロード手順の手順4のとおり、
マイクロSDカードのルートにBINディレクトリをつくりコピーします。


==== 音楽ファイル
音楽ファイルを前述したWebドキュメントのチュートリアル 4.1.1. ビルド&ロード手順の手順5のとおり、
マイクロSDカードのルートにAUDIOディレクトリをつくりコピーします。


==== プレイリスト
椅子取りゲームはサンプルプログラムexamples/audio_playerをベースに作っています。

examples/audio_playerは前述したWebドキュメントのチュートリアル 4.1.1. ビルド&ロード手順の手順6に記載のとおり
【簡易PlayListを利用した再生】を行っています。
そのため簡易PlayListをマイクロSDカードのルートにPLAYLISTディレクトリの中に作成します。

===== プレイリストの中身
プレイリストの中身はつぎのファイルに説明があります。

 * /Users/ユーザー名/spresense/sdk/modules/audio/playlist/README.txt

上記ファイルを参考に今回はつぎの内容にしました。

//listnum[playlist_id][プレイリストの中身]{
maoutamasii_old-music_boss07.mp3,Anyone,1stAlbum,2,16,44100,mp3
//}

項目の意味はつぎのとおりです。

 * maoutamasii_old-music_boss07.mp3 : 音楽ファイル名

 * Anyone : 著者名

 * 1stAlbum : アルバム名

 * 2 : チャンネル数

 * 16 : bit長

 * 44100 : サンプリングレート

 * mp3 : フラグ。音楽ファイルのフォーマットでmp3かwavを指定する。


== ソースコード解説
椅子取りゲームのソースコードについて解説します。
椅子取りゲームには限らず他のゲームについても該当することですがつぎのスタンスで実装しています。

 * なるべく少ない工数でゲームを実装する
サンプルプログラムをベースにして機能を追加します。
将来的に変更しやすいソフトウェアの構造にすることはとても大切なことだと思います。
ですが今回は物を動かすことを第一に考え、コードの読みやすさ、ソフトウェアの変更容易性には目を瞑ります。

=== 状態の導入
椅子取りゲームはexamples/audio_playerのサンプルプログラムをベースに実装します。

examples/audio_playerは10秒間音楽ファイルを5回再生して終了する動作となっています。
この構造を椅子取りゲームを実現するための構造に変更する必要があります。

椅子取りゲームはつぎの状態で振る舞いが変わるのでその状態を実装していきます。

 * 停止状態: 音楽ファイルが1秒も再生していない状態です。
 ゲーム開始時は停止状態になります。音楽ファイルを最後まで再生するとこの状態に戻ります。

 * 再生状態: 音楽ファイルを再生している状態です。
椅子取りゲームのプレイ状況でいうとプレイヤーが椅子の周りを回り、音楽が停止するタイミングを伺っている状況です。

 * 一時停止状態: 音楽ファイルの再生が停止した状態です。
椅子取りゲームのプレイ状況でいうとプレイヤーは音楽が停止を認識し競って椅子に座ろうとしている状況です。
椅子取りが決着したら音楽ファイル再生するためにSW2を押し、再生状態に移行します。


=== 再生開始
SW2押下が音楽ファイル再生のトリガです。
停止状態からSW2押下でplay_or_pause_triggerがtrueになります。
音楽ファイルを再生するには@<list>{main_loop_app_start_list}のapp_start関数を呼び出します。

//listnum[main_loop_app_start_list][メインループの再生開始箇所]{
  for (;;)
    {

      switch (game_state) {
        case STOP:
          if (play_or_pause_trigger) {
            play_or_pause_trigger = false;

            printf("state:stop play_or_pause_trigger.\n");


            /* Running... */
//          printf("Running time is %d sec\n", PLAYER_PLAY_TIME);

            /* Start player operation. */
            if (!app_start())
              {
                printf("Error: app_start_player() failure.\n");

                /* Abnormal termination processing */
                goto errout_start;
              }
            game_state = PLAY;
            printf("state:stop goto play state.\n");
          }
          break;

//}


@<list>{app_start_list}は初期化のapp_init_player関数、再生開始のapp_play_player関数を呼び出しています。
//listnum[app_start_list][app_start関数]{
static bool app_start(void)
{
  /* Init Player */

  Track *t = &s_player_info.file.track;
  if (!app_init_player(t->codec_type,
                       t->sampling_rate,
                       t->channel_number,
                       t->bit_length))
    {
      printf("Error: app_init_player() failure.\n");
      app_close_play_file();
      return false;
    }

  /* Play Player */

  if (!app_play_player())
    {
      printf("Error: app_play_player() failure.\n");
      app_close_play_file();
      return false;
    }

  return true;
}
//}


@<list>{app_init_player_list}は音楽再生の初期化です。
音楽再生の初期化ついてはつぎのWebドキュメントの該当箇所を見ると分かると思います。
5.3.3.10. 各機能の詳細からページを送っていくとInitialize and Start playerの記載箇所があります。

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_%E5%90%84%E6%A9%9F%E8%83%BD%E3%81%AE%E8%A9%B3%E7%B4%B0,5.3.3.10. 各機能の詳細 Initialize and Start player}

//listnum[app_init_player_list][app_init_player関数]{
static int app_init_player(uint8_t codec_type,
                           uint32_t sampling_rate,
                           uint8_t channel_number,
                           uint8_t bit_length)
{
    AudioCommand command;
    command.header.packet_length = LENGTH_INIT_PLAYER;
    command.header.command_code  = AUDCMD_INITPLAYER;
    command.header.sub_code      = 0x00;
    command.player.player_id                 = AS_PLAYER_ID_0;
    command.player.init_param.codec_type     = codec_type;
    command.player.init_param.bit_length     = bit_length;
    command.player.init_param.channel_number = channel_number;
    command.player.init_param.sampling_rate  = sampling_rate;
    snprintf(command.player.init_param.dsp_path,
             AS_AUDIO_DSP_PATH_LEN,
             "%s",
             DSPBIN_FILE_PATH);
    AS_SendAudioCommand(&command);

    AudioResult result;
    AS_ReceiveAudioResult(&result);
    return printAudCmdResult(command.header.command_code, result);
}
//}

@<list>{app_play_player_list}は音楽再生です。

//listnum[app_play_player_list][app_play_player関数]{
static int app_play_player(void)
{
    AudioCommand command;
    command.header.packet_length = LENGTH_PLAY_PLAYER;
    command.header.command_code  = AUDCMD_PLAYPLAYER;
    command.header.sub_code      = 0x00;
    command.player.player_id     = AS_PLAYER_ID_0;
    AS_SendAudioCommand(&command);

    AudioResult result;
    AS_ReceiveAudioResult(&result);
    return printAudCmdResult(command.header.command_code, result);
}
//}

音楽再生についてはつぎのWebドキュメントの該当箇所を見ると分かると思います。
5.3.3.10. 各機能の詳細からページを送っていくとStart Playerの記載箇所があります。

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_%E5%90%84%E6%A9%9F%E8%83%BD%E3%81%AE%E8%A9%B3%E7%B4%B0,5.3.3.10. 各機能の詳細 Start Player}

うえのリンク先に記載の【図 13. Player State sequence】も初期化、再生の一連のシーケンスがわかりやすいです。

@<img>{Player_State_sequence}はうえのリンク先の図の引用です。
//image[Player_State_sequence][Player State sequence]{ 
//}


=== 任意時間の再生について
examples/audio_playerは10秒間の音楽ファイル再生ですが、椅子取りゲームでは任意の長さで再生できるように変更しています。
任意の長さは@<list>{music_play_time_list}のように再生開始する時に3秒〜11秒の間で乱数により指定しています。

//listnum[music_play_time_list][任意時間の指定]{
        case PLAY:
          music_play_time = 3 + rand() % 8;
          app_play_process(music_play_time, &game_event);
//}


=== 再生中の動作
再生中は@<list>{app_play_process_list}のapp_play_process関数内をループします。
この関数はつぎの条件を満たすと終了します。

 * 音楽ファイルを最後まで再生した場合。引数にMUSIC_ENDをセットし終了する。
 * 音楽ファイル再生中にエラーが発生した場合。引数にERROR_HAPPENをセットし終了する。
 * ゲーム終了条件（APS学習ボードのSW1・SW2が同時に押された）が成立した場合。引数にEND_REQUESTをセットし終了する。
 * 引数で指定された任意時間の再生が終了した場合。引数にMUSIC_PAUSEをセットし終了する。

//listnum[app_play_process_list][再生中]{
void app_play_process(uint32_t play_time, GAME_EVENT* p_game_event)
{
  /* Timer Start */
  time_t start_time;
  time_t cur_time;
  int fifo_state_result;

  time(&start_time);

  do
    {
      /* Check the FIFO every 2 ms and fill if there is space. */

      usleep(2 * 1000);
      if (!app_refill_simple_fifo(s_player_info.file.fd, &fifo_state_result))
        {
          if (fifo_state_result == FIFO_RESULT_EOF) {
            *p_game_event = MUSIC_END;
          } else {
            *p_game_event = ERROR_HAPPEN;
          }
          return;
        }

#ifdef CONFIG_EXAMPLES_AUDIO_PLAYER_USEPOSTPROC2
      static int cnt = 0;
      if (cnt++ > 100)
        {
          app_send_setpostproc_command();
          cnt = 0;
        }
#endif /* CONFIG_EXAMPLES_AUDIO_PLAYER_USEPOSTPROC2 */

      if (exit_app) {
        *p_game_event = END_REQUEST;
        return;
      }

    } while((time(&cur_time) - start_time) < play_time);
    *p_game_event = MUSIC_PAUSE;
}
//}


=== メインループ

@<list>{main_loop_list}のように@<list>{app_play_process_list}の関数を呼び出した側では引数の値により動きが変わります。

 * 再生が任意時間経過で一時停止の場合（MUSIC_PAUSE）： 一時停止動作（app_pause）を行い、一時停止状態に遷移する。
 * 音楽ファイルを最後まで再生した場合（MUSIC_END）： 停止動作（app_stop）を行い、停止状態に遷移する。
 * ゲーム終了条件が検出した場合（END_REQUEST）： 停止動作（app_stop）を行い、ゲーム終了する（fot文の外に出る）。


//listnum[main_loop_list][メインループ]{
  for (;;)
    {

      switch (game_state) {
        case STOP:
          if (play_or_pause_trigger) {
            play_or_pause_trigger = false;

            printf("state:stop play_or_pause_trigger.\n");


            /* Running... */
//          printf("Running time is %d sec\n", PLAYER_PLAY_TIME);

            /* Start player operation. */
            if (!app_start())
              {
                printf("Error: app_start_player() failure.\n");

                /* Abnormal termination processing */
                goto errout_start;
              }
            game_state = PLAY;
            printf("state:stop goto play state.\n");
          }
          break;

        case PLAY:
          music_play_time = 3 + rand() % 8;
          app_play_process(music_play_time, &game_event);
          if (game_event == MUSIC_PAUSE) {
            if (!app_pause())
            {
              printf("Error: app_pause() failure.\n");
              goto errout_start;
            }
            game_state = PAUSE;
            printf("state:play goto pause state.\n");
          } else if (game_event == MUSIC_END) {
            /* Stop player operation. */
            if (!app_stop()) {
                printf("Error: app_stop() failure.\n");
                return 1;
            }
            game_state = STOP;
            printf("state:play goto stop state.\n");
          }
          break;

        case PAUSE:
          if (play_or_pause_trigger) {
            play_or_pause_trigger = false;

            if (!replay())
            {
              printf("Error: replay() failure.\n");
              goto errout_start;
            }
            game_state = PLAY;
            printf("state:pause goto play state.\n");
          }
          break;

        default:
          break;
      } // switch 

      if (exit_app) {
        exit_app = false;
        if (!app_stop()) {
            printf("Error: app_stop() failure.\n");
            return 1;
        }
        game_state = STOP;
        printf("exit switch pressed. goto exit.\n");
        break;
      }
#ifndef CONFIG_AUDIOUTILS_PLAYLIST
      break;
#endif
    } // for
//}


=== 再生→一時停止
音楽ファイルを再生から一時停止する場合は@<list>{pause_list}の関数を呼び出します。
関数内部ではAS_STOPPLAYER_NORMALをapp_stop_player関数の引数に指定しています。

//listnum[pause_list][一時停止]{
static bool app_pause(void)
{
  bool result = true;

  int  stop_mode = AS_STOPPLAYER_NORMAL;

  if (!app_stop_player(stop_mode))
    {
      printf("Error: app_stop_player() failure.\n");
      result = false;
    }

  return result;
}
//}


app_stop_player関数は@<list>{app_stop_player_list}になっています。
引数に指定されたストップモードを構造体メンバにセットし、AS_SendAudioCommand関数を呼び出すと音楽再生が停止します。
AS_SendAudioCommand関数はオーディオを制御するコマンドです。

//listnum[app_stop_player_list][app_stop_player関数]{
static bool app_stop_player(int mode)
{
    AudioCommand command;
    command.header.packet_length = LENGTH_STOP_PLAYER;
    command.header.command_code  = AUDCMD_STOPPLAYER;
    command.header.sub_code      = 0x00;
    command.player.player_id            = AS_PLAYER_ID_0;
    command.player.stop_param.stop_mode = mode;
    AS_SendAudioCommand(&command);

    AudioResult result;
    AS_ReceiveAudioResult(&result);
    return printAudCmdResult(command.header.command_code, result);
}
//}

この辺りはつぎのWebドキュメントに詳しく書かれています。

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_audio_subsystem,Spresense SDK 開発ガイド　5.3. Audio Subsystem}

//comment{
Spresense SDK 開発ガイド　5.3. Audio Subsystem
https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_audio_subsystem
//}

とはいえAudio Subsystem全体を見るのは大変だと思います。
再生停止の動作についてはつぎのWebドキュメントの該当箇所を見ると分かると思います。
5.3.3.10. 各機能の詳細からページを送っていくとstop_modeの記載箇所があります。

 * @<href>{https://developer.sony.com/develop/spresense/docs/sdk_developer_guide_ja.html#_%E5%90%84%E6%A9%9F%E8%83%BD%E3%81%AE%E8%A9%B3%E7%B4%B0,5.3.3.10. 各機能の詳細 stop_mode}

一時停止の場合は次回の再生時に音楽ファイルの続きから再生したいです。
そのため@<list>{pause_list}では通常停止のAS_STOPPLAYER_NORMALを指定しています。
通常停止は停止要求のタイミングでFIFOの中身は残っている状態でできるだけ早く停止します。
対してES終端停止（AS_STOPPLAYER_ESEND）は、停止要求時点でFIFOに入っているデータをすべて発音してから停止します。


=== 一時停止→再生
一時停止から音楽ファイルを再生するには@<list>{replay_list}の関数を実行します。

//listnum[replay_list][replay関数]{
static bool replay(void)
{
  /* Play Player */
  if (!app_play_player())
    {
      printf("Error: app_play_player() failure.\n");
      app_close_play_file();
      return false;
    }

  return true;
}
//}


=== 停止
音楽再生が停止するパターンとしてつぎの2点があります。

 * 音楽ファイルを最後まで再生した場合
 * SW1とSW2押下を検出しゲーム終了の場合

うえのどちらの場合も@<list>{app_stop_list}の関数を実行します。

//comment{
音楽ファイル終端まで達して停止したときはどちらの停止モードで停止しているか確認しておくこと!!!
音楽ファイル終端まで達して停止したとき: stop_modeはAS_STOPPLAYER_ESENDだった。

//}

//listnum[app_stop_list][app_stop関数]{
static bool app_stop(void)
{
  bool result = true;

  /* Set stop mode.
   * If the end of the file is detected, play back until the data empty
   * and then stop.(select AS_STOPPLAYER_ESEND)
   * Otherwise, stop immediate reproduction.(select AS_STOPPLAYER_NORMAL)
   */

  int  stop_mode = (s_player_info.file.size != 0) ?
                    AS_STOPPLAYER_NORMAL : AS_STOPPLAYER_ESEND;

  if (!app_stop_player(stop_mode))
    {
      printf("Error: app_stop_player() failure.\n");
      result = false;
    }

  if (!app_close_play_file())
    {
      printf("Error: app_close_play_file() failure.\n");
      result = false;
    }

  return result;
}
//}


=== GPIO
椅子取りゲームではAPS学習ボードのSW1、SW2につぎの機能を割り当てています。

 * SW1: SW2と同時押下でゲーム終了
 * SW2: 音楽再生のトリガ。SW1と同時押下でゲーム終了

上記機能を満たすためのソースコードについて説明します。
すべてつぎのファイルに実装されています。

 * /Users/ユーザー名/spresense/spresense_game-main/musical_chairs/gpio.c


==== GPIO初期化
GPIO初期化は@<list>{gpio_create_list}です。
つぎの設定を行います。

 * 割り込み設定（対象ピン、割り込みエッジ、割り込みハンドラの登録）
 * 割り込み有効化

//listnum[gpio_create_list][GPIO初期化]{
void gpio_create(void)
{
  /* 割り込み設定 */
  board_gpio_intconfig(SWITCH_1, INT_BOTH_EDGE, true, gpio_switch_1_handler); 
  board_gpio_intconfig(SWITCH_2, INT_BOTH_EDGE, true, gpio_switch_2_handler); 

  if (board_gpio_int(SWITCH_1, true) < 0) { 
    message("gpio_create board_gpio_int(switch_1) failure.\n");
  }

  if (board_gpio_int(SWITCH_2, true) < 0) {
    message("gpio_create board_gpio_int(switch_2) failure.\n");
  }  

  return;
}
//}


==== 割り込み設定

割り込み設定は@<list>{board_gpio_intconfig_list}です。

//listnum[board_gpio_intconfig_list][gpio_create関数]{
  board_gpio_intconfig(SWITCH_1, INT_BOTH_EDGE, true, gpio_switch_1_handler); 
//}

この場合はつぎの設定をしています。

 * APS学習ボードSW1 （SWITCH_1 == 39ピン）を対象とする
 * 割り込みは立ち上がり・立ち下がりの両エッジ
 * フィルタをON
 * 割り込みハンドラはgpio_switch_1_handlerに設定

APIリファレンスはこちらのリンクです。

 * @<href>{https://developer.sony.com/develop/spresense/developer-tools/api-reference/api-references-spresense-sdk/group__gpioif.html,GPIO Interface driver}


==== 割り込み有効化

割り込み有効化は@<list>{board_gpio_int_list}です。

//listnum[board_gpio_int_list][board_gpio_int関数]{
  if (board_gpio_int(SWITCH_1, true) < 0) { 
    message("gpio_create board_gpio_int(switch_1) failure.\n");
  }
//}

SW1の割り込みを有効にしています。


==== 割り込みハンドラ
@<list>{gpio_int_handler_list}のコードです。

SW1両エッジ検出時の割り込みハンドラがgpio_switch_1_handlerです。

SW2両エッジ検出時の割り込みハンドラがgpio_switch_2_handlerです。

割り込みハンドラではSW1、SW2の読み込みに加えてAPS学習ボードのUSER_LED1、USER_LED2の2つのLEDをSW1のレベルで点灯・消灯しています。
SW1・SW2は押下で0、押下なしで1が読み込めます。
LEDは1の書き込みで点灯、0の書き込みで消灯します。

SW2の割り込みハンドラではplay_or_pause_trigger変数に再生開始トリガを示すtrueを設定します。
SW1・SW2のどちらの割り込みハンドラでもSW1・SW2が押下されていたらexit_app変数にゲーム終了を示すtrueを設定します。

//listnum[gpio_int_handler_list][GPIO割り込みハンドラ]{
bool play_or_pause_trigger = false;
bool exit_app = false;

static int gpio_switch_1_handler(int irq, FAR void *context, FAR void *arg)
{
  int sw1_status = board_gpio_read(SWITCH_1);
  int sw2_status = board_gpio_read(SWITCH_2);

  board_gpio_write(USER_LED_1, sw1_status);

  if (!sw1_status && !sw2_status) exit_app = true;

  return 0;
}

static int gpio_switch_2_handler(int irq, FAR void *context, FAR void *arg)
{
  int sw2_status = board_gpio_read(SWITCH_2);
  int sw1_status = board_gpio_read(SWITCH_1);
  board_gpio_write(USER_LED_2, sw2_status);

  if (!sw2_status) play_or_pause_trigger = true;
  if (!sw1_status && !sw2_status) exit_app = true;

  return 0;
}
//}


==== GPIO後処理
GPIO後処理は@<list>{gpio_destroy_list}です。

//listnum[gpio_destroy_list][GPIO後処理]{
void gpio_destroy(void)
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

つぎの設定を行います。

 * 割り込み禁止

割り込み禁止は@<list>{board_gpio_int_list}のboard_gpio_int関数の第2引数指定が異なります。
割り込み禁止はfalseを指定します。


== Tips
=== プログラム終了時に割り込み禁止にする必要性について
Spresenseでアプリケーションを作り技術書を書くのは今回で2回目です。
今回本を書く過程で過去の本では気づかなかったことに気づいたので共有させてください。
すでにご存じかもしれませんが見てくださるとありがたいです。

アプリケーション終了時に@<hd>{GPIO後処理}で割り込みを禁止しています。
もし割り込み禁止せずに終了した場合、アプリケーションが動いていないのにSW1またはSW2を押下すると割り込みハンドラが動きます。

椅子取りゲーム以外のアプリケーションがSW1・SW2の割り込みを使う場合（実際に使います）、
椅子取りゲームの終了処理が不十分なため他のアプリケーションの実行を邪魔してしまいます。

割り込みを禁止せずに終了しているので当たり前といえば当たり前ですが私には盲点でした。

というのも私はこれまでOSがない・シェルがないベタメタルな組込み機器ばかりをやってきたので

 * アプリケーションが終了する == 組込み機器の電源がOFFになる

という認識がありました。

OS動作のもと再びアプリケーションが実行可能な環境の場合は

 * アプリケーション終了後も異常な動作をしない（他のアプリケーションの実行に影響を与えない）ように終了処理をしっかりする

ということを今回学びました。


== 課題
現状の椅子取りゲームの課題です。

=== ゲーム終了時の不具合
つぎの状態でゲーム終了するとエラーが発生し、次回椅子取りゲームを起動してもエラーが発生しゲームをプレイできません。

 * 一時停止状態
 * 音楽ファイル最後まで再生し停止状態

リセットでしかエラーを回復できません。
おそらくゲーム終了時の終了処理に不具合があります。

=== ローダブルELF対応
今回つくった3つのゲームの中で椅子取りゲームだけローダブルELF対応できませんでした。
@<hd>{concept|ローダブルELF}に書いたコンセプトを実現できなかったので原因を理解して対策したいところです。

=== 音量調整機能
音量はベースにしたサンプルプログラムexamples/audio_playerから変更していません。
静かな環境で椅子取りゲームを開始する分は問題ないですが、少し騒がしい環境だと音楽が聞こえません。
音量を調節する機能は必要そうです。

=== 選曲機能
選曲ができないため1ファイルの固定再生となります。
1曲のみ固定再生だと飽きてしまうため改善が必要だと考えています。

