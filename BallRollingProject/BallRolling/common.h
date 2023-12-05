#pragma once
#include"Controll.h"
#define _USE_MATH_DEFINES
#include<math.h>

#define DEBUG

#include <vector>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定

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

//角度
struct ST_Angle
{
	float angleHor;		//水平角度	X
	float anglePar;		//平行角度	Y
	float angleVer;		//垂直角度	Z


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

//当たり判定用
struct ST_CheckHit
{
	bool hit;
	VECTOR hitposi;
	VECTOR normalize;
};
//色
struct Color
{
	static unsigned int color[COLOR_PARETTE_NUM];
};

//面
struct ST_Surfaces
{
	VECTOR surface;
	VECTOR normal;
	VECTOR size;
	VECTOR poly[2][3];
};

//床の傾き
struct ACCELERATION
{
	bool flg;
	float acceleration;
};

//色の種類
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

//角度を調整用
void ResetAngle(float* a);

//奥から見た時の回転
VECTOR GetVerRotateVECTOR(VECTOR _data, float verangle);
//横から見たときの回転
VECTOR GetHorRotateVECTOR(VECTOR _data, float Horangle);
//上から見たときの回転移動
VECTOR GetParRotateVECTOR(VECTOR _data, float Parangle);

//全ての回転移動
VECTOR MoveRotation(VECTOR _data, ST_Angle _angle);

VECTOR VECTORNormal(VECTOR origin, VECTOR _data1, VECTOR _data2);

/*ポリゴンと線分の当たり判定セット*/
/// 3次元座標上の線分と3角ポリゴンが交差してるかを判定
ST_CheckHit CheckLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3次元座標上の線分と平面が交差してるかを判定
bool CheckLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3次元座標上の線分と平面の交点座標を求める
VECTOR VectorOfLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// ポリゴン上に点が含まれるかを判定
bool CheckPointOnPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);

/// ある点から平面までの距離
float DistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);


float GetAngle(float x1, float y1, float x2, float y2);


