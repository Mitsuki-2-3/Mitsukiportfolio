#include "GameClearScene.h"
#include"C3DTitle.h"

//虹色
Rainbow Rainbowpalette[7] = {
	{250,0,0},
	{250,120,0},
	{250,210,0},
	{0,250,100},
	{0,180,250},
	{0,100,200},
	{180,0,150}
};

GameClearScene::GameClearScene()
{
	current = 0;
	color = Rainbowpalette[current];
}

void GameClearScene::Update()
{
	//色の変化
	if (color == Rainbowpalette[current]) {
		//次の色の配列に変更
		if (++current > 6) {
			current = 0;
		}
	}
	else {
		//現在の色から次の色に近づける
		if (color.red > Rainbowpalette[current].red) {
			color.red -= 10;
		}
		else if (color.red < Rainbowpalette[current].red) {
			color.red += 10;
		}

		if (color.green > Rainbowpalette[current].green) {
			color.green -= 10;
		}
		else if (color.green < Rainbowpalette[current].green) {
			color.green += 10;
		}

		if (color.blue > Rainbowpalette[current].blue) {
			color.blue -= 10;
		}
		else if (color.blue < Rainbowpalette[current].blue) {
			color.blue += 10;
		}
	}
}

void GameClearScene::Draw() const
{
	SetFontSize(32);
	DrawString(390, 200, "ゲームクリア！！", GetColor(color.red,color.green,color.blue));
	DrawString(200, 300, "キーボードのSPACEかコントローラーのAボタンでゲームに戻る", GetColor(color.red,color.green,color.blue));
	SetFontSize(DEFAULT_FONT_SIZE);

}

AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE)
		||Controll::JudgePressButton(XINPUT_BUTTON_A)) {
		//キーボードのスペースかコントローラーのAを押したら
		return new C3DTitle;
	}
	return this;
}
