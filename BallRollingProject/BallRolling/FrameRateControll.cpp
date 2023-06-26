#include "FrameRateControll.h"

void FrameRateControll::Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();		//最初の時間
	}
	if (mCount == AVERAGE_FPS) { //60フレーム目なら平均を計算する
		int t = GetNowCount();		//現在までの時間
		mFps = 1000.0f / ((t - mStartTime) / (float)AVERAGE_FPS);		//現在のFPSの計算
		mCount = 0;		//フレームのリセット
		mStartTime = t;		//0フレーム目の設定
	}
	mCount++;		//毎フレーム加算
}

void  FrameRateControll::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void  FrameRateControll::Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間	
	int waitTime = mCount * 1000 / ATTACH_FLAME - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//waitTimeが1以上なら待機
	}
}