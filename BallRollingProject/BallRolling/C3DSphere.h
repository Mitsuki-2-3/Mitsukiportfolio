#pragma once
#include"common.h"
#include"C3DPrism.h"

#define D_RADIAN 0.0174533f

class C3DSphere
{
private:
	VECTOR nowWorldPosi;
	VECTOR moveVector;

	ST_Angle localAngle;
	float radius;

	float test;

	float gravity;

	int mHandle;

	bool friction;

	float circumference;
public:
	C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle);

	void Updata();

	void Draw()const;

	VECTOR GetNowPosition() { return nowWorldPosi; }
	VECTOR GetMoveVector() { return moveVector; }
	void CheckHitWall(C3DPrism* data);
	void CheckHitFloor(C3DPrism* data);
	bool CheckHitItem(C3DPrism* data);
	float GetRadius() { return radius; }
	void SetNowPosi(VECTOR _data) { nowWorldPosi = _data; }
};

