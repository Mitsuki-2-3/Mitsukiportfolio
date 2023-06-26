#pragma once
#include"DxLib.h"

#define DEADZONE_STICK_ 23000
#define DEADZONE_TRIGGER 100
#define MIX_STICK 10000
#define STICK_LX 1
#define STICK_LY 2
#define STICK_RX 3
#define STICK_RY 4

#define D_STICK_L 0
#define D_STICK_R 1
#define D_STICK_X_PLUS 3
#define D_STICK_X_MINUS 2
#define D_STICK_Y_PLUS 1
#define D_STICK_Y_MINUS 0

#define D_TRIGGER_L 0
#define D_TRIGGER_R 1

#define D_CROSSKEY_RIGHT 3
#define D_CROSSKEY_LEFT	2
#define D_CROSSKEY_UP 1
#define D_CROSSKEY_DOWN 0

#define D_HOLD_TIME 10

//�ז��Ȃ�܂Ƃ߂�
typedef struct BoolControll_STICK_TRIGGER
{
	bool stick[2][4];
	bool triger[2];
} BoolControll;

class Controll
{
private:
	static XINPUT_STATE nowkey;		//���݂̓���
	static XINPUT_STATE oldkey;		//�Â�����
	static XINPUT_STATE keyflg;		//���݂̃L�[
	static float localAngle;		//�X�e�B�b�N����̃A���O��
	static BoolControll nowbool;		//���݂̓��͔���
	static BoolControll oldbool;		//�Â����͔���
	static BoolControll keybool;		//���݂̔���L�[
	static int stickTimer[8];		//�X�e�B�b�N���Ƃ̒��������ԕۑ�

	//�X�e�B�b�N�̔���(Private)
	static void PrivateStickJudge();
	//�g���K�[�̔���(Private)
	static void PrivateTriggerJudge();

public:
	Controll() = default;

	//���݂̃L�[�̎擾
	static XINPUT_STATE GetKey() { return nowkey; }

	//���݂̃{�^���i�`���^�i�V�j(���� : XINPUT_BUTTON_�`)
	static bool JudgeButton(unsigned int data) {
		if (nowkey.Buttons[data] == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	//���݂̃{�^���i�`���^�A���j(���� : XINPUT_BUTTON_�`)
	static bool JudgePressButton(unsigned int data) {
		if (keyflg.Buttons[data] == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	//���݂̃{�^���i�����[�X�j(���� : XINPUT_BUTTON_�`)
	static bool JudgeReleaseButton(unsigned int data) {
		if (oldkey.Buttons[data] == 1 && nowkey.Buttons[data] == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	//���݂̃X�e�B�b�N�̐��l(���� : STICK_�`)
	static short GetStickValue(int data) {
		switch (data)
		{
		case 1:
			return nowkey.ThumbLX;
			break;
		case 2:
			return nowkey.ThumbLY;
			break;
		case 3:
			return nowkey.ThumbRX;
			break;
		case 4:
			return nowkey.ThumbRY;
			break;
		default:
			break;
		}
		return short(-128);
	}

	//���݂̃g���K�[�̒l���Ƃ�(���� :  D_TRIGGER_�`)
	static unsigned char GetTrigger(int data) {
		switch (data)
		{
		case D_TRIGGER_L:
			return nowkey.LeftTrigger;
			break;
		case D_TRIGGER_R:
			return nowkey.RightTrigger;
			break;
		}
	}

	static unsigned char GetStick(int stick,int localAngle) {
		switch (stick)
		{
		case D_STICK_L:
			return nowbool.stick[D_STICK_L][localAngle];
			break;
		case D_STICK_R:
			return nowbool.stick[D_STICK_R][localAngle];
			break;
		}
		return 0x00;
	}

	//���݂̃X�e�B�b�N�̔���(����1 : D_STICK_�` , ����2 : D_STICK_�`)
	static bool JustOnceStick(int controll, int stick) {
		if ((0 <= controll && controll <= 1) && (0 <= stick && stick <= 3)) {
			return keybool.stick[controll][stick];
		}
		else {
			return false;
		}
	}

	//���݂̃g���K�[�̔���(���� :  D_TRIGGER_�`)
	static bool JustOnceTrigger(int trigger) {
		if (0 <= trigger && trigger <= 1) {
			return keybool.triger[trigger];
		}
		else {
			return false;
		}
	}

	//�X�e�B�b�N�Ə\���L�[��A��������PUSH(����1 : D_STICK_�` , ����2 : D_CROSSKEY_�`)
	static bool JustOnceStickAndCrossKey(int stick, int dic);

	//�X�e�B�b�N�Ə\���L�[��A��������RELEASE(����1 : D_STICK_�` , ����2 : D_CROSSKEY_�`)
	static bool ReleaseStickAndCrossKey(int stick, int dic);

	//���݂̃X�e�B�b�N����̃A���O��(���� : D_STICK_�`)
	static float GetNowAngle(unsigned int stick);

	static void Update();
};

typedef struct ST_BoolKeyBoard
{
	char Key;
	int timer;
} BoolKeyBoard;

class KeyManager
{
private:
	static char oldKey[256];
	static char nowKey[256];
	static BoolKeyBoard keyBoardFlg[256];

	static int oldMouse;
	static int nowMouse;
	static int keyMouse;

	KeyManager() = default;

public:
	static void Update();		//�L�[�̍X�V
	static bool OnKeyClicked(int key);		//�N���b�N�����Ƃ�
	static bool OnKeyRelease(int key);		//��������
	static bool OnKeyPressed(int key);		//�������Ƃ�
	static bool OnKeyKeepPress(int key);

	static bool OnMouseClicked(int key);
	static bool OnMouseRelease(int key);
	static bool OnMousePressed(int key);
};