#include "C3DMain.h"
#include"GameClearScene.h"

C3DMain::C3DMain()
{
	//�J�����̓��I�m��
	camera = new Camera;

	//�}�l�[�W���[�̓��I�m��
	floor = new FloorManager(VGet(0, 30, 0), { 0,0,0 });

	//���̓��I�m��
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
			//�A�C�e������������
			return this;
		}
	}
	//�Q�[�����ɃA�C�e�����S������Ă�����
	return new GameClearScene;
}