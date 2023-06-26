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


ST_CheckHit detectIsIntersectedLineSegmentAndPolygon(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	bool bCollision = detectCollisionLineSegmentAndPlane(a, b, v0, v1, v2);
	ST_CheckHit hit = { false,VGet(0,0,0) };

	if (bCollision) {
		VECTOR p = calcIntersectionLineSegmentAndPlane(a, b, v0, v1, v2);
		if (detectPointIsEnclosedByPolygon(p, v0, v1, v2)) {
			hit.hit = true;
			hit.hitposi = p;
			return hit;
		}
		else {
			return hit;
		}
	}
	else {
		return hit;
	}
}

bool detectCollisionLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	VECTOR n = VNorm((VCross(v1 - v0, v2 - v1)));
	VECTOR g = (v0 + v1 + v2) / 3.0f;

	if (VDot((a - g), n) * VDot((b - g), n) <= 0) {
		return true;
	}
	else {
		return false;
	}
}

VECTOR calcIntersectionLineSegmentAndPlane(VECTOR a, VECTOR b, VECTOR v0, VECTOR v1, VECTOR v2) {

	float distAP = calcDistancePointAndPlane(a, v0, v1, v2);
	float distBP = calcDistancePointAndPlane(b, v0, v1, v2);

	float t = distAP / (distAP + distBP);

	return (b - a) * t + a;
}

bool detectPointIsEnclosedByPolygon(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));

	VECTOR n0 = VNorm(VCross(v1 - v0, p - v1));
	VECTOR n1 = VNorm(VCross(v2 - v1, p - v2));
	VECTOR n2 = VNorm(VCross(v0 - v2, p - v0));

	if ((1.0f - VDot(n, n0)) > 0.001f) return false;
	if ((1.0f - VDot(n, n1)) > 0.001f) return false;
	if ((1.0f - VDot(n, n2)) > 0.001f) return false;

	return true;
}

