#pragma once
#include"Camera.h"
#include"FloorManager.h"
#include"C3DSphere.h"
#include "AbstractScene.h"

class C3DTitle :
    public AbstractScene
{
private:
	int sHandle;
	FloorManager* floor;
	Camera* camera;

	int selectNumber;

public:
	C3DTitle();
	~C3DTitle();

	void Update() override;
	void Draw()const override;
	AbstractScene* ChangeScene() override;

};

