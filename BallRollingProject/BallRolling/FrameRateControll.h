#pragma once
#include"DxLib.h"

#define AVERAGE_FPS 60.0f //���ς����T���v����
#define ATTACH_FLAME 60 //�ݒ肵��FPS

//�t���[�����[�g�Œ�p�N���X
class  FrameRateControll {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
public:
	FrameRateControll() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	void Update();		//�X�V

	void Draw();		//�`��

	void Wait();		//�t���[�����[�g�̌Œ�
};

