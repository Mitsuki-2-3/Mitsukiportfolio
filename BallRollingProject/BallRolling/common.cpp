#include"common.h"

//����
//Ver = ZRotate
//Hor = XRotate
//Par = YRotate

unsigned int  Color::color[COLOR_PARETTE_NUM] = {
	0xE83929,	//�� 0
	0xE8DD29,	//�� 1
	0x50E829,	//�� 2
	0x29E8A6,	//�� 3
	0x2986E8,	//�� 4
	0x7029E8,	//�� 5
	0xE829BD,	//�� 6
	0x898989,	//�D 7
	0x3E3A39	//���C���p
};

void ResetAngle(float* a)
{
	float i = floorf(*a) / (float)M_PI;

	float re = *a - ( (float)M_PI * i);

	*a = floorf(re * 100.0f) / 100.0f;
}

VECTOR GetVerRotateVECTOR(VECTOR _data, float verangle)
{
	//Z = Z;
	//X = xcos�� - ysin��;
	//Y = xsin�� + ycos��;

	VECTOR self;

	self.z = _data.z;

	self.x = _data.x * (cosf(verangle)) - _data.y * (sinf(verangle));
	self.y = _data.x * (sinf(verangle)) + _data.y * (cosf(verangle));

	return self;
}
VECTOR GetHorRotateVECTOR(VECTOR _data, float Horangle)
{
	//X = X;
	//Y = ycos�� - zsin��;
	//Z = ysin�� + zcos��;

	VECTOR self;

	self.x = _data.x;

	self.y = _data.y * (cosf(Horangle)) - _data.z * (sinf(Horangle));
	self.z = _data.y * (sinf(Horangle)) + _data.z * (cosf(Horangle));

	return self;
}

VECTOR GetParRotateVECTOR(VECTOR _data, float Parangle)
{
	//Y = Y;
	//Z = zcos�� - xsin��;
	//X = zsin�� + xcos��;

	VECTOR self;

	self.y = _data.y;

	self.z = _data.z * (cosf(Parangle)) - _data.x * (sinf(Parangle));
	self.x = _data.z * (sinf(Parangle)) + _data.x * (cosf(Parangle));

	return self;
}

VECTOR MoveRotation(VECTOR _data, ST_Angle _angle)
{
	VECTOR self;
	{
		//��]����
		//�ォ�猩���Ƃ��̉�]
		self = GetParRotateVECTOR(_data, _angle.anglePar);
		//�����猩���Ƃ��̉�]
		self = GetHorRotateVECTOR(self, _angle.angleHor);
		//�����猩�����̉�]
		self = GetVerRotateVECTOR(self, _angle.angleVer);
	}

	//�ړ���̎O�������W
	return self;
}


//�@���̌v�Z
VECTOR VECTORNormal(VECTOR origin, VECTOR _data1, VECTOR _data2)
{
	VECTOR localnormal;
	VECTOR savelocal1 = _data1.VFloor() + origin.VFloor();
	VECTOR savelocal2 = _data2.VFloor() + origin.VFloor();

	//����
	localnormal = VCross(savelocal2, savelocal1);

	localnormal.x = floorf(localnormal.x * 100.0f) / 100;
	localnormal.y = floorf(localnormal.y * 100.0f) / 100;
	localnormal.z = floorf(localnormal.z * 100.0f) / 100;

	//���K��
	return VNorm(localnormal);
}


ST_CheckHit CheckLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//���������ʂɌ������Ă��邩
	bool bCollision = CheckLineSegmentAndPlane(a, b, v0, v1, v2);
	ST_CheckHit hit = { false,VGet(0,0,0) };

	if (bCollision) {
		//��_���W
		VECTOR p = VectorOfLineSegmentAndPlane(a, b, v0, v1, v2);
		//�ʂ̒��Ɍ�_���W���܂܂�邩
		if (CheckPointOnPolygon(p, v0, v1, v2)) {
			//�܂܂��
			hit.hit = true;
			hit.hitposi = p;
			return hit;
		}
		else {
			//�܂܂�Ȃ�
			return hit;
		}
	}
	else {
		//�������Ă��Ȃ�
		return hit;
	}
}

bool CheckLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//�ʂ̖@���x�N�g��
	VECTOR n = VNorm((VCross(v1 - v0, v2 - v1)));
	//�x�N�g���̕���
	VECTOR g = (v0 + v1 + v2) / 3.0f;

	//���������ʂɌ������Ă��邩
	if (VDot((a - g), n) * VDot((b - g), n) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

VECTOR VectorOfLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//���ʂ�������̎n�_�܂ł̋���
	float distAP = DistancePointAndPlane(a, v0, v1, v2);
	//���ʂ�������̏I�_�܂ł̋���
	float distBP = DistancePointAndPlane(b, v0, v1, v2);

	//���ʂ����̓_�̊���
	float t = distAP / (distAP + distBP);

	return (b - a) * t + a;
}

bool CheckPointOnPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	//�ʂ̖@���x�N�g��
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));

	//�ʂƓ_�̖@���x�N�g��
	VECTOR n0 = VNorm(VCross(v1 - v0, p - v1));
	VECTOR n1 = VNorm(VCross(v2 - v1, p - v2));
	VECTOR n2 = VNorm(VCross(v0 - v2, p - v0));

	//���ςŔ�r(0.001�����̌덷�����e)
	if ((1.0f - VDot(n, n0)) > 0.001f) return false;
	if ((1.0f - VDot(n, n1)) > 0.001f) return false;
	if ((1.0f - VDot(n, n2)) > 0.001f) return false;

	return true;
}

float DistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	//�ʂ̖@���x�N�g��
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));
	//�x�N�g���̕���
	VECTOR g = (v0 + v1 + v2) / 3.0f;
	//�����̑傫��
	return fabsf(VDot(n, p - g));
}

float GetAngle(float x1, float y1,float x2,float y2)
{
	//�x�N�g��A��B�̒������v�Z����
	float length_A = sqrtf((x1 * x1) + (y1 * y1));
	float length_B = sqrtf((x2 * x2) + (y2 * y2));

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = (x1 * x2 + y1 * y2) / (length_A * length_B);

	//cos�Ƃ���Ƃ����߂�
	float sita = acosf(cos_sita);

	//���W�A���łȂ�0�`180�̊p�x�łق����ꍇ�̓R�����g�O��
	//sita = sita * 180.0 / PI;

	return floorf(sita * 100.0f) / 100.0f;
}

