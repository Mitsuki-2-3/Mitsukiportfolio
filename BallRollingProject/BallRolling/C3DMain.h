#pragma once
#include"AbstractScene.h"
#include"Camera.h"
#include"FloorManager.h"
#include"C3DSphere.h"

#define D_Light_POSI_X 0.5f
#define D_Light_POSI_Y -500.5f
#define D_Light_POSI_Z 100.5f

class C3DMain	: public AbstractScene
{
private:
	FloorManager* floor;	//床と壁
	C3DSphere* sphere;		//球
	Camera* camera;			//カメラ

public:
	C3DMain();
	~C3DMain();

	void Update() override;						//更新
	void Draw()const override;					//描画
	AbstractScene * ChangeScene() override;		//シーンの遷移
};

