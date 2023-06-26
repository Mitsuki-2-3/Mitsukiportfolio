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
	//�ړ��O�ƈړ���̍��W���ʂ��ђʂ��Ă�����
	for (int i = 0; i < 6; i++) 
	{
		//�K�v�ȃf�[�^�̕ۑ�
		ST_Surfaces surface = check[i];
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
		ST_CheckHit hit1, hit2;

		hit1 = detectIsIntersectedLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[0][0].VFloor(), surface.poly[0][1].VFloor(),
			surface.poly[0][2].VFloor());
		hit2 = detectIsIntersectedLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[1][0].VFloor(), surface.poly[1][1].VFloor(),
			surface.poly[1][2].VFloor());

		if (hit1.hit == true || hit2.hit == true)
		{
			result.hit = true;
			if (hit1.hit == true)result.hitposi = hit1.hitposi.VFloor()
				+ surface.normal * (sphere->GetRadius() 
					+ sphere->GetRadius()/20.0f);
			if (hit2.hit == true)result.hitposi = hit2.hitposi.VFloor()
				+ surface.normal * (sphere->GetRadius() 
					+ sphere->GetRadius()/20.0f);
			result.normalize = surface.normal;

			return result;
		}
		
	}
	return result;
}

//���Ɨ����̂̓����蔻��
ST_CheckHit CheckPrism(C3DPrism* prism, C3DSphere* sphere)
{
	ST_CheckHit resault = { false,VGet(0,0,0) };

	ST_CheckHit faceResault;

	{
		//�����̂Ɋ܂܂��ʂƋ��̓����蔻��
		faceResault = CheckFaceOfCube(prism, sphere);
	}

	if(faceResault.hit == true)
	{
		//�������Ă������Ƀf�[�^��n��
		resault.hit = true;
		resault.normalize = faceResault.normalize;
		//�����蔻��𒆐S���W�łƂ��Ă���̂ŋ��̔��a�����炷
		resault.hitposi = faceResault.hitposi + faceResault.normalize 
			* (sphere->GetRadius() + sphere->GetRadius() / 40);

		return resault;  
	}
	return resault;
}

bool NotTiltedPrism(C3DPrism* prism, C3DSphere* sphere)
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

	for (int i = 0; i < 3; i++) {
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

	if (vec <= sphere->GetRadius()*sphere->GetRadius())
	{

		return true;
	}

	return false;
}



bool ItemCheck(C3DPrism* prism, C3DSphere* sphere)
{
	//�g���ϐ����ꎞ�I�ɕۑ�
	VECTOR G = prism->GetNowPosi()  ;
	VECTOR nowSpherePosi = sphere->GetNowPosition();
	VECTOR* dic = prism->Getdic();
	VECTOR vec = { 0 };
	VECTOR vect[3] = { 0 };
	float L = 0;
	float s[3] = { 0 };
	float pl[3] = { 0 };
	float* vsize = prism->GetSize();

	//�C���O
	for (int i = 0; i < 3; i++) {
		L = vsize[i];
		if (L <= 0)continue;
		s[i] = VDot(nowSpherePosi - G, dic[i]) / L;
		s[i] = fabsf(s[i]);
		if (s[i] > 1) {
			vec += dic[i] * ((1 - s[i]) * L);
			vect[i] += dic[i] * ((1 - s[i]) * L);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		L = vsize[i];
		s[i] = VDot(nowSpherePosi - G, dic[i]) / L;
		s[i] = fabsf(s[i]);
		pl[i] = (sphere->GetRadius() + L) / L;
	}
	if (VSize(vec) < sphere->GetRadius())
	{
		return true;
	}
	return false;
}