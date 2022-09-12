
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
//comment{
TODO: プレイ画面・動画リンクを書く。
//}
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
Attention: module[11][0] attention id[1]/code[20] (components/decoder/decoder_component.cpp L511)
Attention!! components/decoder/dAttention: module[11][0] attention id[1]/code[20] (components/decoder/decoder_component.cpp L511)
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


== 操作方法

== Tips

== 課題

== 発展
