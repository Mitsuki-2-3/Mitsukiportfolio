#include"common.h"

//メモ
//Ver = ZRotate
//Hor = XRotate
//Par = YRotate

unsigned int  Color::color[COLOR_PARETTE_NUM] = {
	0xE83929,	//赤 0
	0xE8DD29,	//橙 1
	0x50E829,	//黄 2
	0x29E8A6,	//緑 3
	0x2986E8,	//青 4
	0x7029E8,	//紺 5
	0xE829BD,	//紫 6
	0x898989,	//灰 7
	0x3E3A39	//ライン用
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
	//X = xcosθ - ysinθ;
	//Y = xsinθ + ycosθ;

	VECTOR self;

	self.z = _data.z;

	self.x = _data.x * (cosf(verangle)) - _data.y * (sinf(verangle));
	self.y = _data.x * (sinf(verangle)) + _data.y * (cosf(verangle));

	return self;
}
VECTOR GetHorRotateVECTOR(VECTOR _data, float Horangle)
{
	//X = X;
	//Y = ycosθ - zsinθ;
	//Z = ysinθ + zcosθ;

	VECTOR self;

	self.x = _data.x;

	self.y = _data.y * (cosf(Horangle)) - _data.z * (sinf(Horangle));
	self.z = _data.y * (sinf(Horangle)) + _data.z * (cosf(Horangle));

	return self;
}

VECTOR GetParRotateVECTOR(VECTOR _data, float Parangle)
{
	//Y = Y;
	//Z = zcosθ - xsinθ;
	//X = zsinθ + xcosθ;

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
		//回転処理
		//上から見たときの回転
		self = GetParRotateVECTOR(_data, _angle.anglePar);
		//横から見たときの回転
		self = GetHorRotateVECTOR(self, _angle.angleHor);
		//奥から見た時の回転
		self = GetVerRotateVECTOR(self, _angle.angleVer);
	}

	//移動後の三次元座標
	return self;
}


//法線の計算
VECTOR VECTORNormal(VECTOR origin, VECTOR _data1, VECTOR _data2)
{
	VECTOR localnormal;
	VECTOR savelocal1 = _data1.VFloor() + origin.VFloor();
	VECTOR savelocal2 = _data2.VFloor() + origin.VFloor();

	//内積
	localnormal = VCross(savelocal2, savelocal1);

	localnormal.x = floorf(localnormal.x * 100.0f) / 100;
	localnormal.y = floorf(localnormal.y * 100.0f) / 100;
	localnormal.z = floorf(localnormal.z * 100.0f) / 100;

	//正規化
	return VNorm(localnormal);
}


ST_CheckHit CheckLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//線分が平面に交差しているか
	bool bCollision = CheckLineSegmentAndPlane(a, b, v0, v1, v2);
	ST_CheckHit hit = { false,VGet(0,0,0) };

	if (bCollision) {
		//交点座標
		VECTOR p = VectorOfLineSegmentAndPlane(a, b, v0, v1, v2);
		//面の中に交点座標が含まれるか
		if (CheckPointOnPolygon(p, v0, v1, v2)) {
			//含まれる
			hit.hit = true;
			hit.hitposi = p;
			return hit;
		}
		else {
			//含まれない
			return hit;
		}
	}
	else {
		//交差していない
		return hit;
	}
}

bool CheckLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//面の法線ベクトル
	VECTOR n = VNorm((VCross(v1 - v0, v2 - v1)));
	//ベクトルの平均
	VECTOR g = (v0 + v1 + v2) / 3.0f;

	//線分が平面に交差しているか
	if (VDot((a - g), n) * VDot((b - g), n) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

VECTOR VectorOfLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	//平面から線分の始点までの距離
	float distAP = DistancePointAndPlane(a, v0, v1, v2);
	//平面から線分の終点までの距離
	float distBP = DistancePointAndPlane(b, v0, v1, v2);

	//平面から二つの点の割合
	float t = distAP / (distAP + distBP);

	return (b - a) * t + a;
}

bool CheckPointOnPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	//面の法線ベクトル
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));

	//面と点の法線ベクトル
	VECTOR n0 = VNorm(VCross(v1 - v0, p - v1));
	VECTOR n1 = VNorm(VCross(v2 - v1, p - v2));
	VECTOR n2 = VNorm(VCross(v0 - v2, p - v0));

	//内積で比較(0.001未満の誤差を許容)
	if ((1.0f - VDot(n, n0)) > 0.001f) return false;
	if ((1.0f - VDot(n, n1)) > 0.001f) return false;
	if ((1.0f - VDot(n, n2)) > 0.001f) return false;

	return true;
}

float DistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	//面の法線ベクトル
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));
	//ベクトルの平均
	VECTOR g = (v0 + v1 + v2) / 3.0f;
	//距離の大きさ
	return fabsf(VDot(n, p - g));
}

float GetAngle(float x1, float y1,float x2,float y2)
{
	//ベクトルAとBの長さを計算する
	float length_A = sqrtf((x1 * x1) + (y1 * y1));
	float length_B = sqrtf((x2 * x2) + (y2 * y2));

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = (x1 * x2 + y1 * y2) / (length_A * length_B);

	//cosθからθを求める
	float sita = acosf(cos_sita);

	//ラジアンでなく0～180の角度でほしい場合はコメント外す
	//sita = sita * 180.0 / PI;

	return floorf(sita * 100.0f) / 100.0f;
}

