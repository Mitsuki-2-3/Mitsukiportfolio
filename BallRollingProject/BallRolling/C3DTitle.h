#pragma once
#include"Camera.h"
#include"FloorManager.h"
#include"C3DSphere.h"
#include "AbstractScene.h"

class C3DTitle :
    public AbstractScene
{
private:
	FloorManager* floor;		//���ƕ�
	Camera* camera;				//�J����

	int selectNumber;			//���݂̑I��

public:
	C3DTitle();
	~C3DTitle();

	void Update() override;					//�X�V
	void Draw()const override;				//�`��
	AbstractScene* ChangeScene() override;	//�V�[���̑J��

};

