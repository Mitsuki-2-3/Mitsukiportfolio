#include "FloorManager.h"

FloorManager::FloorManager(VECTOR _posi, ST_Angle _angle)
{
	localAngle = _angle;
	nowWorldPosi = _posi;

	prisms = new C3DPrism*[prismCount];
	items = new C3DPrism * [itemCount];

	//������
	for (int i = 0; i < prismCount; i++)
	{
		prisms[i] = nullptr;
	}
	for (int i = 0; i < itemCount; i++)
	{
		items[i] = nullptr;
	}

	float leng = 250;
	float hight = 20;

	VECTOR localposi = {};
	prisms[0] = new C3DPrism(nowWorldPosi, localposi,&localAngle, { 0.0f,0.0f,0.0f }, VGet(leng*2, hight,leng*2));
	localposi.y = 20;
	localposi.x = leng;
	prisms[1] = new C3DPrism(nowWorldPosi, localposi, &localAngle, { 0.0f,0.0f,0.0f }, VGet(hight/2, hight, leng * 2));
	localposi.x = -leng;
	prisms[2] = new C3DPrism(nowWorldPosi, localposi, &localAngle, { 0.0f,0.0f,0.0f }, VGet(hight/2, hight, leng * 2));
	localposi.x = 0;
	localposi.z = leng;
	prisms[3] = new C3DPrism(nowWorldPosi, localposi, &localAngle, { 0.0f,0.0f,0.0f }, VGet(leng * 2, hight, hight/2));
	localposi.z = -leng;
	prisms[4] = new C3DPrism(nowWorldPosi, localposi, &localAngle, { 0.0f,0.0f,0.0f }, VGet(leng * 2, hight, hight/2));

	localposi = nowWorldPosi;
	localposi.y = 20;
	localposi.x = 90;
	ST_Angle localangle = {};
	float itemangle = (float)M_PI * 2.f / 12.f;
	for (int i = 0; i < 12; i++)
	{
		items[i] = new C3DPrism(nowWorldPosi, MoveRotation(localposi, localangle), &localAngle, { 0.0f,(float)M_PI_4,(float)M_PI_4 }, VGet(10.0f, 10.0f, 10.0f));
		localangle.anglePar += itemangle;
	}

	for (int i = 0; i < 4; i++)
	{
		acce[i].flg = false;
		acce[i].acceleration = 0.0f;
	}
}

FloorManager::~FloorManager()
{
	delete prisms;
	delete items;
}

