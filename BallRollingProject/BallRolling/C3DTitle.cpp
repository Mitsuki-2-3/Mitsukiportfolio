#include "C3DTitle.h"
#include"DrawBoxUI.h"
#include"C3DMain.h"

C3DTitle::C3DTitle()
{
	selectNumber = 0;

	//カメラの動的確保
	camera = new Camera;

	//マネージャーの動的確保
	floor = new FloorManager(VGet(0, 30, 0), { 0,0,0 });
}

C3DTitle::~C3DTitle()
{
	delete floor;
	delete camera;
}

void C3DTitle::Update()
{
	//カメラの更新(ボールを追いかける)
	camera->Rotation();

	if (Controll::JustOnceStickAndCrossKey(D_STICK_L, D_CROSSKEY_UP)
		|| KeyManager::OnKeyClicked(KEY_INPUT_UP))
	{
		if (selectNumber - 1 > -1)
		{
			selectNumber -= 1;
		}
	}

	if (Controll::JustOnceStickAndCrossKey(D_STICK_L, D_CROSSKEY_DOWN)
		|| KeyManager::OnKeyClicked(KEY_INPUT_DOWN))
	{
		if (selectNumber + 1 < 2)
		{
			selectNumber += 1;
		}
	}
}

void C3DTitle::Draw() const
{
	//床と壁とアイテムの描画
	floor->Draw();

	SetFontSize(90);
	DrawString(500, 150, "球転がし", 0xFFFFFF, TRUE);
	SetFontSize(DEFAULT_FONT_SIZE);

	if (selectNumber == 0)
	{
		DrawBoxUI::DrawBoxUIString(680, 300, "START", 80, 0xff0000, 0x0000ff);
		DrawBoxUI::DrawBoxUIString(680, 400, "EXIT", 80, 0x0000ff, 0x0000ff);

	}
	if (selectNumber == 1)
	{
		DrawBoxUI::DrawBoxUIString(680, 300, "START", 80, 0x0000ff, 0x0000ff);
		DrawBoxUI::DrawBoxUIString(680, 400, "EXIT", 80, 0xff0000, 0x0000ff);
	}
}

AbstractScene* C3DTitle::ChangeScene()
{
	if (selectNumber == 0 &&
		(Controll::JudgePressButton(XINPUT_BUTTON_A) || KeyManager::OnKeyClicked(KEY_INPUT_Z)))
	{
		return new C3DMain();
	}
	if (selectNumber == 1 && 
		(Controll::JudgePressButton(XINPUT_BUTTON_A) || KeyManager::OnKeyClicked(KEY_INPUT_Z)))
	{
		return nullptr;
	}

	return this;
}
