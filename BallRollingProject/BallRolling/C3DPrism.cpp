#include "C3DPrism.h"

C3DPrism::C3DPrism(VECTOR parentposi, VECTOR localposi, ST_Angle* _angle, ST_Angle _localangle, VECTOR _size)
{
	nowParentPosi = parentposi;
	nowChildPosi = localposi;

	worldAngle = _angle;
	localAngle = _localangle;

	poly = 4 * 2;

	size[0] = _size.x/2;
	size[1] = _size.y/2;
	size[2] = _size.z/2;

	int face = abs(poly - (4 * 3) - 2);
	surface = new ST_Surfaces [face];
	
	polyPosi = new VECTOR[poly];
  

	////現在の傾きから四面体それぞれの頂点位置を計算
	float saveX = -1;
	float saveY = -1;
	float saveZ = -1;

	nowWorldPosi = nowParentPosi + MoveRotation((nowChildPosi), *worldAngle);

	//面のサイズ
	for (int i = 0; i < 6; i++)
	{
		surface[i].size = VGet(no[i].x * size[0], no[i].y * size[1], no[i].z * size[2]);
	}

	//四面体の面の中心位置
	for (int i = 0; i < 6; i++) {
		surface[i].surface = nowWorldPosi + MoveRotation(MoveRotation(surface[i].size, localAngle), *worldAngle);
	}

	//四面体の頂点座標を更新
	for (int i = 0; i < poly; i++)
	{
		polyPosi[i] = nowWorldPosi + MoveRotation(MoveRotation(
			VGet(size[0] * saveX, size[1] * saveY, size[2] * saveZ), localAngle), *worldAngle);
		saveZ = saveZ * -1;
		if ((i + 1) % 2 == 0) {
			saveX = saveX * -1;
		}
		if ((i + 1) % 4 == 0) {
			saveY = saveY * -1;
		}
	}

	//四面体の面の頂点保存
	for (int i = 0; i < 6; i++) {
		int i0 = idx[6 * i + 0];
		int i1 = idx[6 * i + 1];
		int i2 = idx[6 * i + 2];
		int i3 = idx[6 * i + 3];
		int i4 = idx[6 * i + 4];
		int i5 = idx[6 * i + 5];

		surface[i].poly[0][0] = polyPosi[i0];
		surface[i].poly[0][1] = polyPosi[i1];
		surface[i].poly[0][2] = polyPosi[i2];
		surface[i].poly[1][0] = polyPosi[i3];
		surface[i].poly[1][1] = polyPosi[i4];
		surface[i].poly[1][2] = polyPosi[i5];
	}



}

//デストラクタ
C3DPrism::~C3DPrism()
{
	delete surface;
	delete polyPosi;
}


void C3DPrism::Updata()
{
	////現在の傾きから四面体それぞれの頂点位置を計算
	float saveX = -1;
	float saveY = -1;
	float saveZ = -1;

	//ワールド座標の保存
	nowWorldPosi = nowParentPosi + MoveRotation((nowChildPosi), *worldAngle);

	//四面体の頂点座標を更新
	for (int i = 0; i < poly; i++)
	{
		polyPosi[i] = nowWorldPosi + MoveRotation(
			MoveRotation(VGet(size[0] * saveX, size[1] * saveY, size[2] * saveZ), localAngle), *worldAngle);
		saveZ = saveZ * -1;
		if ((i + 1) % 2 == 0) {
			saveX = saveX * -1;
		}
		if ((i + 1) % 4 == 0) {
			saveY = saveY * -1;
		}
	}

	//四面体の面の中心位置の更新
	for (int i = 0; i < 6; i++) {
		surface[i].surface = nowWorldPosi + MoveRotation(MoveRotation(surface[i].size, localAngle), *worldAngle);
	}

	//四面体の面に頂点座標を入れなおし
	for (int i = 0; i < 6; i++) {
		int i0 = idx[6 * i + 0];
		int i1 = idx[6 * i + 1];
		int i2 = idx[6 * i + 2];
		int i3 = idx[6 * i + 3];
		int i4 = idx[6 * i + 4];
		int i5 = idx[6 * i + 5];

		surface[i].poly[0][0] = polyPosi[i0];
		surface[i].poly[0][1] = polyPosi[i1];
		surface[i].poly[0][2] = polyPosi[i2];
		surface[i].poly[1][0] = polyPosi[i3];
		surface[i].poly[1][1] = polyPosi[i4];
		surface[i].poly[1][2] = polyPosi[i5];
	}

	//四面体上の面の法線を計算
	for (int i = 0; i < 6; i++) {
		surface[i].normal = MoveRotation(MoveRotation(no[i], localAngle), *worldAngle);
	}

	//当たり判定用の単位ベクトル
	direct[0] = VNorm(MoveRotation(MoveRotation(VGet(size[0], 0, 0), localAngle), *worldAngle));
	direct[1] = VNorm(MoveRotation(MoveRotation(VGet(0, size[1], 0), localAngle), *worldAngle));
	direct[2] = VNorm(MoveRotation(MoveRotation(VGet(0, 0, size[2]), localAngle), *worldAngle));
}

void C3DPrism::Draw(int color) const
{
	//立方体の面を描画
	for (int i = 0; i < 12; i++) {
		int i0 = idx[3 * i + 0];
		int i1 = idx[3 * i + 1];
		int i2 = idx[3 * i + 2];

		int addColor = i / 2;

		DrawTriangle3D(polyPosi[i0], polyPosi[i1], polyPosi[i2],
			Color::color[color], TRUE);
	}

	int b = 6;

	//立方体の辺を描画
	for (int i = 0; i < 6; i++)
	{
		int i0 = idx[i * b];
		int i1 = idx[i * b + 1];
		int i2 = idx[i * b + 2];
		int i3 = idx[i * b + 3];

		DrawLine3D(polyPosi[i0], polyPosi[i1], Color::color[COLORTYPE::LINE]);
		DrawLine3D(polyPosi[i1], polyPosi[i3], Color::color[COLORTYPE::LINE]);
		DrawLine3D(polyPosi[i3], polyPosi[i2], Color::color[COLORTYPE::LINE]);
		DrawLine3D(polyPosi[i0], polyPosi[i2], Color::color[COLORTYPE::LINE]);
	}
}