void FloorManager::Updata()
{
	// �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
	if (Controll::GetStick(D_STICK_L, D_CROSSKEY_RIGHT)
		|| KeyManager::OnKeyPressed(KEY_INPUT_RIGHT) && !acce[1].flg)
	{
		acce[0].flg = true;
		acce[0].acceleration = 0.0f; 
		if (localAngle.angleHor >= -D_TILT) {
			localAngle.angleHor -= D_ACCELERATION;
		}

		// �|30�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (localAngle.angleHor < -D_TILT)
		{
			localAngle.angleHor = -D_TILT;
		}
	}
	// �u���v�{�^����������Ă����琅���p�x���v���X����
	if (Controll::GetStick(D_STICK_L, D_CROSSKEY_LEFT)
		|| KeyManager::OnKeyPressed(KEY_INPUT_LEFT) && !acce[0].flg)
	{
		acce[1].flg = true;
		acce[1].acceleration = 0.0f;
		if (localAngle.angleHor <= D_TILT) {
			localAngle.angleHor += D_ACCELERATION;
		}

		// 30�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤��30�x�ɌŒ�
		if (localAngle.angleHor > D_TILT)
		{
			localAngle.angleHor = D_TILT;
		}
	}
	// �u���v�{�^����������Ă����琂���p�x���v���X����
	if (Controll::GetStick(D_STICK_L, D_CROSSKEY_UP)
		|| KeyManager::OnKeyPressed(KEY_INPUT_UP) && !acce[3].flg)
	{
		acce[2].flg = true;
		acce[2].acceleration = 0.0f;
		if (localAngle.angleVer >= -D_TILT) {
			localAngle.angleVer -= D_ACCELERATION;
		}

		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (localAngle.angleVer < -D_TILT)
		{
			localAngle.angleVer = -D_TILT;
		}
	}

	// �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
	if (Controll::GetStick(D_STICK_L, D_CROSSKEY_DOWN)
		|| KeyManager::OnKeyPressed(KEY_INPUT_DOWN) && !acce[2].flg)
	{
		acce[3].flg = true;
		acce[3].acceleration = 0.0f;
		if (localAngle.angleVer <= D_TILT) {
			localAngle.angleVer += D_ACCELERATION;
		}

		// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
		if (localAngle.angleVer > D_TILT)
		{
			localAngle.angleVer = D_TILT;
		}
	}

	//�{�^���܂��̓L�[�{�[�h�������ꂽ�猻�݂̌X������60���������p�x��ۑ�
	if (Controll::ReleaseStickAndCrossKey(D_STICK_L, D_CROSSKEY_RIGHT)
		|| KeyManager::OnKeyRelease(KEY_INPUT_RIGHT))
	{
		acce[0].acceleration = localAngle.angleHor / 60.0f;
	}
	if (Controll::ReleaseStickAndCrossKey(D_STICK_L, D_CROSSKEY_LEFT)
		|| KeyManager::OnKeyRelease(KEY_INPUT_LEFT))
	{
		acce[1].acceleration = localAngle.angleHor / 60.0f;
	}
	if (Controll::ReleaseStickAndCrossKey(D_STICK_L, D_CROSSKEY_DOWN)
		|| KeyManager::OnKeyRelease(KEY_INPUT_DOWN))
	{
		acce[3].acceleration = localAngle.angleVer / 60.0f;
	}
	if (Controll::ReleaseStickAndCrossKey(D_STICK_L, D_CROSSKEY_UP)
		|| KeyManager::OnKeyRelease(KEY_INPUT_UP))
	{
		acce[2].acceleration = localAngle.angleVer / 60.0f;
	}

	//�߂肷���Ȃ��悤�ɂ���
	if ((acce[0].acceleration < 0 || acce[1].acceleration > 0))
	{
		if (localAngle.angleHor != 0.0f) {
			if (localAngle.angleHor < -0.00001f)
			{
				localAngle.angleHor -= acce[0].acceleration;
				if (localAngle.angleHor >= acce[0].acceleration)
				{
					localAngle.angleHor = 0.0f;
					acce[0].acceleration = 0.0f;
					acce[0].flg = false;
				}
			}
			else if (localAngle.angleHor > 0.00001f)
			{
				localAngle.angleHor -= acce[1].acceleration;
				if (localAngle.angleHor <= acce[1].acceleration)
				{
					localAngle.angleHor = 0.0f;
					acce[1].acceleration = 0.0f;
					acce[1].flg = false;
				}
			}
		}
	}
	if (acce[2].acceleration < 0 || acce[3].acceleration > 0)
	{
		if (localAngle.angleVer != 0.0f) {
			if (localAngle.angleVer < -0.000001f)
			{
				localAngle.angleVer -= acce[2].acceleration;
				if (localAngle.angleVer >= acce[2].acceleration)
				{
					localAngle.angleVer = 0.0f;
					acce[2].acceleration = 0.0f;
					acce[2].flg = false;
				}
			}
			else if (localAngle.angleVer > 0.00001f)
			{
				localAngle.angleVer -= acce[3].acceleration;
				if (localAngle.angleVer <= acce[3].acceleration)
				{
					localAngle.angleVer = 0.0f;
					acce[3].acceleration = 0.0f;
					acce[3].flg = false;
				}
			}


		}
	}

	//60�������ꂽ�p�x��60�t���[�������Ė߂�
	for (int i = 0; i < 4; i++)
	{
		if (acce[i].flg == false) {
			acce[i].acceleration = acce[i].acceleration - (acce[i].acceleration / 60.0f);
		}
	}

	// �P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
	if (localAngle.angleVer > M_PI)localAngle.angleVer -= float(M_PI * 2);
	// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
	if (localAngle.angleVer < -M_PI)localAngle.angleVer += float(M_PI * 2);
	// �P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
	if (localAngle.angleHor > M_PI)localAngle.angleHor -= float(M_PI * 2);
	// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
	if (localAngle.angleHor < -M_PI)localAngle.angleHor += float(M_PI * 2);
	// �P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
	if (localAngle.anglePar > M_PI)localAngle.anglePar -= float(M_PI * 2);
	// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
	if (localAngle.anglePar < -M_PI)localAngle.anglePar += float(M_PI * 2);

	//�l�ʑ̂̍X�V
	for (int i = 0; i < prismCount; i++)
	{
		prisms[i]->Updata();
	}

	//�A�C�e���̍X�V
	for (int i = 0; i < itemCount; i++)
	{
		if (items[i] != nullptr)
		{
			items[i]->Updata();
		}
	}
}

void FloorManager::Draw() const
{
	//�l�ʑ̂̕`��
	for (int i = 1; i < 5; i++)
	{
		//�ǂ͔�
		prisms[i]->Draw(7);
	}
	//���͐�
	prisms[0]->Draw(5);

	//�A�C�e���̕`��
	for (int i = 0; i < itemCount; i++)
	{
		if (items[i] != nullptr)
		{
			items[i]->Draw(4);
		}
	}
}
