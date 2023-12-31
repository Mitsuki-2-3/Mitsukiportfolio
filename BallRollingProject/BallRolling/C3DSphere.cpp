#include "C3DSphere.h"
#include "CheckHit.h"
#include <iostream>
#include <cmath>

C3DSphere::C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle)
{
	//座標
	nowWorldPosi = firstposi;
	//半径
	radius = _radius;
	//傾き
	localAngle = _angle;
	//重力
	gravity = -0.1f;
	//移動量の初期化
	moveVector = VGet(0,0,0);

	//なんちゃって摩擦のON/OFF
	friction = false;	
}

void C3DSphere::Updata()
{
	//移動量に重力の追加
	moveVector.y += gravity;

	//古い座標へ現在の移動量の加算
	nowWorldPosi += moveVector;

	////なんちゃって摩擦
	if (friction) {
		moveVector -= moveVector * 0.02f;
	}
}

void C3DSphere::Draw() const
{
	//球の描画
	DrawSphere3D(nowWorldPosi, radius, 32, 0x0000FF, 0x00ff00, TRUE);
}

//壁との当たり判定処理
void C3DSphere::CheckHitWall(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };
	//立方体との当たり判定
	hit1 = Check3DQuadrangularPrism(data, this);
	//ここで当たり判定と当たった時の座標
	if (hit1.hit == true)
	{
		//当たったら移動量を逆にして跳ね返す
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize) * 1.15f);
		//ここでめり込み防止
		saves1 = (hit1.hitposi + hit1.normalize * (GetRadius() / 100.0f)) - nowWorldPosi;
		//めり込んでる分戻す
		nowWorldPosi += saves1;
	}

}

//床との当たり判定処理
void C3DSphere::CheckHitFloor(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };

	hit1 = Check3DQuadrangularPrism(data, this);
	//ここで当たり判定と当たった時の座標
	if (hit1.hit == true)
	{
		//当たったら移動量を逆にする
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize));
		//ここでめり込み防止
		saves1 = (hit1.hitposi) - nowWorldPosi;
		//めり込んでる分戻す
		nowWorldPosi += saves1;
	}
}

bool C3DSphere::CheckHitItem(C3DPrism* data)
{
	//アイテムとの処理
	if (OBBPrism(data, this))
	{
		DrawString(200, 200, "HIT ITEM", 0xffffff);
		return true;
	}
	return false;
}

