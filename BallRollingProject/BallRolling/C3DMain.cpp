#include "C3DMain.h"
#include"GameClearScene.h"

//// �V���h�E�}�b�v�n���h���̍쐬
//sHandle = MakeShadowMap(1024, 1024);
//// �J�����̈ʒu�ƌ�����ݒ�
//SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 800.0f, -800.0f), VGet(0.000f, 500.000f, 0.000f));
//// �`�悷�鉜�s�������͈̔͂�ݒ�
//SetCameraNearFar(40.000f, 10000.000f);

//// ���C�g�̕�����ݒ�
//SetLightDirection(VGet(D_Light_POSI_X, D_Light_POSI_Y, D_Light_POSI_Z));
//SetShadowMapLightDirection(sHandle,
//	VGet(D_Light_POSI_X, D_Light_POSI_Y, D_Light_POSI_Z));

//// �V���h�E�}�b�v�͈̔͂�ݒ�
//SetShadowMapDrawArea(sHandle,
//	VGet(-1000.0f, -1.0f, -1000.0f), VGet(1000.0f, 1000.0f, 1000.0f));

C3DMain::C3DMain()
{
	//�J�����̓��I�m��
	camera = new Camera;

	//�}�l�[�W���[�̓��I�m��
	floor = new FloorManager(VGet(0, 30, 0), { 0,0,0 });

	//���̓��I�m��
	sphere = new C3DSphere(VGet(0, 65, 0),10, { 0,0,0});
}

void C3DMain::Update()
{
	//�J�����̍X�V(�{�[����ǂ�������)
	camera->Update(sphere);
	//���ƕǂƃA�C�e���̍X�V
	floor->Updata();
	//���̍X�V
	sphere->Updata();

	//���Ə��̓����蔻��
	sphere->CheckHitFloor(floor->GetPrismSpecity(0));

	//���ƕǂ̓����蔻��
	for (int i = 1; i < floor->GetPrismCount(); i++)
	{
		if (floor->GetPrismSpecity(i) != nullptr)
		{
			sphere->CheckHitWall(floor->GetPrismSpecity(i));
		}
	}

	//���ƃA�C�e���̓����蔻��
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
	//���ƕǂƃA�C�e���̕`��
	floor->Draw();

	//���̕`��
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
//	// �i�q����`�ʂ���B
//	for (int n = 0; n <= numOfMesh; n++) {// Z���ɕ��s�ȕ��s�����������B
//		float ratio = n / (1.0f * numOfMesh);
//		float offset = ratio * width;
//		DrawLine3D(VGet(x0 + offset, 0.0f, z0), VGet(x0 + offset, 0.0f, -z0), lineColor);
//	}
//	for (int n = 0; n <= numOfMesh; n++) {// X���ɕ��s�ȕ��s�����������B
//		float ratio = n / (1.0f * numOfMesh);
//		float offset = ratio * width;
//		DrawLine3D(VGet(x0, 0.0f, z0 + offset), VGet(-x0, 0.0f, z0 + offset), lineColor);
//	}
//}
