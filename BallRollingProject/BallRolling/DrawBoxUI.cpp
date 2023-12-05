#include "DrawBoxUI.h"

//�������͂��l�p�`�̕`��
void DrawBoxUI::DrawBoxUIString(int x, int y, const TCHAR* str, int fontSize, unsigned int backColor, unsigned int frontColor)
{
	// BOX����肻��̒��ɕ���������
	size_t len = strlen(str);
	int width = 0;
	int height = 0;
	int judgeJ = 0;
	int judgeI = 0;

	//���s�����邩�̊m�F
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

	//�O�g�̃{�b�N�X
	DrawBox(x - (width / 2) - ((int)len / 3) -5, y - (height / 2) - ((int)len / 3) -5,
		x + (width / 2) + ((int)len / 5) +5, y + (height / 2) + ((int)len / 5) +5,
		backColor, TRUE);
	//���g�̃{�b�N�X
	DrawBox(x - (width / 2) - ((int)len / 3), y - (height / 2) - ((int)len / 3),
		x + (width / 2) + ((int)len/5), y + (height / 2) + ((int)len / 5),
		frontColor, TRUE);

	//�w�肵���傫���̕������o��
	SetFontSize(fontSize);
	//�s
	for (int i = 0; i < judgeI; i++)
	{
		if (len / 10 >= 1) {
			judgeJ = 10;
		}
		else
		{
			judgeJ = len % 10;
		}
		//��
		for (int j = 0; j < judgeJ; j++) {
			DrawFormatString(x - (width / 2)+j*(fontSize-fontSize/20), y - (height / 2)+ i* (fontSize - fontSize / 5), 0xffffff, "%c", str[(i*10)+j]);
		}
		len -= 10;
	}

	//�f�t�H���g�̃t�H���g�T�C�Y�ɕύX
	SetFontSize(DEFAULT_FONT_SIZE);
}

//�������Œ����̕ς��o�[�̕\��
void DrawBoxUI::DrawChargeBox(float x, float y, float width, float height, float value, unsigned int color, unsigned int type)
{
	if (type == 0) {
		//�`���[�W�o�[
		DrawBoxAA(x - (width / 2.0f), y + (height / 2.0f) - value, x + (width / 2.0f), y + (height / 2.0f), color, TRUE);
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x + (width / 2.0f), y + (height / 2.0f), 0x000000, FALSE);
	}
	else if (type == 1) {
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x - (width / 2.0f) + value, y + (height / 2.0f), color, TRUE);
		DrawBoxAA(x - (width / 2.0f), y - (height / 2.0f), x + (width / 2.0f), y + (height / 2.0f), 0x000000, FALSE);
	}
}
