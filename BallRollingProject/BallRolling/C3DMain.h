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
	FloorManager* floor;	//���ƕ�
	C3DSphere* sphere;		//��
	Camera* camera;			//�J����

public:
	C3DMain();
	~C3DMain();

	void Update() override;						//�X�V
	void Draw()const override;					//�`��
	AbstractScene * ChangeScene() override;		//�V�[���̑J��
};

