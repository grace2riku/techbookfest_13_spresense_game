
= 開発環境構築
各種開発環境を構築します。

== Spresense SDK
//footnote[spresense_doc_url][@<href>{https://developer.sony.com/develop/spresense/docs/home_ja.html, Spresenseドキュメント 参考URL}]

Spresense SDKの開発環境を構築します。
私はmacOS Monterey バージョン12.5.1のホストPCで開発環境を構築しました。
Linux、Windowsでも環境構築可能のようです。

Spresense SDKの開発環境構築はWebのドキュメント@<fn>{spresense_doc_url}とおりに進めれば完了できます。
SpresenseドキュメントにはCLI・IDE（Visual Studio Code）の2とおりの環境構築方法が記載されています。
私はCLIで環境構築したので本書の記載はCLIの記載・手順となります。

=== Spresense SDKバージョン
Spresense SDKのバージョンは執筆当時の最新版【v2.6.0 （2022/08/05）】で確認しています。


== ゲームのソースコード取得
//footnote[app_add_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E3%83%84%E3%83%BC%E3%83%AB%E3%82%92%E4%BD%BF%E7%94%A8%E3%81%99%E3%82%8B, ユーザーアプリの追加方法 参考URL}]
//footnote[github_url][@<href>{https://github.com/grace2riku/spresense_game, Spresenseゲームgithub}]

今回作ったゲームのソースコードをgithub@<fn>{github_url}からZIPでダウンロードします。
ダウンロードしたZIPファイルは開発構築したSpresenseディレクトリに解凍します。

デフォルトだとつぎのディレクトリになります。

 * /Users/ユーザー名/spresense

ここにコピーするのでつぎのようになります。

 * /Users/ユーザー名/spresense/spresense_game-main

spresense_game-mainディレクトリには3つのアプリがあります。

 * musical_chairs: 椅子取りゲーム
 * shooting_watch: 連射測定ゲーム
 * electric_guitar: エレキギター

アプリの作成はWebドキュメント@<fn>{app_add_url}6. ユーザーアプリの追加方法 -> 6.3. ツールを使用するの手順とおりに作業しました。


== コンフィグレーション
//footnote[defconfig_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%AE%9A%E7%BE%A9%E6%B8%88%E3%81%BF%E3%82%B3%E3%83%B3%E3%83%95%E3%82%A3%E3%82%AE%E3%83%A5%E3%83%AC%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3defconfig, 定義済みコンフィギュレーション（defconfig）の説明先URL}]

コンフィグレーションの手順を書きます。

/Users/ユーザー名/spresense/sdk ディレクトリに移動します（カレントディレクトリがspresenseの前提とします）。

//cmd{
$ cd sdk
//}

インストールしたツールを使用可能にするために、つぎのおまじないのコマンドを実行します。
//cmd{
source ~/spresenseenv/setup
//}

こちらの定義済みコンフィグレーション@<fn>{defconfig_url}を指定します。
各要素は後で説明します。

//cmd{
@<seqsplit>{$ tools/config.py examples/audio_player examples/audio_beep examples/sixaxis feature/loadable device/sdcard feature/usbmsc}
//}

コンフィグレーションを変更します。
//cmd{
$ tools/config.py -m
//}

@<img>{config-m_1}のようにApplication Configurationを選択します。
//image[config-m_1][Application Configurationを選択]{ 
//}

@<img>{config-m_2}のようにExamplesを選択します。
//image[config-m_2][Examplesを選択]{ 
//}

@<img>{config-m_3}のようにBMI160 sensor exampleを選択しスペースキーを押下します。
//image[config-m_3][BMI160 sensor exampleを選択]{ 
//}

@<img>{config-m_4}のようにBMI160 sensor exampleの*を空白スペースに変更します。
//image[config-m_4][BMI160 sensor exampleを非選択]{ 
//}

Escキーを押下し、ひとつ上の階層に移動します。
@<img>{config-m_4_spresense_sdk選択}のようにSpresense SDKを選択します。
//image[config-m_4_spresense_sdk選択][Spresense SDKを選択]{ 
//}

