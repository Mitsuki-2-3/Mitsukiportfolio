#pragma once
#include"Controll.h"
#define _USE_MATH_DEFINES
#include<math.h>

#define DEBUG

#include <vector>       // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��

#define D_SCREEN_WIDTH_MAX 1280
#define D_SCREEN_HEIGHT_MAX 720

#define D_COLLISION_SPHERE 0
#define D_COLLISION_BOX 1

#define D_GRAVITY 1.f

#define COLOR_PARETTE_NUM 9

#define D_TILT_TIME 90.0f
#define D_TILT float(30 * M_PI /180)
#define D_ACCELERATION D_TILT / D_TILT_TIME
#define D_ACCE_ANGLE 0.0058177555555556/24.f
#define D_ACCE_DOUBLE 6.f

//�p�x
struct ST_Angle
{
	float angleHor;		//�����p�x	X
	float anglePar;		//���s�p�x	Y
	float angleVer;		//�����p�x	Z


	ST_Angle operator=(ST_Angle localAngle)
	{
		this->angleVer = localAngle.angleVer;
		this->angleHor = localAngle.angleHor;
		this->anglePar = localAngle.anglePar;

		return *this;
	}
	ST_Angle operator+=(ST_Angle localAngle)
	{
		this->angleVer += localAngle.angleVer;
		this->angleHor += localAngle.angleHor;
		this->anglePar += localAngle.anglePar;

		return *this;
	}
	ST_Angle operator-=(ST_Angle localAngle)
	{
		this->angleVer -= localAngle.angleVer;
		this->angleHor -= localAngle.angleHor;
		this->anglePar -= localAngle.anglePar;

		return *this;
	}
	ST_Angle operator+(ST_Angle localAngle)
	{
		ST_Angle data;

		data.angleVer =this->angleVer + localAngle.angleVer;
		data.angleHor =this->angleHor + localAngle.angleHor;
		data.anglePar =this->anglePar + localAngle.anglePar;

		return data;
	}
	ST_Angle operator-(ST_Angle localAngle)
	{
		ST_Angle data;

		data.angleVer =this->angleVer - localAngle.angleVer;
		data.angleHor =this->angleHor - localAngle.angleHor;
		data.anglePar =this->anglePar - localAngle.anglePar;

		return data;
	}
};

//�����蔻��p
struct ST_CheckHit
{
	bool hit;
	VECTOR hitposi;
	VECTOR normalize;
};
//�F
struct Color
{
	static unsigned int color[COLOR_PARETTE_NUM];
};

//��
struct ST_Surfaces
{
	VECTOR surface;
	VECTOR normal;
	VECTOR size;
	VECTOR poly[2][3];
};

//���̌X��
struct ACCELERATION
{
	bool flg;
	float acceleration;
};

//�F�̎��
enum COLORTYPE : unsigned int
{
	RED = 0,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	NAVYBLUE,
	PURPLE,
	GRAY,
	LINE,
};

//�p�x�𒲐��p
void ResetAngle(float* a);

//�����猩�����̉�]
VECTOR GetVerRotateVECTOR(VECTOR _data, float verangle);
//�����猩���Ƃ��̉�]
VECTOR GetHorRotateVECTOR(VECTOR _data, float Horangle);
//�ォ�猩���Ƃ��̉�]�ړ�
VECTOR GetParRotateVECTOR(VECTOR _data, float Parangle);

//�S�Ẳ�]�ړ�
VECTOR MoveRotation(VECTOR _data, ST_Angle _angle);

VECTOR VECTORNormal(VECTOR origin, VECTOR _data1, VECTOR _data2);

/*�|���S���Ɛ����̓����蔻��Z�b�g*/
/// 3�������W��̐�����3�p�|���S�����������Ă邩�𔻒�
ST_CheckHit CheckLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3�������W��̐����ƕ��ʂ��������Ă邩�𔻒�
bool CheckLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3�������W��̐����ƕ��ʂ̌�_���W�����߂�
VECTOR VectorOfLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// �|���S����ɓ_���܂܂�邩�𔻒�
bool CheckPointOnPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);

/// ����_���畽�ʂ܂ł̋���
float DistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);


float GetAngle(float x1, float y1, float x2, float y2);


