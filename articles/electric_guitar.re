
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


== Tips

== 課題

