#include "C3DItem.h"


C3DItem::C3DItem(VECTOR worldposi, VECTOR localposi, ST_Angle* _worldAngle, ST_Angle _localangle, VECTOR _size)
	:C3DPrism(worldposi, localposi, _worldAngle,_localangle,_size)
{
}

void C3DItem::Updata()
{
	////���݂̌X������l�ʑ̂��ꂼ��̒��_�ʒu���v�Z
	float saveX = -1;
	float saveY = -1;
	float saveZ = -1;

	nowWorldPosi = MoveRotation(nowChildPosi, *worldAngle);

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

	//�l�ʑ̖̂ʂ̒��S�ʒu
	for (int i = 0; i < 6; i++) {
		surface[i].surface = nowWorldPosi + MoveRotation(MoveRotation(surface[i].size, *worldAngle), localAngle);
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

	//�l�ʑ̏�̖ʂ̖@�����v�Z
	for (int i = 0; i < 6; i++) {
		surface[i].normal = MoveRotation(MoveRotation(no[i], *worldAngle),localAngle);
	}

	//direct[0] = VNorm(MoveRotation(MoveRotation(VGet(size[0], 0, 0), *worldAngle), localAngle));
	//direct[1] = VNorm(MoveRotation(MoveRotation(VGet(0, size[1], 0), *worldAngle),localAngle));
	//direct[2] = VNorm(MoveRotation(MoveRotation(VGet(0, 0, size[2]), *worldAngle),localAngle));
	direct[0] = VNorm(MoveRotation(VGet(size[0], 0, 0), localAngle));
	direct[1] = VNorm(MoveRotation(VGet(0, size[1], 0), localAngle));
	direct[2] = VNorm(MoveRotation(VGet(0, 0, size[2]), localAngle));
}

