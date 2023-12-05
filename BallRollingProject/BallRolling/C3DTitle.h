#pragma once
#include"Camera.h"
#include"FloorManager.h"
#include"C3DSphere.h"
#include "AbstractScene.h"

class C3DTitle :
    public AbstractScene
{
private:
	FloorManager* floor;		//床と壁
	Camera* camera;				//カメラ

	int selectNumber;			//現在の選択

public:
	C3DTitle();
	~C3DTitle();

	void Update() override;					//更新
	void Draw()const override;				//描画
	AbstractScene* ChangeScene() override;	//シーンの遷移

};

