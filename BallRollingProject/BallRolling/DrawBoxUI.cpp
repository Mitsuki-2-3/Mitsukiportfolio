#include "DrawBoxUI.h"

//文字を囲う四角形の描画
void DrawBoxUI::DrawBoxUIString(int x, int y, const TCHAR* str, int fontSize, unsigned int backColor, unsigned int frontColor)
{
	// BOXを二つ作りそれの中に文字を入れる
	size_t len = strlen(str);
	int width = 0;
	int height = 0;
	int judgeJ = 0;
	int judgeI = 0;

	//改行があるかの確認
	if ((len - 1) /10 >= 1) {
		height =  (int)(1 + (len-1)/10)* fontSize;
		judgeI = (int)(1 + (len / 10));
	}
	else
	{
		height = fontSize;
		judgeI = 1;
	}
	if (len / 10 >= 1) {
		width = 10 * (fontSize - 10);
		judgeJ = 10;
	}
	else
	{
		width = ((int)len % 10) * (fontSize - 10);
		judgeJ = (int)len % 10;
	}

	//外枠のボックス
	DrawBox(x - (width / 2) - ((int)len / 3) -5, y - (height / 2) - ((int)len / 3) -5,
		x + (width / 2) + ((int)len / 5) +5, y + (height / 2) + ((int)len / 5) +5,
		backColor, TRUE);
	//内枠のボックス
	DrawBox(x - (width / 2) - ((int)len / 3), y - (height / 2) - ((int)len / 3),
		x + (width / 2) + ((int)len/5), y + (height / 2) + ((int)len / 5),
		frontColor, TRUE);

	//指定した大きさの文字を出力
	SetFontSize(fontSize);
	//行
	for (int i = 0; i < judgeI; i++)
	{
		if (len / 10 >= 1) {
			judgeJ = 10;
		}
		else
		{
			judgeJ = len % 10;
		}
		//列
		for (int j = 0; j < judgeJ; j++) {
			DrawFormatString(x - (width / 2)+j*(fontSize-fontSize/20), y - (height / 2)+ i* (fontSize - fontSize / 5), 0xffffff, "%c", str[(i*10)+j]);
		}
		len -= 10;
	}

	//デフォルトのフォントサイズに変更
	SetFontSize(DEFAULT_FONT_SIZE);
}

//長押しで長さの変わるバーの表示
void DrawBoxUI::DrawChargeBox(float x, float y, float width, float height, float value, unsigned int color, unsigned int type)
{
	if (type == 0) {
		//チャージバー
		DrawBoxAA(x - (width / 2.0f), y + (height / 2.0f) - value, x + (width / 2.0f), y + (height / 2.0f), color, TRUE);
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x + (width / 2.0f), y + (height / 2.0f), 0x000000, FALSE);
	}
	else if (type == 1) {
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x - (width / 2.0f) + value, y + (height / 2.0f), color, TRUE);
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x + (width / 2.0f), y + (height / 2.0f), 0x000000, FALSE);
	}
}
