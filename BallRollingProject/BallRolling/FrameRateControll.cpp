#include "FrameRateControll.h"

void FrameRateControll::Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();		//�ŏ��̎���
	}
	if (mCount == AVERAGE_FPS) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();		//���݂܂ł̎���
		mFps = 1000.0f / ((t - mStartTime) / (float)AVERAGE_FPS);		//���݂�FPS�̌v�Z
		mCount = 0;		//�t���[���̃��Z�b�g
		mStartTime = t;		//0�t���[���ڂ̐ݒ�
	}
	mCount++;		//���t���[�����Z
}

void  FrameRateControll::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void  FrameRateControll::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������	
	int waitTime = mCount * 1000 / ATTACH_FLAME - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//waitTime��1�ȏ�Ȃ�ҋ@
	}
}