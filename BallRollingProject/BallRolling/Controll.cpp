#include "Controll.h"
#include <math.h>

XINPUT_STATE Controll::nowkey{};
XINPUT_STATE Controll::oldkey{};
XINPUT_STATE Controll::keyflg{};
float Controll::localAngle = 0;
BoolControll Controll::nowbool{};
BoolControll Controll::oldbool{};
BoolControll Controll::keybool{};
int Controll::stickTimer[8] = { 0 };
char KeyManager::oldKey[256] = { 0 };
char KeyManager::nowKey[256] = { 0 };
BoolKeyBoard KeyManager::keyBoardFlg[256] = { 0 };
int KeyManager::oldMouse = 0;
int KeyManager::nowMouse = 0;



void Controll::PrivateStickJudge()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			switch (i)
			{
			case D_STICK_L:
				switch (j)
				{
				case D_STICK_X_PLUS:
					if (nowkey.ThumbLX >= DEADZONE_STICK_)
					{
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_X_MINUS:
					if (nowkey.ThumbLX <= -DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_Y_PLUS:
					if (nowkey.ThumbLY >= DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_Y_MINUS:
					if (nowkey.ThumbLY <= -DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				}
				break;
			case D_STICK_R:
				switch (j)
				{
				case D_STICK_X_PLUS:
					if (nowkey.ThumbRX >= DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_X_MINUS:
					if (nowkey.ThumbRX <= -DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_Y_PLUS:
					if (nowkey.ThumbRY <= -DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				case D_STICK_Y_MINUS:
					if (nowkey.ThumbRY >= DEADZONE_STICK_) {
						nowbool.stick[i][j] = true;
						break;
					}
					nowbool.stick[i][j] = false;
					break;
				}
				break;
			}
		}
	}
}

void Controll::PrivateTriggerJudge()
{
	for (int i = 0; i < 2; i++) {
		switch (i)
		{
		case D_TRIGGER_L:
			if (nowkey.LeftTrigger >= DEADZONE_TRIGGER) {
				nowbool.triger[i] = true;
				break;
			}
			nowbool.triger[i] = false;
			break;
		case D_TRIGGER_R:
			if (nowkey.RightTrigger >= DEADZONE_TRIGGER) {
				nowbool.triger[i] = true;
				break;
			}
			nowbool.triger[i] = false;
			break;
		}
	}
}

bool Controll::JustOnceStickAndCrossKey(int stick, int dic)
{
	if (JudgePressButton(dic) || keybool.stick[stick][dic]) {
		return true;
	}
	else {
		return false;
	}
}

bool Controll::ReleaseStickAndCrossKey(int stick, int dic)
{
	if (JudgeReleaseButton(dic) || (!nowbool.stick[stick][dic] && oldbool.stick[stick][dic])) {
		return true;
	}
	else {
		return false;
	}
}

float Controll::GetNowAngle(unsigned int stick)
{
	switch (stick)
	{
	case D_STICK_L:
		if ((nowkey.ThumbLX >= DEADZONE_STICK_ || nowkey.ThumbLX <= -DEADZONE_STICK_)
			|| (nowkey.ThumbLY >= DEADZONE_STICK_ || nowkey.ThumbLY <= -DEADZONE_STICK_)) {
			localAngle = atan2f(nowkey.ThumbLY * -1.0f, nowkey.ThumbLX);
		}
		else {
			localAngle = atan2f(0, 0);
		}
		break;
	case D_STICK_R:
		if ((nowkey.ThumbLX >= DEADZONE_STICK_ || nowkey.ThumbLX <= -DEADZONE_STICK_)
			|| (nowkey.ThumbLY >= DEADZONE_STICK_ || nowkey.ThumbLY <= -DEADZONE_STICK_)) {
			localAngle = atan2f(nowkey.ThumbLY * -1.0f, nowkey.ThumbLX);
		}
		else {
			localAngle = atan2f(0, 0);
		}
		break;
	}

	return localAngle;
}

void Controll::Update()
{
	//ここで古いボタンの更新
	for (int i = 0; i < 16; i++) {
		oldkey.Buttons[i] = nowkey.Buttons[i];
	}

	//新しいコントローラの値更新
	GetJoypadXInputState(DX_INPUT_PAD1, &nowkey);

	//ここでコントローラーの値を更新
	if (nowkey.ThumbLX >= DEADZONE_STICK_ || nowkey.ThumbLY >= DEADZONE_STICK_ ||
		nowkey.ThumbLX <= -DEADZONE_STICK_ || nowkey.ThumbLY <= -DEADZONE_STICK_) {
		oldkey.ThumbLX = nowkey.ThumbLX;
		oldkey.ThumbLY = nowkey.ThumbLY;
	}
	else {
		oldkey.ThumbLX = 128;
		oldkey.ThumbLY = 128;

	}

	//ここでトリガーの更新
	for (int i = 0; i < 2; i++) {
		switch (i)
		{
		case D_TRIGGER_L:
			if (nowkey.LeftTrigger >= DEADZONE_TRIGGER) {
				oldkey.LeftTrigger = nowkey.LeftTrigger;
				break;
			}
			else {
				oldkey.LeftTrigger = 0;
			}

		case D_TRIGGER_R:
			if (nowkey.RightTrigger >= DEADZONE_TRIGGER) {
				oldkey.RightTrigger = nowkey.RightTrigger;
				break;
			}
			else {
				oldkey.LeftTrigger = 0;
			}
		}
	}

	//ここでスティックのフラグをoldに上書き
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			oldbool.stick[i][j] = nowbool.stick[i][j];
		}
	}


	//複数入力の阻止変数に値を更新
	for (int i = 0; i < 16; i++) {
		keyflg.Buttons[i] = nowkey.Buttons[i] & ~oldkey.Buttons[i];
	}




	//ここでスティックのフラグをnowに更新
	PrivateStickJudge();
	//ここで複数入力の阻止変数の値を更新
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			//ここで長押ししてる時の処理
			if (nowbool.stick[i][j] && !oldbool.stick[i][j]
				|| stickTimer[i * 4 + j] >= D_HOLD_TIME) {
				keybool.stick[i][j] = true;
				stickTimer[i * 4 + j] = 0;

			}
			//長押しの加算
			else if (nowbool.stick[i][j]) {
				stickTimer[i * 4 + j] += 1;
				keybool.stick[i][j] = false;
			}
			//何も押されてないとき
			else {
				stickTimer[i * 4 + j] = 0;
				keybool.stick[i][j] = false;
			}
		}
	}

	//ここでトリガーのフラグをoldに上書き
	for (int i = 0; i < 2; i++) {
		oldbool.triger[i] = nowbool.triger[i];
	}
	//ここでトリガーのフラグをnowに更新
	PrivateTriggerJudge();
	//ここで複数入力の阻止変数の値を更新
	for (int i = 0; i < 2; i++) {
		if (nowbool.triger[i] && !oldbool.triger[i]) {
			keybool.triger[i] = true;
		}
		else
		{
			keybool.triger[i] = false;
		}
	}
}

