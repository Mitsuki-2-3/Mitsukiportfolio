#include "Camera.h"

Camera::Camera()
{
	angleHei = 0.0f;
	angleVer = (float)-M_PI_4;
	// �J�����̒����_�͌Œ���W����K��l���������W
	targetPosi = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));

	MATRIX RotZ, RotY;

	// ���������̉�]�͂x����]
	RotY = MGetRotY(angleHei);

	// ���������̉�]�͂y����] )
	RotZ = MGetRotZ(angleVer);

	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
	// ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
	// �����_�̍��W�𑫂������̂��J�����̍��W
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//�J�����ʒu�̃Z�b�g
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);

}

void Camera::Update(C3DSphere* sphere)
{
	MATRIX RotZ, RotY;		//�s��v�Z�p

	targetPosi = VAdd(VGet(sphere->GetNowPosition().x, 0.0f, sphere->GetNowPosition().z), VGet(0.0f, 0.0f, 0.0f));

	if (KeyManager::OnKeyPressed(KEY_INPUT_A))
	{
		angleHei += 0.1f;
	}
	if (KeyManager::OnKeyPressed(KEY_INPUT_D))
	{
		angleHei -= 0.1f;
	}
	// ���������̉�]�͂x����]
	RotY = MGetRotY(angleHei);
	// ���������̉�]�͂y����] )
	RotZ = MGetRotZ(angleVer);
	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����:::VGet(-Camera_Player_Length, 10.0f, 0.0f)
	// ����������]( �y����] )����������:::VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ)
	// ����������]( �x����] )���� :::VTransform(VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ), RotY)
	// �����_�̍��W�𑫂������̂��J�����̍��W:::VAdd~
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//�J�����̈ʒu��V�������W�ɃZ�b�g
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);
}

void Camera::Rotation()
{
	MATRIX RotZ, RotY;		//�s��v�Z�p

	targetPosi = VAdd(VGet(0, 0, 0), VGet(0.0f, 0.0f, 0.0f));

	angleHei += 0.01f;

	// ���������̉�]�͂x����]
	RotY = MGetRotY(angleHei);

	// ���������̉�]�͂y����] )
	RotZ = MGetRotZ(angleVer);
	// �J�����̍��W���Z�o
	// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����:::VGet(-Camera_Player_Length, 10.0f, 0.0f)
	// ����������]( �y����] )����������:::VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ)
	// ����������]( �x����] )���� :::VTransform(VTransform(VGet(-Camera_Player_Length, 10.0f, 0.0f), RotZ), RotY)
	// �����_�̍��W�𑫂������̂��J�����̍��W:::VAdd~
	nowPosi = VAdd(VTransform(VTransform(VGet(-D_CAMERA_HIGHT_POSI, 10.0f, 0.0f), RotZ), RotY), targetPosi);

	//�J�����̈ʒu��V�������W�ɃZ�b�g
	SetCameraPositionAndTarget_UpVecY(nowPosi, targetPosi);
}

