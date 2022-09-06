
= ゲーム開発コンセプト
Spresenseでオリジナルゲームを作るにあたりつぎのコンセプトを考えました。

== プレイ環境
ゲームを楽しめる要素は何か?、
なぜファミコン・スーパーファミコンは流行したのか、を考えてみました。

結果、つぎの要素があると思いました。

 * 専用ハードウェアで遊べる
 * 共通の操作性で遊べる

=== 専用ハードウェアで遊べる
ファミコン・スーパーファミコンは専用ハードウェアを用意すればソフトウェアを入れ替えて遊べます。
またソフトウェアを持ち運べる、という特徴もあります。

今回のSpresenseを使ったオリジナルゲームもこれを実現したいと思いました。
Spresenseと後述するハードウェアを用意すればゲームをプレイできることを考えました。

=== 共通の操作性で遊べる
ゲーム機にはコントローラが付属しています。コントローラを通じてゲームを進行します。
コントローラがあればソフトウェアごとの振る舞いは変わりますがゲームができます。

今回のSpresenseを使ったオリジナルゲームではAPS学習ボードという基板を使うことで3つのゲームである程度同じ操作方法でゲームできることを考えて開発しました。


== コンセプトを実現するための技術要素
前述のコンセプトを実現するためにどのような技術要素を使っているか説明します。

=== NuttX, Spresense SDK
SpresenseはArduino, Spresense SDKの2つの実行環境で動かすことが可能です。
Spresense SDKは組込みリアルタイムOS NuttXをベースにして動きます。
Arduinoは電源ONでお馴染みのsetup, loop関数を実行します。
Spresense SDKは電源ONでシェルが起動し、実行するアプリケーションをユーザーが選択します。
今回3つのゲームをつくりましたが、ユーザーがプレイしたいゲームを選べる・任意のタイミングでゲームを終了し別なゲームをプレイする、というシーンを
考えた場合にSpresense SDKをゲームの実行環境にした方が適切だと思いました。
そういった理由からSpresense SDKでゲームを開発しました。


=== ローダブルELF
//footnote[loadable_elf_url][@<href>{https://developer.sony.com/develop/spresense/docs/sdk_tutorials_ja.html#_%E3%83%AD%E3%83%BC%E3%83%80%E3%83%96%E3%83%ABelf%E3%83%81%E3%83%A5%E3%83%BC%E3%83%88%E3%83%AA%E3%82%A2%E3%83%AB, ローダブルELF 参考URL}]
ローダブルELF@<fn>{loadable_elf_url}とは【OSとアプリケーションを別々のバイナリで作成し、動作時にアプリケーションをロードして実行できる機能】です。
3つのゲームを別々のバイナリにしてSDカードに保存し、ゲームするときはシェルから実行するようにしたいと思いました。
この機能を使うことで@<hd>{concept|専用ハードウェアで遊べる}に書いた【Spresenseを用意すればソフトウェアを持ち運べる】のコンセプトを達成することができます。


== ハードウェア
今回作った3つのゲームで共通で使用するハードウェアはつぎのとおりです。
各ゲームでのみ使用するハードウェアはゲームの章で別途説明します。

=== Spresenseメインボード
//footnote[spresense_main_url][@<href>{https://developer.sony.com/develop/spresense/docs/introduction_ja.html#_spresense_%E3%83%A1%E3%82%A4%E3%83%B3%E3%83%9C%E3%83%BC%E3%83%89, Spresenseメインボード 参考URL}]
プロセッサCXD5602が搭載されているボードです@<fn>{spresense_main_url}。

=== Spresense拡張ボード
//footnote[spresense_ex_url][@<href>{https://developer.sony.com/develop/spresense/docs/introduction_ja.html#_spresense_%E6%8B%A1%E5%BC%B5%E3%83%9C%E3%83%BC%E3%83%89, Spresense拡張ボード 参考URL}]
Spresense拡張ボード@<fn>{spresense_ex_url}はArduino Uno互換のピンソケットに加えて次の端子があります。

 * ヘッドホンジャック
 * micro SD カードスロット
 * USB コネクタ
 * マイク接続用ピンヘッダー

=== APS学習ボード
//footnote[aps_study_url][@<href>{https://www.aps-web.jp/academy/amp/8467/, APS学習ボード 参考URL}]
//footnote[aps_study_buy_url][@<href>{https://www.chip1stop.com/view/dispDetail/DispDetail?partId=APS1-0000001, APS学習ボード購入先 参考URL}]

APS学習ボード@<fn>{aps_study_url}はSpresense拡張ボードにスタックして使うボードです。
ボードにつぎのデバイスを搭載可能です。

 * LED 2個
 * タクトスイッチ 2個
 * アナログコンデンサマイク 4個
 * ILI9341 2.2インチLCD
 * リセット用タクトスイッチ 

今回のゲームではLED、タクトスイッチを使います。

現在だとchip1stop@<fn>{aps_study_buy_url}から購入可能です。実装部品は別途購入する必要があります。
