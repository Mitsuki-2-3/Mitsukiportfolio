#include "C3DMain.h"
#include"GameClearScene.h"

//// シャドウマップハンドルの作成
//sHandle = MakeShadowMap(1024, 1024);
//// カメラの位置と向きを設定
//SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 800.0f, -800.0f), VGet(0.000f, 500.000f, 0.000f));
//// 描画する奥行き方向の範囲を設定
//SetCameraNearFar(40.000f, 10000.000f);

//// ライトの方向を設定
//SetLightDirection(VGet(D_Light_POSI_X, D_Light_POSI_Y, D_Light_POSI_Z));
//SetShadowMapLightDirection(sHandle,
//	VGet(D_Light_POSI_X, D_Light_POSI_Y, D_Light_POSI_Z));

//// シャドウマップの範囲を設定
//SetShadowMapDrawArea(sHandle,
//	VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

C3DMain::C3DMain()
{
	//カメラの動的確保
	camera = new Camera;

	//マネージャーの動的確保
	floor = new FloorManager(VGet(0, 30, 0), { 0,0,0 });

	//球の動的確保
	sphere = new C3DSphere(VGet(0, 65, 0),10, { 0,0,0});
}

void C3DMain::Update()
{
	//カメラの更新(ボールを追いかける)
	camera->Update(sphere);
	//床と壁とアイテムの更新
	floor->Updata();
	//球の更新
	sphere->Updata();

	//球と床の当たり判定
	sphere->CheckHitFloor(floor->GetPrismSpecity(0));

	//球と壁の当たり判定
	for (int i = 1; i < floor->GetPrismCount(); i++)
	{
		if (floor->GetPrismSpecity(i) != nullptr)
		{
			sphere->CheckHitWall(floor->GetPrismSpecity(i));
		}
	}

	//球とアイテムの当たり判定
	for (int i = 0; i < floor->GetItemCount(); i++)
	{
		if (floor->GetItemSpecity(i) != nullptr)
		{
			if (sphere->CheckHitItem(floor->GetItemSpecity(i)))
			{
				floor->DeleteItem(i);
			}
		}
	}
}

void C3DMain::Draw() const
{
	//床と壁とアイテムの描画
	floor->Draw();

	//球の描画
	sphere->Draw();

}

AbstractScene* C3DMain::ChangeScene()
{
	for (int i = 0; i < floor->GetItemCount(); i++)
	{
		if (floor->GetItemSpecity(i) != nullptr)
		{
			return this;
		}
	}

	return new GameClearScene;
}

//void C3DMain::drawXZPlane(int numOfMesh, float meshInterval, bool FillFlag)
//{
//	float width = numOfMesh * meshInterval;
//	float x0 = -width / 2.0f;
//	float z0 = x0;
//	unsigned int lineColor = GetColor(220, 220, 220);
//
//	DrawTriangle3D(VGet(x0, 0.0f, z0), VGet(x0, -0.0f, -z0), VGet(-x0, 0.0f, z0), GetColor(255, 255, 255), true);
//	DrawTriangle3D(VGet(-x0, 0.0f, -z0), VGet(x0, -0.0f, -z0), VGet(-x0, 0.0f, z0), GetColor(255, 255, 255), true);
//	lineColor = GetColor(220, 220, 220);
//
//
//	// 格子線を描写する。
//	for (int n = 0; n <= numOfMesh; n++) {// Z軸に平行な平行線分を書く。
//		float ratio = n / (1.0f * numOfMesh);
//		float offset = ratio * width;
//		DrawLine3D(VGet(x0 + offset, 0.0f, z0), VGet(x0 + offset, 0.0f, -z0), lineColor);
//	}
//	for (int n = 0; n <= numOfMesh; n++) {// X軸に平行な平行線分を書く。
//		float ratio = n / (1.0f * numOfMesh);
//		float offset = ratio * width;
//		DrawLine3D(VGet(x0, 0.0f, z0 + offset), VGet(-x0, 0.0f, z0 + offset), lineColor);
//	}
//}
