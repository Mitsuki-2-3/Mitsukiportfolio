#pragma once
#include"DxLib.h"
#include<iostream>
#include<string>

using namespace std;

class DrawBoxUI
{
public:

	/*DrawBoxUIString(int x, int y, string str, int fontSize, int backColor, int frontColor)
	座標X,Y　文字列(英字のみ)　フォントサイズ　ボックスの背景　ボックスの前面色　*/
	static void DrawBoxUIString(int x, int y, const TCHAR* str, int fontSize, unsigned int backColor, unsigned int frontColor);

	/*DrawChargeBox(float x, float y, float width, float height, float value, unsigned int color, unsigned int type)
	座標X,Y　大きさWidth,Height　ChargeValue　色　縦横のタイプ(0:縦 1:横)*/
	static void DrawChargeBox(float x,float y,float width,float height,float value,unsigned int color,unsigned int type);

};

