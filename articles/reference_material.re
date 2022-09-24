= 参考資料

== BMI160 Datasheet
@<title>{electric_guitar}ではBMI160のジャイロで傾きを計測します。

BMI160のデータシートを参照しました。必要に応じて参照しました。

 * @<href>{https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi160-ds000.pdf,BMI160 Datasheet}


== ジャイロ（角速度）から角度の算出方法
@<title>{electric_guitar}ではBMI160のジャイロで角速度から角度を算出しています。

算出方法について参考にさせていただきました。

 * @<href>{https://garchiving.com/angular-from-angular-acceleration/,ジャイロ（角速度）から角度の算出方法}


== BMI160サンプルプログラム
@<title>{electric_guitar}ではBMI160から加速度・角速度を取得しています。
BMI160の制御についてつぎのコードを参考にさせていただきました。

コードはArduino向けに書かれていますが参考になりました。

 * @<href>{https://github.com/hanyazou/BMI160-Arduino/blob/master/examples/Gyro/Gyro.ino,BMI160サンプルプログラム}

== Spresense SDKでライブラリを追加する方法
つぎの2つのリンクが参考になりそうです。

 * @<href>{https://qiita.com/ixy-shino/items/9c778243365cad50a443,SPRESENSE SDKに独自の拡張機能を追加する【External Library】}

 * @<href>{https://ja.stackoverflow.com/questions/61027/spresense-sdk%e3%81%ab-static-library-a%e3%82%92%e8%bf%bd%e5%8a%a0%e3%81%99%e3%82%8b%e6%96%b9%e6%b3%95%e3%81%af,Spresense SDKに、Static Library (.a)を追加する方法は}


