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
  

	////���݂̌X������l�ʑ̂��ꂼ��̒��_�ʒu���v�Z
	float saveX = -1;
	float saveY = -1;
	float saveZ = -1;

	nowWorldPosi = nowParentPosi + MoveRotation((nowChildPosi), *worldAngle);

	//�ʂ̃T�C�Y
	for (int i = 0; i < 6; i++)
	{
		surface[i].size = VGet(no[i].x * size[0], no[i].y * size[1], no[i].z * size[2]);
	}

	//�l�ʑ̖̂ʂ̒��S�ʒu
	for (int i = 0; i < 6; i++) {
		surface[i].surface = nowWorldPosi + MoveRotation(MoveRotation(surface[i].size, localAngle), *worldAngle);
	}

	//�l�ʑ̂̒��_���W���X�V
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

	//�l�ʑ̖̂ʂ̒��_�ۑ�
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

//�f�X�g���N�^
C3DPrism::~C3DPrism()
{
	delete surface;
	delete polyPosi;
}


void C3DPrism::Updata()
{
	////���݂̌X������l�ʑ̂��ꂼ��̒��_�ʒu���v�Z
	float saveX = -1;
	float saveY = -1;
	float saveZ = -1;

	//���[���h���W�̕ۑ�
	nowWorldPosi = nowParentPosi + MoveRotation((nowChildPosi), *worldAngle);

	//�l�ʑ̂̒��_���W���X�V
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

	//�l�ʑ̖̂ʂ̒��S�ʒu�̍X�V
	for (int i = 0; i < 6; i++) {
		surface[i].surface = nowWorldPosi + MoveRotation(MoveRotation(surface[i].size, localAngle), *worldAngle);
	}

	//�l�ʑ̖̂ʂɒ��_���W�����Ȃ���
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

	//�l�ʑ̏�̖ʂ̖@�����v�Z
	for (int i = 0; i < 6; i++) {
		surface[i].normal = MoveRotation(MoveRotation(no[i], localAngle), *worldAngle);
	}

	//�����蔻��p�̒P�ʃx�N�g��
	direct[0] = VNorm(MoveRotation(MoveRotation(VGet(size[0], 0, 0), localAngle), *worldAngle));
	direct[1] = VNorm(MoveRotation(MoveRotation(VGet(0, size[1], 0), localAngle), *worldAngle));
	direct[2] = VNorm(MoveRotation(MoveRotation(VGet(0, 0, size[2]), localAngle), *worldAngle));
}

void C3DPrism::Draw(int color) const
{
	//�����̖̂ʂ�`��
	for (int i = 0; i < 12; i++) {
		int i0 = idx[3 * i + 0];
		int i1 = idx[3 * i + 1];
		int i2 = idx[3 * i + 2];

		int addColor = i / 2;

		DrawTriangle3D(polyPosi[i0], polyPosi[i1], polyPosi[i2],
			Color::color[color], TRUE);
	}

	int b = 6;

	//�����̂̕ӂ�`��
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