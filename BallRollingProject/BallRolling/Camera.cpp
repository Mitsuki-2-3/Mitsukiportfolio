#include "Camera.h"

Camera::Camera()
{
	angleHei = 0.0f;
	angleVer = (float)-M_PI_4;
	// カメラの注視点は固定座標から規定値分高い座標
	targetPosi = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));

	MATRIX RotZ, RotY;

	// 水平方向の回転はＹ軸回転
	RotY = MGetRotY(angleHei);

	// 垂直方向の回転はＺ軸回転 )
	RotZ = MGetRotZ(angleVer);

	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
	// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
	// 注視点の座標を足したものがカメラの座標
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//カメラ位置のセット
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);

}

void Camera::Update(C3DSphere* sphere)
{
	MATRIX RotZ, RotY;		//行列計算用

	targetPosi = VAdd(VGet(sphere->GetNowPosition().x, 0.0f, sphere->GetNowPosition().z), VGet(0.0f, 0.0f, 0.0f));

	if (KeyManager::OnKeyPressed(KEY_INPUT_A))
	{
		angleHei += 0.1f;
	}
	if (KeyManager::OnKeyPressed(KEY_INPUT_D))
	{
		angleHei -= 0.1f;
	}
	// 水平方向の回転はＹ軸回転
	RotY = MGetRotY(angleHei);
	// 垂直方向の回転はＺ軸回転 )
	RotZ = MGetRotZ(angleVer);
	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを:::VGet(-Camera_Player_Length, 10.0f, 0.0f)
	// 垂直方向回転( Ｚ軸回転 )させたあと:::VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ)
	// 水平方向回転( Ｙ軸回転 )して :::VTransform(VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ), RotY)
	// 注視点の座標を足したものがカメラの座標:::VAdd~
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//カメラの位置を新しい座標にセット
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);
}

void Camera::Rotation()
{
	MATRIX RotZ, RotY;		//行列計算用

	targetPosi = VAdd(VGet(0, 0, 0), VGet(0.0f, 0.0f, 0.0f));

	angleHei += 0.01f;

	// 水平方向の回転はＹ軸回転
	RotY = MGetRotY(angleHei);

	// 垂直方向の回転はＺ軸回転 )
	RotZ = MGetRotZ(angleVer);
	// カメラの座標を算出
	// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを:::VGet(-Camera_Player_Length, 10.0f, 0.0f)
	// 垂直方向回転( Ｚ軸回転 )させたあと:::VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ)
	// 水平方向回転( Ｙ軸回転 )して :::VTransform(VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ), RotY)
	// 注視点の座標を足したものがカメラの座標:::VAdd~
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//カメラの位置を新しい座標にセット
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);
}

