
= 開発環境構築
各種開発環境を構築します。

== Spresense SDK
//footnote[spresense_doc_url][@<href>{https://developer.sony.com/develop/spresense/docs/home_ja.html, Spresenseドキュメント 参考URL}]

Spresense SDKの開発環境を構築します。
私はmacOS Monterey バージョン12.5.1のホストPCで開発環境を構築しました。
Linux、Windowsでも環境構築可能のようです。

Spresense SDKの開発環境構築はWebのドキュメント@<fn>{spresense_doc_url}とおりに進めれば完了できます。
SpresenseドキュメントにはCLI・IDE(Visual Studio Code)の2とおりの環境構築方法が記載されています。
私はCLIで環境構築したので本書の記載はCLIの記載・手順となります。

=== Spresense SDKバージョン
Spresense SDKのバージョンは執筆当時の最新版【v2.6.0 (2022/08/05)】で確認しています。


== ゲームのソースコード取得
//footnote[app_add_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B, ユーザーアプリの追加方法 参考URL}]
//footnote[github_url][@<href>{https://github.com/grace2riku/spresense_game, Spresenseゲームgithub}]

今回作ったゲームのソースコードをgithub@<fn>{github_url}からZIPでダウンロードします。
ダウンロードしたZIPファイルは開発構築したSpresenseディレクトリに解凍します。

デフォルトだとつぎのディレクトリになります。

/Users/ユーザー名/spresense

ここにコピーするのでつぎのようになります。

/Users/ユーザー名/spresense/spresense_game-main


== コンフィグレーション
//footnote[defconfig_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_set_up_ja.html#_%E5%AE%9A%E7%BE%A9%E6%B8%88%E3%81%BF%E3%82%B3%E3%83%B3%E3%83%95%E3%82%A3%E3%82%AE%E3%83%A5%E3%83%AC%E3%83%BC%E3%82%B7%E3%83%A7%E3%83%B3defconfig, 定義済みコンフィギュレーション（defconfig）の説明先URL}]

コンフィグレーションの手順を書きます。

/Users/ユーザー名/spresense/sdk ディレクトリに移動します(カレントディレクトリがspresenseの前提とします)。

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
$ tools/config.py examples/audio_player examples/audio_beep examples/sixaxis feature/loadable device/sdcard feature/usbmsc
//}

コンフィグレーションを変更します。
//cmd{
$ tools/config.py -m
//}

//comment{
TODO: コンフィグレーションの変更を画面キャプチャと併用し書く。
//}


makeを実行せよ、と表示されます。
//cmd{
$ tools/config.py -m
LN: include/arch to arch/arm/include
LN: include/arch/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/include
LN: include/arch/chip to arch/arm/include/cxd56xx
LN: arch/arm/src/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/../common
LN: arch/arm/src/board/board to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/src
LN: arch/arm/src/chip to arch/arm/src/cxd56xx
LN: /Users/k-abe/spresense/nuttx/drivers/platform to /Users/k-abe/spresense/nuttx/boards/arm/cxd56xx/spresense/../drivers
LN: platform/board to /Users/k-abe/spresense/sdk/apps/platform/dummy
make[2]: Nothing to be done for `preconfig'.
configuration written to .config

*** End of the configuration.
*** Execute 'make' to start the build or try 'make help'.
//}

makeします。-jオプションで並列ビルドが可能です。
//cmd{
$ make -j
//}

makeが正常終了するとつぎの表示になります(make実行結果の最終行付近から引用です)。

//cmd{
AR (create): libboard.a   cxd56_main.o cxd56_clock.o cxd56_bringup.o cxd56_appinit.o cxd56_power.o cxd56_ioctl.o cxd56_ostest.o cxd56_gpioif.o cxd56_pwm.o cxd56_spi.o cxd56_sdcard.o cxd56_boot.o cxd56_audio.o cxd56_uid.o cxd56_crashdump.o cxd56_sensors.o cxd56_bmi160_i2c.o cxd56_netinit.o cxd56_flash.o cxd56_usbmsc.o cxd56_i2cdev.o cxd56_spidev.o 
LD: nuttx
Generating: nuttx.spk
make[2]: Nothing to be done for `all'.
tools/cxd56/mkspk -c2 nuttx nuttx nuttx.spk;
File nuttx.spk is successfully created.
Done.
//}


=== コンフィグレーション要素について


== make

== 書き込み

== ゲームバイナリをSDカードにコピー

== シェルと接続