void KeyManager::Update()
{
	oldMouse = nowMouse;
	nowMouse = GetMouseInput();

	for (int i = 0; i < 256; i++) {
		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1) {
		throw - 1;
	}

	//ここで複数入力の阻止変数の値を更新
	for (int i = 0; i < 256; i++) {
		//ここで長押ししてる時の処理
		if (nowKey[i] && !oldKey[i]) {
			keyBoardFlg[i].Key = 1;
			keyBoardFlg[i].timer = -D_HOLD_TIME;

		}
		//長押しの加算
		else if (nowKey[i]) {
			keyBoardFlg[i].Key = 0;
			keyBoardFlg[i].timer += 5;
			if (keyBoardFlg[i].timer >= D_HOLD_TIME) {
				keyBoardFlg[i].Key = 1;
				keyBoardFlg[i].timer = D_HOLD_TIME / 2;
			}
		}
		//何も押されてないとき
		else {
			keyBoardFlg[i].Key = 0;
			keyBoardFlg[i].timer = 0;
		}
	}

}

bool KeyManager::OnKeyClicked(int key)
{
	//if (nowKey[key] == 1 && oldKey[key] != 1) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	bool ret = ((nowKey[key] == 1 && oldKey[key] != 1));

	return ret;
}

bool KeyManager::OnKeyRelease(int key)
{
	//if (nowKey[key] != 1 && oldKey[key] == 1) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	bool ret = ((nowKey[key] != 1 && oldKey[key] == 1));

	return ret;
}

bool KeyManager::OnKeyPressed(int key)
{
	//if (nowKey[key] == 1 && oldKey[key] != 1) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	bool ret = (nowKey[key] == 1);

	return ret;
}

bool KeyManager::OnKeyKeepPress(int key)
{
	bool ret = (keyBoardFlg[key].Key == 1);

	return ret;
}

bool KeyManager::OnMouseClicked(int key)
{
	bool ret = ((nowMouse & key) != 0 && (oldMouse & key) == 0);

	return ret;
}

bool KeyManager::OnMouseRelease(int key)
{
	bool ret = ((nowMouse & key) == 0 && (oldMouse & key) != 0);

	return ret;
}

bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);

	return ret;
}