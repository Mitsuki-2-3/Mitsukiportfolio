#pragma once
#include"common.h"
#include"C3DPrism.h"

#define D_RADIAN 0.0174533f

class C3DSphere
{
private:
	VECTOR nowWorldPosi;		//座標
	VECTOR moveVector;			//移動量

	ST_Angle localAngle;		//傾き(試作中)
	float radius;				//半径

	float gravity;				//重力

	bool friction;				//摩擦(笑)のON/OFF
public:
	C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle);

	void Updata();			//更新

	void Draw()const;		//描画

	VECTOR GetNowPosition() { return nowWorldPosi; }			//座標の取得
	VECTOR GetMoveVector() { return moveVector; }				//移動量の取得
	void CheckHitWall(C3DPrism* data);							//壁との当たり判定処理
	void CheckHitFloor(C3DPrism* data);							//床との当たり判定処理
	bool CheckHitItem(C3DPrism* data);							//アイテム取得処理
	float GetRadius() { return radius; }						//半径の取得
	void SetNowPosi(VECTOR _data) { nowWorldPosi = _data; }		//座標の上書き
};

