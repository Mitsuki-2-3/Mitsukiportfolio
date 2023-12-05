#include"CheckHit.h"


using namespace std;


//�������ʂɓ������Ă��邩
ST_CheckHit CheckFaceOfCube(C3DPrism* prism, C3DSphere* sphere)
{
	//�ړ��O�ƈړ���̍��W���ʂ��ђʂ��Ă�����
	//�K�v�ȃf�[�^�̕ۑ�
	ST_Surfaces* check = prism->GetSuface();
	ST_CheckHit result = { false,VGet(0,0,0) };

	for (int i = 0; i < 6; i++)
	{
		ST_Surfaces surface = check[i];
		HITRESULT_LINE hit1,hit2;
		VECTOR sphereS = sphere->GetNowPosition();
		VECTOR sphereF;
		if (VSize(sphere->GetMoveVector()) > sphere->GetRadius()) {
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (VSize(sphere->GetMoveVector())) * -1;
		}
		else {
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (sphere->GetRadius()) * -1;
		}
		hit1 = HitCheck_Line_Triangle(sphereS.VFloor(), sphereF.VFloor(),
			surface.poly[0][0].VFloor(), surface.poly[0][1].VFloor(),
			surface.poly[0][2].VFloor());
		hit2 = HitCheck_Line_Triangle(sphereS.VFloor(), sphereF.VFloor(),
			surface.poly[1][0].VFloor(), surface.poly[1][1].VFloor(), 
			surface.poly[1][2].VFloor());
		if (hit1.HitFlag == 1 || hit2.HitFlag == 1)
		{
			result.hit = true;
			if (hit1.HitFlag == 1)result.hitposi = hit1.Position.VFloor();
			if (hit2.HitFlag == 1)result.hitposi = hit2.Position.VFloor();
			result.normalize = surface.normal;

			return result;
		}
	}
	return result;
}

//���Ɨ����̂Ɋ܂܂��ʂƂ̓����蔻��
ST_CheckHit Check3DQuadrangularPrism(C3DPrism* prism, C3DSphere* sphere)
{
	ST_CheckHit result = { false,VGet(0,0,0),VGet(0,0,0) };
	ST_Surfaces* check = prism->GetSuface();
	//����p�̃x�N�g���n�_
	VECTOR sphereS = sphere->GetNowPosition();
	//����p�̃x�N�g���I�_
	VECTOR sphereF;
	//�ړ��O�ƈړ���̍��W���ʂ��ђʂ��Ă�����
	for (int i = 0; i < 6; i++) 
	{
		//�K�v�ȃf�[�^�̕ۑ�
		//���茋�ʗp
		ST_Surfaces surface = check[i];

		//���̃T�C�Y�ƈړ��ʃx�N�g���̑傫����r
		if (VSize(sphere->GetMoveVector()) > sphere->GetRadius()) {
			//�ړ��ʂ��傫����
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (VSize(sphere->GetMoveVector())) * -1;
		}
		else {
			//�T�C�Y���傫����
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (sphere->GetRadius()) * -1;
		}
		//�O�p�|���S������p1�E2
		ST_CheckHit hit1, hit2;

		//�|���S���Ɛ����̔���1
		hit1 = CheckLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[0][0].VFloor(), surface.poly[0][1].VFloor(),
			surface.poly[0][2].VFloor());
		//�|���S���Ɛ����̔���2
		hit2 = CheckLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[1][0].VFloor(), surface.poly[1][1].VFloor(),
			surface.poly[1][2].VFloor());

		//�ǂ��炩�ɓ������Ă���ꍇ
		if (hit1.hit == true || hit2.hit == true)
		{
			result.hit = true;
			if (hit1.hit == true) 
			{
				//�����Ɩʂ̌����_�̍��W���狅�̔��a�����炷
				result.hitposi = hit1.hitposi.VFloor()
					+ surface.normal * (sphere->GetRadius()
						+ sphere->GetRadius() / 20.0f);
			}
			if (hit2.hit == true)
			{
				//�����Ɩʂ̌����_�̍��W���狅�̔��a�����炷
				result.hitposi = hit2.hitposi.VFloor()
					+ surface.normal * (sphere->GetRadius()
						+ sphere->GetRadius() / 20.0f);
			}
			//�|���S���̖@���x�N�g����Ԃ�
			result.normalize = surface.normal;
			return result;
		}
	}
	return result;
}

//���ƌX���Ȃ������̂̓����蔻��
bool AABBPrism(C3DPrism* prism, C3DSphere* sphere)
{
	//�g���ϐ����ꎞ�I�ɕۑ�
	VECTOR G = prism->GetNowPosi();
	VECTOR nowSpherePosi = VSub(sphere->GetNowPosition() , G);
	float center[3] = { nowSpherePosi.x,nowSpherePosi.y,nowSpherePosi.z };
	float pr[3] = { G.x,G.y,G.z };
	float* size = prism->GetSize();
	float vec = 0;
	float s = 0;
	float vsize = 0;

	//�����̂̍��W�{�傫���Ƌ��̒��S���W���r��
	//�͂ݏo���Ă��镪��ۑ�
	for (int i = 0; i < 3; i++) {
		//�傫���p
		float min = size[i] * -1.0f;
		float max = size[i] * 1.0f;
		if (center[i] < min)
		{
			vec += (center[i] - min) * (center[i] - min);
			continue;
		}
		if (center[i] > max)
		{
			vec += (center[i] - max) * (center[i] - max);
			continue;
		}
	}

	//�͂ݏo���Ă��镪�����̔��a��菬�������ǂ���
	if (vec <= sphere->GetRadius()*sphere->GetRadius())
	{
		//�������̂œ������Ă���
		return true;
	}
	//�������Ă��Ȃ�
	return false;
}

//���ƌX���ނ������̂̓����蔻��
bool OBBPrism(C3DPrism* prism, C3DSphere* sphere)
{
	//�g���ϐ����ꎞ�I�ɕۑ�
	VECTOR G = prism->GetNowPosi()  ;
	VECTOR nowSpherePosi = sphere->GetNowPosition();
	VECTOR* dic = prism->Getdic();
	VECTOR vec = { 0 };
	VECTOR vect[3] = { 0 };
	float L = 0;
	float s[3] = { 0 };
	float* vsize = prism->GetSize();

	//�����̂̍��W�{�傫���Ƌ��̒��S���W���r��
	//�͂ݏo���Ă��镪�̃x�N�g����ۑ�
	for (int i = 0; i < 3; i++) {
		//�傫��
		L = vsize[i];
		if (L <= 0)continue;
		//�����痧���̂ւ̃x�N�g���ƌX���Ă�Ӄx�N�g���̓��ς�{���̕ӂ̑傫���Ŋ���
		s[i] = VDot(nowSpherePosi - G, dic[i]) / L;
		//��Βl���㏑��
		s[i] = fabsf(s[i]);
		//1���傫����
		if (s[i] > 1) {
			//�͂ݏo���Ă��镪�̃x�N�g����ۑ�
			vec += dic[i] * ((1 - s[i]) * L);
		}
	}

	//�͂ݏo���Ă���x�N�g���̃T�C�Y�������̔��a��菬�������ǂ���
	if (VSize(vec) < sphere->GetRadius())
	{
		//�������̂œ������Ă���
		return true;
	}
	return false;
}