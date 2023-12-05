#pragma once
#include"DxLib.h"

#define AVERAGE_FPS 60.0f //平均を取るサンプル数
#define ATTACH_FLAME 60 //設定したFPS

//フレームレート固定用クラス
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

	void Update();		//更新

	void Draw();		//描画

	void Wait();		//フレームレートの固定
};

