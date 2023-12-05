#pragma once
#include"common.h"
#include"C3DSphere.h"

#define D_CAMERA_HIGHT_POSI 400.0f

class Camera
{
private:
	float angleHei;		//水平角度
	float angleVer;		//垂直角度
	VECTOR nowPosi;		//カメラの現在地
	VECTOR targetPosi;		//見ている中心点

public:
	float GetAngleHeight() { return angleHei; }
	void SetAngleHeight(float _angleHei) { angleHei = _angleHei; }
	float GetAngleVer() { return angleVer; }
	void SetAngleVer(float _angleVer) { angleVer = _angleVer; }
	VECTOR GetNowPosi() { return nowPosi; }
	void SetNowPosi(VECTOR _nowposi) { nowPosi = _nowposi; }
	VECTOR GetTargetPosi() { return targetPosi; }
	void SetTargetPosi(VECTOR _targetposi) { targetPosi = _targetposi; }
public:
	Camera();

	void Update(C3DSphere * sphere);	//更新
	void Rotation();					//回転(タイトルシーンでのみ使用)
};