@<img>{config-m_5_examples選択}のようにExamplesを選択します。
//image[config-m_5_examples選択][Spresense SDK -> Examplesを選択]{ 
//}

@<img>{config-m_6_examples選択中}の画面になります。
//image[config-m_6_examples選択中][Spresense SDK -> Examplesの階層]{ 
//}

Audio beep example、Audio player exampleを選択しスペースキーを押下します。
@<img>{config-m_7_examples変更後}のように*を空白スペースに変更します。
//image[config-m_7_examples変更後][Audio beep example、Audio player exampleを非選択]{ 
//}

Escキーを押下し、ひとつ上の階層に移動します。
@<img>{config-m_8_spresense_game選択}のようにSpSesense_gameを選択します。
//image[config-m_8_spresense_game選択][SpSesense_gameを選択]{ 
//}

@<img>{config-m_9_spresense_game選択中}の画面になります。
//image[config-m_9_spresense_game選択中][Spresense_gameのコンフィグレーション画面]{ 
//}

electric_guitar・musical chairs・shooting_watchを選択し
@<img>{config-m_10_spresense_game変更後}のようにコンフィグレーションを変更します。
//image[config-m_10_spresense_game変更後][Spresense_gameコンフィグレーション変更]{ 
//}

 * electric_guitar: Mに設定（バイナリを別ファイルにする。SDカードに保存し実行する想定）
 * musical chairs: *に設定（nuttx.spkファイルに組み込まれる）
 * shooting_watch: Mに設定（バイナリを別ファイルにする。SDカードに保存し実行する想定）

本当であればmusical chairsもMに設定し、別ファイルにしたかったのですが、
この後のmakeでエラーになり原因理解・問題解決できなかったためnuttx.spkファイルに組み込むようにしました。

Escキーを押下し、ひとつ上の階層に移動します。
Escキーを押下し続けて@<img>{config-m_11_save}の画面に移動します。
コンフィグレーションをセーブするか聞いてくるのでYesを選択します。
//image[config-m_11_save][コンフィグレーション保存]{ 
//}


