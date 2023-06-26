#include "C3DSphere.h"
#include "CheckHit.h"
#include <iostream>
#include <cmath>

C3DSphere::C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle)
{
	nowWorldPosi = firstposi;
	radius = _radius;

	localAngle = _angle;

	gravity = -0.1f;

	moveVector = VGet(0,0,0);

	test = (radius * 2.0f * float(M_PI)) / float(M_PI * 2);

	//なんちゃって摩擦のON/OFF
	friction = false;
	
	mHandle = MV1LoadModel("3D_Model/SphereModel.mv1");

	circumference = (_radius * 2.0f * (float)M_PI) / ((float)M_PI * 2.0f);
}

void C3DSphere::Updata()
{
	moveVector.y += gravity;

	//古い座標へ現在の移動量の加算
	nowWorldPosi += moveVector;

	MV1SetPosition(mHandle, nowWorldPosi);

	////なんちゃって摩擦
	if (friction) {
		moveVector -= moveVector * 0.02f;
	}

	////位置のリセット
	//if (KeyManager::OnKeyClicked(KEY_INPUT_Z))
	//{
	//	moveVector = VGet(0, 0, 0);
	//	nowWorldPosi = VGet(0, 265, 0);
	//}if (KeyManager::OnKeyClicked(KEY_INPUT_X))
	//{
	//	moveVector = VGet(0, 0, 0);
	//	nowWorldPosi = VGet(90, 65, 0);
	//}if (KeyManager::OnKeyClicked(KEY_INPUT_C))
	//{
	//	moveVector = VGet(0, 0, 0);
	//	nowWorldPosi = VGet(0, 65, 90);
	//}
	//if (nowWorldPosi.y < -550)
	//{
	//	moveVector = VGet(0, 0, 0);
	//	nowWorldPosi = VGet(0, 265, 0);
	//}
	////ボールスピード変更
	//if (KeyManager::OnKeyClicked(KEY_INPUT_SPACE))
	//{
	//	gravity -= 0.1;
	//}if (KeyManager::OnKeyClicked(KEY_INPUT_LSHIFT))
	//{
	//	if (gravity < -0.1)gravity += 0.1;
	//}
	////摩擦フラグ
	//if (KeyManager::OnKeyClicked(KEY_INPUT_L))
	//{
	//	friction = !friction;
	//}

	//回転処理(未完成)
	//ST_Angle local = {0,0,0};
	////VECTOR s = MoveRotation({0,-1,0},localAngle);
	//Quaternion test = { 0,0,0,0 };
	////Quaternion test = EulerAnglesToQuaternion(localAngle);
	////DrawSphere3D(nowWorldPosi + s * 20, 5, 32, 0xff00ff, 0x00ff00, TRUE);


	////VECTOR data = (MoveRotation(moveVector + nowWorldPosi,localAngle));
	//VECTOR data = ((moveVector));
	//Quaternion localqu = { 0,data.x,0,data.z };
	////localqu = (test.Reverse(M_PI_4) * localqu * test.Rotate(M_PI_4));
	//localqu = (test.Reverse(localqu.w) * localqu.Norm() * test.Rotate(localqu.w));

	//local = QuaternionToEulerAngles(localqu);

	//ResetAngle(&local.angleHor);
	//ResetAngle(&local.anglePar);
	//ResetAngle(&local.angleVer);

	//DrawFormatString(20, 20, 0xFFFFFF, "now:%f,%f,%f",
	//	local.angleHor, local.anglePar, local.angleVer);
	//DrawLine3D(nowWorldPosi, nowWorldPosi + MoveRotation(VGet(0, 1, 0), { localqu.v.z,localqu.v.x,localqu.v.y }) * 10, 0xFFFFFF);

	////localAngle += local;
	//localAngle += { localqu.v.x * 90.0f / 180.0f * float(M_PI),
	//	localqu.v.y * 90 / 180 * float(M_PI),
	//	localqu.v.z * 90 / 180 * float(M_PI) };
}

void C3DSphere::Draw() const
{
	//MV1DrawModel(mHandle);

	DrawSphere3D(nowWorldPosi, radius, 32, 0x0000FF, 0x00ff00, TRUE);
}

//壁との当たり判定処理
void C3DSphere::CheckHitWall(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };

	hit1 = Check3DQuadrangularPrism(data, this);
	//ここで当たり判定と当たった時の座標
	if (hit1.hit == true)
	{
		moveVector = VSub(moveVector, hit1.normalize * VDot(moveVector, hit1.normalize) * 1.15f);
		//ここでめり込み防止
		saves1 = (hit1.hitposi + hit1.normalize * (GetRadius() / 100.0f)) - nowWorldPosi;
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
		moveVector = VSub(moveVector, hit1.normalize * VDot(moveVector, hit1.normalize));
		//ここでめり込み防止
		saves1 = (hit1.hitposi) - nowWorldPosi;
		nowWorldPosi += saves1;
	}
}

bool C3DSphere::CheckHitItem(C3DPrism* data)
{
	//アイテムとの処理
	if (ItemCheck(data, this))
	{
		DrawString(200, 200, "HIT ITEM", 0xffffff);
		return true;
	}
	return false;
}

