#include"CheckHit.h"


using namespace std;


//線分が面に当たっているか
ST_CheckHit CheckFaceOfCube(C3DPrism* prism, C3DSphere* sphere)
{
	//移動前と移動後の座標が面を貫通していたら
	//必要なデータの保存
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

//球と立方体に含まれる面との当たり判定
ST_CheckHit Check3DQuadrangularPrism(C3DPrism* prism, C3DSphere* sphere)
{
	ST_CheckHit result = { false,VGet(0,0,0),VGet(0,0,0) };
	ST_Surfaces* check = prism->GetSuface();
	//判定用のベクトル始点
	VECTOR sphereS = sphere->GetNowPosition();
	//判定用のベクトル終点
	VECTOR sphereF;
	//移動前と移動後の座標が面を貫通していたら
	for (int i = 0; i < 6; i++) 
	{
		//必要なデータの保存
		//判定結果用
		ST_Surfaces surface = check[i];

		//球のサイズと移動量ベクトルの大きさ比較
		if (VSize(sphere->GetMoveVector()) > sphere->GetRadius()) {
			//移動量が大きい時
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (VSize(sphere->GetMoveVector())) * -1;
		}
		else {
			//サイズが大きい時
			sphereF = sphere->GetNowPosition() + surface.normal 
				* (sphere->GetRadius()) * -1;
		}
		//三角ポリゴン判定用1・2
		ST_CheckHit hit1, hit2;

		//ポリゴンと線分の判定1
		hit1 = CheckLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[0][0].VFloor(), surface.poly[0][1].VFloor(),
			surface.poly[0][2].VFloor());
		//ポリゴンと線分の判定2
		hit2 = CheckLineSegmentAndPolygon(sphereS, sphereF,
			surface.poly[1][0].VFloor(), surface.poly[1][1].VFloor(),
			surface.poly[1][2].VFloor());

		//どちらかに当たっている場合
		if (hit1.hit == true || hit2.hit == true)
		{
			result.hit = true;
			if (hit1.hit == true) 
			{
				//線分と面の交差点の座標から球の半径分ずらす
				result.hitposi = hit1.hitposi.VFloor()
					+ surface.normal * (sphere->GetRadius()
						+ sphere->GetRadius() / 20.0f);
			}
			if (hit2.hit == true)
			{
				//線分と面の交差点の座標から球の半径分ずらす
				result.hitposi = hit2.hitposi.VFloor()
					+ surface.normal * (sphere->GetRadius()
						+ sphere->GetRadius() / 20.0f);
			}
			//ポリゴンの法線ベクトルを返す
			result.normalize = surface.normal;
			return result;
		}
	}
	return result;
}

//球と傾かない立方体の当たり判定
bool AABBPrism(C3DPrism* prism, C3DSphere* sphere)
{
	//使う変数を一時的に保存
	VECTOR G = prism->GetNowPosi();
	VECTOR nowSpherePosi = VSub(sphere->GetNowPosition() , G);
	float center[3] = { nowSpherePosi.x,nowSpherePosi.y,nowSpherePosi.z };
	float pr[3] = { G.x,G.y,G.z };
	float* size = prism->GetSize();
	float vec = 0;
	float s = 0;
	float vsize = 0;

	//立方体の座標＋大きさと球の中心座標を比較し
	//はみ出している分を保存
	for (int i = 0; i < 3; i++) {
		//大きさ用
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

	//はみ出している分が球の半径より小さいかどうか
	if (vec <= sphere->GetRadius()*sphere->GetRadius())
	{
		//小さいので当たっている
		return true;
	}
	//当たっていない
	return false;
}

//球と傾かむく立方体の当たり判定
bool OBBPrism(C3DPrism* prism, C3DSphere* sphere)
{
	//使う変数を一時的に保存
	VECTOR G = prism->GetNowPosi()  ;
	VECTOR nowSpherePosi = sphere->GetNowPosition();
	VECTOR* dic = prism->Getdic();
	VECTOR vec = { 0 };
	VECTOR vect[3] = { 0 };
	float L = 0;
	float s[3] = { 0 };
	float* vsize = prism->GetSize();

	//立方体の座標＋大きさと球の中心座標を比較し
	//はみ出している分のベクトルを保存
	for (int i = 0; i < 3; i++) {
		//大きさ
		L = vsize[i];
		if (L <= 0)continue;
		//球から立方体へのベクトルと傾いてる辺ベクトルの内積を本来の辺の大きさで割る
		s[i] = VDot(nowSpherePosi - G, dic[i]) / L;
		//絶対値を上書き
		s[i] = fabsf(s[i]);
		//1より大きい時
		if (s[i] > 1) {
			//はみ出している分のベクトルを保存
			vec += dic[i] * ((1 - s[i]) * L);
		}
	}

	//はみ出しているベクトルのサイズがが球の半径より小さいかどうか
	if (VSize(vec) < sphere->GetRadius())
	{
		//小さいので当たっている
		return true;
	}
	return false;
}