makeを実行して、と表示されます。
//cmd{
$ tools/config.py -m
LN: include/arch to arch/arm/include
@<seqsplit>{LN: include/arch/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/include}
LN: include/arch/chip to arch/arm/include/cxd56xx
@<seqsplit>{LN: arch/arm/src/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/../common}
@<seqsplit>{LN: arch/arm/src/board/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/src}
LN: arch/arm/src/chip to arch/arm/src/cxd56xx
@<seqsplit>{LN: /Users/k-abe/spresense/nuttx/drivers/platform to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/../drivers}
LN: platform/board to /Users/k-abe/spresense/sdk/apps/platform/dummy
make[2]: Nothing to be done for `preconfig'.
configuration written to .config

*** End of the configuration.
*** Execute 'make' to start the build or try 'make help'.
//}

=== コンフィグレーション要素について
コンフィグレーションの設定について説明します。

//cmd{
@<seqsplit>{$ tools/config.py examples/audio_player examples/audio_beep examples/sixaxis feature/loadable device/sdcard feature/usbmsc}
//}

tools/config.pyはコンフィグレーションを行うツール名称です。
tools/config.py以降の記述がコンフィグレーション設定です。
今回の作った3つのアプリに必要なコンフィグレーションをすべて設定しています。

==== examples/audio_player
@<title>{musical_chairs}のコンフィグレーションです。
@<title>{musical_chairs}はexamples/audio_playerのサンプルプログラムをベースにして作りました。
そのためexamples/audio_playerのコンフィグレーションを設定しています。
@<img>{config-m_7_examples変更後}でexamples/audio_playerを非対象にしていました。
これはexamples/audio_playerのアプリケーションはバイナリファイルに組込み不要なためです。


==== examples/audio_beep
@<title>{electric_guitar}のコンフィグレーションです。
@<title>{electric_guitar}はbeep音を鳴らす動作があります。
beep音を鳴らすサンプルプログラム（examples/audio_beep）があったのでこのコンフィグレーションを設定しました。
@<img>{config-m_7_examples変更後}でexamples/audio_beepを非対象にしていました。
これは@<hd>{development_environment|examples/audio_player}と同じく、examples/audio_beepのアプリケーションはバイナリファイルに組込み不要なためです。

==== examples/sixaxis
@<title>{electric_guitar}のコンフィグレーションです。
@<title>{electric_guitar}はジャイロセンサ（BMI160）で傾きを取得する動作があります。
ジャイロセンサのサンプルプログラム（examples/sixaxis）があったのでこのコンフィグレーションを設定しました。
@<img>{config-m_4}でexamples/sixaxisを非対象にしていました。
これは@<hd>{development_environment|examples/audio_player}と同じく、examples/sixaxisのアプリケーションはバイナリファイルに組込み不要なためです。


==== feature/loadable, device/sdcard
//footnote[loadable_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_%E3%83%AD%E3%83%BC%E3%83%80%E3%83%96%E3%83%ABelf%E3%83%81%E3%83%A5%E3%83%BC%E3%83%88%E3%83%AA%E3%82%A2%E3%83%AB, ローダブルELFチュートリアルの説明先URL}]

@<hd>{concept|ローダブルELF}で書いたとおりローダブルELFは【OSとアプリケーションを別々のバイナリで作成し、動作時にアプリケーションをロードして実行できる機能】でした。
ローダブルELFのコンフィグレーションはWebドキュメントのチュートリアル@<fn>{loadable_url}に記載されているとおりに設定しました。


==== feature/usbmsc
//footnote[usbmsc_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_system_usbmsc, USB MSC機能の説明先URL}]

このコンフィグレーションはUSB MSC機能@<fn>{usbmsc_url}を使うために設定しました。
USB MSC（Mass Storage Class）はホストPCからSpresenseボード上のSDカードへ直接アクセスすることができます。
今回はつぎの用途でUSB MSC機能を使います。

 * アプリケーションを変更しSDカードにアプリのバイナリファイルを保存するとき
 * SDカードに保存してある椅子取りゲームの音楽ファイルを変更するとき

USB MSC機能を使わなくともよいですがその場合、つぎを手作業で行う必要があります。

 * Spresenseボード上のSDカードを抜き、ホストPCに接続しデータ書き込み
 * SDカードをSpresenseボードに差し直し

開発効率アップに影響する機能と思ったのでコンフィグレーションに設定しました。


== make
makeします。-jオプションで並列ビルドが可能です。
//cmd{
$ make -j
//}

makeが正常終了するとつぎの表示になります（make実行結果の最終行付近から引用です）。
OSとアプリが組み込まれたnuttx.spkファイルが作成されます。


//cmd{
@<seqsplit>{AR (create): libboard.a   cxd56_main.o cxd56_clock.o cxd56_bringup.o cxd56_appinit.o cxd56_power.o cxd56_ioctl.o cxd56_ostest.o cxd56_gpioif.o cxd56_pwm.o cxd56_spi.o cxd56_sdcard.o cxd56_boot.o cxd56_audio.o cxd56_uid.o cxd56_crashdump.o cxd56_sensors.o cxd56_bmi160_i2c.o cxd56_netinit.o cxd56_flash.o cxd56_usbmsc.o cxd56_i2cdev.o cxd56_spidev.o }
LD: nuttx
Generating: nuttx.spk
make[2]: Nothing to be done for `all'.
tools/cxd56/mkspk -c2 nuttx nuttx nuttx.spk;
File nuttx.spk is successfully created.
Done.
//}

nuttx.spkファイルはsdkディレクトリに作成されます。

 * /Users/ユーザー名/spresense/sdk/nuttx.spk

ローダブルELF指定したアプリ（shooting_watch、electric_guitar）は@<img>{バイナリ保存先}に作成されます。
//image[バイナリ保存先][ローダブルELF指定したアプリの作成ディレクトリ]{ 
//}

 * /Users/ユーザー名/spresense/sdk/apps/bin


== 書き込み
nuttx.spkファイルをSpresenseに書き込みます。

