#pragma once
#include"DxLib.h"

#define AVERAGE_FPS 60 //平均を取るサンプル数
#define ATTACH_FLAME 60 //設定したFPS

class  FrameRateControll {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
public:
	FrameRateControll() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	void Update();

	void Draw();

	void Wait();
};

