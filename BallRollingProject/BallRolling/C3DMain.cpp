#include "C3DMain.h"
#include"GameClearScene.h"

C3DMain::C3DMain()
{
	//カメラの動的確保
	camera = new Camera;

	//マネージャーの動的確保
	floor = new FloorManager(VGet(0, 30, 0), { 0,0,0 });

	//球の動的確保
	sphere = new C3DSphere(VGet(0, 65, 0),10, { 0,0,0});
}

C3DMain::~C3DMain()
{
	delete camera;
	delete floor;
	delete sphere;
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
			//アイテムがあったら
			return this;
		}
	}
	//ゲーム中にアイテムが全部取られていたら
	return new GameClearScene;
}