まずはホストPCとSpresenseメインボードをUSBケーブルで接続します。
つぎのコマンドでSpresenseメインボードのシリアルポートのデバイスファイル名を調べます。

//cmd{
$ ls /dev/cu.usb*
/dev/cu.usbserial-141410
//}

デバイスファイル名は/dev/cu.usbserial-141410であることがわかりました。
デバイスファイル名は読者のみなさんの環境で異なると思いますのでこの後のデバイスファイ名は適宜読み替えてください。

つぎのコマンドを実行しmakeで作成されたnuttx.spkをSpresenseに書き込みます。

//cmd{
tools/flash.sh -c /dev/cu.usbserial-141410 nuttx.spk
//}

正常に書き込みが終了するとつぎの表示になり、Spresenseが再起動します。

//cmd{
>>> Install files ...
install -b 115200
Install nuttx.spk
|0%-----------------------------50%------------------------------100%|
######################################################################

301472 bytes loaded.
Package validation is OK.
Saving package to "nuttx"
updater# sync
updater# Restarting the board ...
reboot
//}


== シェルと接続
書き込みが終了したらNuttxのシェル（nsh）と接続します。

つぎのコマンドを実行します。
私はターミナルにminicomを使用しました。ボーレート115200bpsであれば他のターミナルでも接続できます。

//cmd{
minicom -D /dev/cu.usbserial-141410 -b 115200
//}

シェルに接続できるとnsh>のように表示されます。

//cmd{
Welcome to minicom 2.8

OPTIONS: 
Compiled on Jan  4 2021, 00:04:46.
Port /dev/cu.usbserial-141410, 12:35:17

Press Meta-Z for help on special keys


NuttShell (NSH) NuttX-10.2.0
nsh> 
//}

helpコマンドを実行してみます。
Builtin Apps:につぎがあればOKです。

 * msconn : USB MSC機能接続コマンド
 * msdis : USB MSC機能接続解除コマンド
 * musical_chairs : 椅子取りゲーム

//cmd{
nsh> help
help usage:  help [-v] [<cmd>]

  .          cmp        false      ls         nslookup   sleep      usleep     
  [          dirname    free       mkdir      poweroff   source     xd         
  ?          date       help       mkfatfs    ps         test       
  basename   dd         hexdump    mkfifo     pwd        time       
  break      df         ifconfig   mkrd       reboot     true       
  cat        echo       ifdown     mksmartfs  rm         uname      
  cd         exec       ifup       mount      rmdir      umount     
  cp         exit       kill       mv         set        unset      

Builtin Apps:
  msconn          msdis           musical_chairs  nsh   
//}


== ゲームバイナリをSDカードにコピー
連射測定ゲームとエレキギターはローダブルELFのモジュールとしたのでBuiltin Apps:には組み込まれていません。
マイクロSDカードに連射測定ゲームとエレキギターのバイナリをコピーします。

Spresense拡張ボードのUSBミニBコネクタとホストPCをUSBケーブルで接続します。
シェルに接続した状態からつぎのコマンドを実行するとつぎの表示になります。

//cmd{
nsh> msconn
mcsonn_main: Creating block drivers
mcsonn_main: Configuring with NLUNS=1
mcsonn_main: handle=0x2d063910
mcsonn_main: Bind LUN=0 to /dev/mmcsd0
mcsonn_main: Connected
//}

ホストPCに記憶デバイスとして認識されていればホストPC⇄Spresenseでデータ転送が可能です。

私のホストPCでは@<img>{usbmsc認識}のように認識されました。
//image[usbmsc認識][マイクロSDカードが記憶デバイスとしてホストPCに認識される]{ 
//}

あとは連射測定ゲーム（shooting_watch）とエレキギター（electric_guitar）のバイナリをコピーします。

ファイルのコピーが終わったらホストPCとマイクロSDカードの接続を解除します。
つぎのコマンドを実行します。
//cmd{
nsh> msdis
msdis: Disconnected
//}

このコマンドでホストPCからマイクロSDカードが見えなくなります。

これで環境構築は終わりです。
ゲームをプレイする準備ができました。