float calcDistancePointAndPlane(VECTOR p, VECTOR v0, VECTOR v1, VECTOR v2) {
	VECTOR n = VNorm(VCross(v1 - v0, v2 - v1));
	VECTOR g = (v0 + v1 + v2) / 3.0f;
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

float GetThreeDimensionalAnglePar(VECTOR data1 , VECTOR data2)
{
	float result;

	result = fabsf(GetAngle(data1.x, data1.z, data2.x, data2.z));

	return result;
}

float GetThreeDimensionalAngleVer(VECTOR data1, VECTOR data2)
{
	float result;

	result = fabsf(GetAngle(data1.y, data1.x, data2.y, data2.x));

	return result;
}

float GetThreeDimensionalAngleHor(VECTOR data1, VECTOR data2)
{
	float result;

	result = fabsf(GetAngle(data1.z, data1.y, data2.z, data2.y));

	return result;
}

//auto cx = std::cos(e.x);
//auto sx = std::sin(e.x);
//auto cy = std::cos(e.y);
//auto sy = std::sin(e.y);
//auto cz = std::cos(e.z);
//auto sz = std::sin(e.z);

//case EulerOrder::XYZ:
//	return RotationMatrix({
//	  cy * cz, sx * sy * cz + cx * sz,
//  -cx * sy * cz + sx * sz,
//	  -cy * sz, -sx * sy * sz + cx * cz,
//  cx * sy * sz + sx * cz,
//	  sy, -sx * cy, cx * cy
//		});
//case EulerOrder::XZY:
//	return RotationMatrix({
//	  cy * cz, cx * cy * sz + sx * sy,
//  sx * cy * sz - cx * sy,
//	  -sz, cx * cz, sx * cz,
//	  sy * cz, cx * sy * sz - sx * cy,
//  sx * sy * sz + cx * cy
//		});
//case EulerOrder::YXZ:
//	return RotationMatrix({
//	  sx * sy * sz + cy * cz,
//  cx * sz, sx * cy * sz - sy * cz,
//	  sx * sy * cz - cy * sz, cx * cz, 
// sx * cy * cz + sy * sz,
//	  cx * sy, -sx, cx * cy
//		});
//case EulerOrder::YZX:
//	return RotationMatrix({
//	  cy * cz, sz, -sy * cz,
//	  -cx * cy * sz + sx * sy, cx * cz, cx * sy * sz + sx * cy,
//	  sx * cy * sz + cx * sy, -sx * cz, -sx * sy * sz + cx * cy
//		});
//case EulerOrder::ZXY:
//	return RotationMatrix({
//	  -sx * sy * sz + cy * cz, sx * sy * cz + cy * sz, -cx * sy,
//	  -cx * sz, cx * cz, sx,
//	  sx * cy * sz + sy * cz, -sx * cy * cz + sy * sz, cx * cy
//		});
//case EulerOrder::ZYX:
//	return RotationMatrix({
//	  cy * cz, cy * sz, -sy,
//	  sx * sy * cz - cx * sz, sx * sy * sz + cx * cz, sx * cy,
//	  cx * sy * cz + sx * sz, cx * sy * sz - sx * cz, cx * cy

//Quaternion EulerAnglesToQuaternion(ST_Angle data)
//{
//	Quaternion re;
//
//	double cx = cos(data.angleHor / M_PI * 180);
//	double sx = sin(data.angleHor / M_PI * 180);
//	double cy = cos(data.anglePar / M_PI * 180);
//	double sy = sin(data.anglePar / M_PI * 180);
//	double cz = cos(data.angleVer / M_PI * 180);
//	double sz = sin(data.angleVer / M_PI * 180);
//	
//
//	//q0 = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
//	//q1 = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
//	//q2 = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
//	//q3 = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
//
//	re.w = cx * cy * cz + sx * sy * sz;
//	re.v.x = sx * cy * cz - cx * sy * sz;
//	re.v.y = cx * sy * cz + sx * cy * sz;
//	re.v.z = cx * cy * sz - sx * sy * cz;
//
//	re.v = VNorm(re.v);
//
//	return re;
//}

//Quaternion QuaternionMultiplication(Quaternion left, Quaternion right) {
//	Quaternion quat;
//	double d0, d1, d2, d3;
//
//	d0 = left.w * right.w;
//	d1 = -left.v.x * right.v.x;
//	d2 = -left.v.y * right.v.y;
//	d3 = -left.v.z * right.v.z;
//	quat.w = d0 + d1 + d2 + d3;
//
//	d0 = left.w * right.v.x;
//	d1 = right.w * left.v.x;
//	d2 = left.v.y * right.v.z;
//	d3 = -left.v.z * right.v.y;
//	quat.v.x = d0 + d1 + d2 + d3;
//
//	d0 = left.w * right.v.y;
//	d1 = right.w * left.v.y;
//	d2 = left.v.z * right.v.x;
//	d3 = -left.v.x * right.v.z;
//	quat.v.y = d0 + d1 + d2 + d3;
//
//	d0 = left.w * right.v.z;
//	d1 = right.w * left.v.z;
//	d2 = left.v.x * right.v.y;
//	d3 = -left.v.y * right.v.x;
//	quat.v.z = d0 + d1 + d2 + d3;
//
//	return quat;
//}
//
//ST_Angle QuaternionToEulerAngles(Quaternion data)
//{
//	ST_Angle an;
//	double q0q0 = data.v.z * data.v.z;
//	double q0q1 = data.v.z * data.v.x;
//	double q0q2 = data.v.z * data.v.y;
//	double q0q3 = data.v.z * data.w;
//	double q1q1 = data.v.x * data.v.x;
//	double q1q2 = data.v.x * data.v.y;
//	double q1q3 = data.v.x * data.w;
//	double q2q2 = data.v.y * data.v.y;
//	double q2q3 = data.v.y * data.w;
//	double q3q3 = data.w * data.w;
//	an.angleHor = atan2(2.0 * (q2q3 + q0q1), q0q0 - q1q1 - q2q2 + q3q3) * 180 / M_PI;
//	an.anglePar = asin(2.0 * (q0q2 - q1q3)) * 180 / M_PI;
//	an.angleVer = atan2(2.0 * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3) * 180 / M_PI;
//
//	an.angleHor = an.angleHor * M_PI / 180.0f;
//	an.anglePar = an.anglePar * M_PI / 180.0f;
//	an.angleHor = an.angleHor * M_PI / 180.0f;
//
//	ResetAngle(&an.angleVer);
//	ResetAngle(&an.anglePar);
//	ResetAngle(&an.angleHor);
//
//	return an;
//}

//Quaternion QuaternionRotate(Quaternion rever, Quaternion move, Quaternion now)
//{
//	Quaternion re;
//
//	re = rever* move* now;
//
//	return re;
//}
