#include "C3DSphere.h"
#include "CheckHit.h"
#include <iostream>
#include <cmath>

C3DSphere::C3DSphere(VECTOR firstposi, float _radius, ST_Angle _angle)
{
	//���W
	nowWorldPosi = firstposi;
	//���a
	radius = _radius;
	//�X��
	localAngle = _angle;
	//�d��
	gravity = -0.1f;
	//�ړ��ʂ̏�����
	moveVector = VGet(0,0,0);

	//�Ȃ񂿂���Ė��C��ON/OFF
	friction = false;	
}

void C3DSphere::Updata()
{
	//�ړ��ʂɏd�͂̒ǉ�
	moveVector.y += gravity;

	//�Â����W�֌��݂̈ړ��ʂ̉��Z
	nowWorldPosi += moveVector;

	////�Ȃ񂿂���Ė��C
	if (friction) {
		moveVector -= moveVector * 0.02f;
	}
}

void C3DSphere::Draw() const
{
	//���̕`��
	DrawSphere3D(nowWorldPosi, radius, 32, 0x0000FF, 0x00ff00, TRUE);
}

//�ǂƂ̓����蔻�菈��
void C3DSphere::CheckHitWall(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };
	//�����̂Ƃ̓����蔻��
	hit1 = Check3DQuadrangularPrism(data, this);
	//�����œ����蔻��Ɠ����������̍��W
	if (hit1.hit == true)
	{
		//����������ړ��ʂ��t�ɂ��Ē��˕Ԃ�
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize) * 1.15f);
		//�����ł߂荞�ݖh�~
		saves1 = (hit1.hitposi + hit1.normalize * (GetRadius() / 100.0f)) - nowWorldPosi;
		//�߂荞��ł镪�߂�
		nowWorldPosi += saves1;
	}

}

//���Ƃ̓����蔻�菈��
void C3DSphere::CheckHitFloor(C3DPrism* data)
{
	ST_CheckHit hit1 = { 0 };
	VECTOR saves1 = { 0 };

	hit1 = Check3DQuadrangularPrism(data, this);
	//�����œ����蔻��Ɠ����������̍��W
	if (hit1.hit == true)
	{
		//����������ړ��ʂ��t�ɂ���
		moveVector = moveVector - (hit1.normalize * VDot(moveVector, hit1.normalize));
		//�����ł߂荞�ݖh�~
		saves1 = (hit1.hitposi) - nowWorldPosi;
		//�߂荞��ł镪�߂�
		nowWorldPosi += saves1;
	}
}

bool C3DSphere::CheckHitItem(C3DPrism* data)
{
	//�A�C�e���Ƃ̏���
	if (OBBPrism(data, this))
	{
		DrawString(200, 200, "HIT ITEM", 0xffffff);
		return true;
	}
	return false;
}

