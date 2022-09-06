
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

今回作ったゲームのソースコードをgithubからZIPでダウンロードします。
ダウンロードしたZIPファイルは開発構築したSpresenseディレクトリに解凍します。

デフォルトだとつぎのディレクトリになります。

/Users/ユーザー名/spresense

ここにコピーするのでつぎのようになります。

/Users/ユーザー名/spresense/spresense_game-main


== コンフィグレーション
コンフィグレーションの手順を書きます。

/Users/ユーザー名/spresense/sdk ディレクトリに移動します(カレントディレクトリがspresenseの前提とします)。

//cmd{
$ cd sdk
//}

インストールしたツールを使用可能にするために、つぎのおまじないのコマンドを実行します。
//cmd{
source ~/spresenseenv/setup
//}

こちらの定義済みコンフィグレーションを指定します。
各要素は後で説明します。

//cmd{
$ tools/config.py examples/audio_player examples/audio_beep examples/sixaxis feature/loadable device/sdcard feature/usbmsc
//}

コンフィグレーションを変更します。
//cmd{
$ tools/config.py -m
//}

//comment{
コンフィグレーションの変更を書く。
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



=== コンフィグレーション要素について


== make

== 書き込み

== ゲームバイナリをSDカードにコピー

== シェルと接続
