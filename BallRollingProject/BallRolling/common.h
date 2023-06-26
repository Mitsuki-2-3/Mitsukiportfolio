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

struct T_Location
{
	float x;
	float y;


	//T_Location(float _x,float _y)
	//{
	//	x = _x;
	//	y = _y;
	//}

	T_Location operator+(T_Location location)
	{
		T_Location w;

		w.x = this->x + location.x;
		w.y = this->y + location.y;

		return w;
	}

	T_Location operator-(T_Location location)
	{
		T_Location w;

		w.x = this->x - location.x;
		w.y = this->y - location.y;

		return w;
	}

	T_Location operator+=(T_Location location)
	{

		this->x += location.x;
		this->y += location.y;

		return *this;

	}

	T_Location operator-=(T_Location location)
	{
		
		this->x -= location.x;
		this->y -= location.y;

		return *this;
	}
};

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

//struct Quaternion
//{
//	float w;
//	VECTOR v;
//
//	Quaternion Norm()
//	{
//		Quaternion data;
//
//		float abs = this->Qabs();
//
//		data = { this->w / abs,this->v.x / abs,this->v.y / abs,this->v.z / abs };
//		
//		return data;
//	}
//	Quaternion operator*(Quaternion data)
//	{
//		Quaternion   ans;
//		float   d1, d2, d3, d4;
//
//		d1 = this->w * data.w;
//		d2 = -this->v.x * data.v.x;
//		d3 = -this->v.y * data.v.y;
//		d4 = -this->v.z * data.v.z;
//		ans.w = d1 + d2 + d3 + d4;
//
//		d1 = this->w * data.v.x;
//		d2 = data.w * this->v.x;
//		d3 = this->v.y * data.v.z;
//		d4 = -this->v.z * data.v.y;
//		ans.v.x = d1 + d2 + d3 + d4;
//
//		d1 = this->w * data.v.y;
//		d2 = data.w * this->v.y;
//		d3 = this->v.z * data.v.x;
//		d4 = -this->v.x * data.v.z;
//		ans.v.y = d1 + d2 + d3 + d4;
//
//		d1 = this->w * data.v.z;
//		d2 = data.w * this->v.z;
//		d3 = this->v.x * data.v.y;
//		d4 = -this->v.y * data.v.x;
//		ans.v.z = d1 + d2 + d3 + d4;
//
//		return   ans;
//	}
//	/*Quaternion operator*(Quaternion data)
//	{
//		Quaternion re;
//		re.w = this->w * data.w - (VDot(this->v, data.v));
//		re.v = data.v * this->w + this->v * data.w + VCross(this->v, data.v);
//
//		return re;
//	}*/
//
//	Quaternion Rotate(float rad)
//	{
//		Quaternion re;
//		re.w = cos(rad / 2.0f);
//		re.v.x = this->v.x * sin(rad / 2.0f);
//		re.v.y = this->v.y * sin(rad / 2.0f);
//		re.v.z = this->v.z * sin(rad / 2.0f);
//
//		return re;
//	}
//
//	Quaternion Reverse(float rad)
//	{
//		Quaternion re;
//		re.w = cos(rad / 2.0f);
//		re.v.x = this->v.x * -1 * sin(rad / 2.0f);
//		re.v.y = this->v.y * -1 * sin(rad / 2.0f);
//		re.v.z = this->v.z * -1 * sin(rad / 2.0f);
//
//		return re;
//	}
//
//private:
//	float Qabs()
//	{
//		float re;
//
//		re = sqrt(pow(this->w,2) + pow(this->v.x,2)
//			+ pow(this->v.y,2) + pow(this->v.z,2));
//
//		return re;
//	}
//};
//
//Quaternion QuaternionRotate(Quaternion rever, Quaternion move, Quaternion now);

struct ST_CheckHit
{
	bool hit;
	VECTOR hitposi;
	VECTOR normalize;
};

struct Color
{
	static unsigned int color[COLOR_PARETTE_NUM];
};

struct ST_Surfaces
{
	VECTOR surface;
	VECTOR normal;
	VECTOR size;
	VECTOR poly[2][3];
};

struct ACCELERATION
{
	bool flg;
	float acceleration;
};

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

//ポリゴンと線分の当たり判定セット

/// 3次元座標上の線分と3角ポリゴンが交差してるかを判定
ST_CheckHit detectIsIntersectedLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3次元座標上の線分と平面が交差してるかを判定
bool detectCollisionLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// 3次元座標上の線分と平面の交点座標を求める
VECTOR calcIntersectionLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2);

/// ポリゴン上に点が含まれるかを判定
bool detectPointIsEnclosedByPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);

/// ある点から平面までの距離
float calcDistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2);


float GetAngle(float x1, float y1, float x2, float y2);

float GetThreeDimensionalAnglePar(VECTOR data1, VECTOR data2);
float GetThreeDimensionalAngleVer(VECTOR data1, VECTOR data2);
float GetThreeDimensionalAngleHor(VECTOR data1, VECTOR data2);


////ボールの回転迷走中
//// -------------------------------------------------------------
///// <summary>
///// オイラー角をクォータニオンに変換
///// </summary>
//Quaternion EulerAnglesToQuaternion(ST_Angle data);
//// -------------------------------------------------------------
///// <summary>
///// クォータニオンをオイラー角に変換
///// </summary>
//ST_Angle QuaternionToEulerAngles(Quaternion data);
//// -------------------------------------------------------------
///// <summary>
/////　クォータニオン同士の掛け算
///// </summary>
//Quaternion QuaternionMultiplication(Quaternion left, Quaternion right);

