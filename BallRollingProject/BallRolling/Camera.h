#pragma once
#include"common.h"
#include"C3DSphere.h"

#define D_CAMERA_HIGHT_POSI 400.0f

class Camera
{
private:
	float angleHei;		//�����p�x
	float angleVer;		//�����p�x
	VECTOR nowPosi;		//�J�����̌��ݒn
	VECTOR targetPosi;		//���Ă��钆�S�_

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

	void Update(C3DSphere * sphere);	//�X�V
	void Rotation();					//��](�^�C�g���V�[���ł̂ݎg�p)
};

