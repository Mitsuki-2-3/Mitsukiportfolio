# Mitsukiportfolio

"Mitsukiportfolio"　は床を傾けてボールを転がしアイテムを取るゲームです。

# DEMO

↓の画像はタイトル画面です
![game 2023_06_02 13_25_39](https://github.com/Mitsuki-2-3/Mitsukiportfolio/assets/107020749/7b865ed2-d59d-490e-8984-a5c59fa981eb)

# Features

このゲームでは特に当たり判定に力を入れて制作し、3種類の当たり判定を作りました。

1つ目は、ポリゴンと球体

2つ目は、傾きのある立体と球体

3つ目は、傾きのない立体と球体(今回のゲームでは使いませんでしたが...)

の当たり判定を作りました。

# Requirement
* Dxlib (描画など)
プロジェクトに入れていますがもしなかった時には入れてください

# Installation
[dxlibのダウンロード(dxlib公式サイト引用)](https://dxlib.xsrv.jp/dxdload.html)

[dxlibの使用方法(dxlib公式サイト引用)](https://dxlib.xsrv.jp/dxuse.html)

# Usage
このリポジトリをダウンロード後、中にあるBallRollingGameファイルの中にあるexeファイルを起動してください。

操作方法：
	コントローラー(XINPUT形式)のスティック、または
	キーボードの矢印で床をを傾けることができます。
	コントローラーを使用する場合はコントローラーを接続し、
	exeを起動してください。

　床	：
	90fかけて最大の角度まで傾き、60fかけて戻ります。
	戻る時間は度の傾きでも60fかけて戻ります。
	ただし、傾けている間はほかの方向へは傾けれません。
	また、傾きが戻っている間はほかの方へ傾けることができます。

　壁　	：
	球が当たると少し跳ね返ります。

アイテム	：
	全て取ると画面が遷移します。

　球	：
	キーボードのLeftShitとSpaceで速さを調整できます。
	また、ボールにかかる摩擦をLでON/OFFできます。

カメラ	：
	AとDで床を中心に回転することができます。

 
＊お使いのウイルス対策ソフトによっては起動できない場合があります。

# Note
このゲームはXinput形式のコントローラーは対応していますが、DirectInput形式は対応していません。

BallRollingProjectはプロジェクトデータになります。
ソースファイルはこちらをご覧ください。

BallRollingGameはビルドデータになります。
ゲームの実行はこちらを開いてください。

# Author
*作成者　　

  yorino　　
  
*E-mail　　

　mitsuki-yorino-k21f@stu.kbc.ac.jp　　

# License
DX Library Copyright (C) 2001-2023 Takumi Yamada.

[License.txt](https://github.com/Mitsuki-2-3/Mitsukiportfolio/files/13555652/License.txt)

END 
