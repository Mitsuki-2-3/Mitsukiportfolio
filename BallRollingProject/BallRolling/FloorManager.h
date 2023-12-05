#pragma once
#include"common.h"
#include"C3DPrism.h"

#define ONE_ 30 * DX_PI_F / 180;
#define MOVE_ONRCE ONE_ / 90

class FloorManager
{
private:
	VECTOR nowWorldPosi;						//���݂̍��W
	ST_Angle localAngle;						//���݂̎O�����p�x
	int prismCount = 5;							//���ƕǂ̑���
	int itemCount = 12;							//�A�C�e���̑���
	ACCELERATION acce[4] = { false,0.0f };		//���̎l�����ꂼ��̌X��
	C3DPrism** prisms;							//���ƕ�
	C3DPrism** items;							//�A�C�e��

public:

	FloorManager(VECTOR _posi, ST_Angle _angle);
	~FloorManager();

	void Updata();

	void Draw() const;

	C3DPrism** GetPrisms() { return prisms; }
	C3DPrism* GetPrismSpecity(int i) { return prisms[i]; }
	C3DPrism** GetItems() { return items; }
	C3DPrism* GetItemSpecity(int i) { return items[i]; }
	void DeleteItem(int i) { items[i] = nullptr; }
	int GetPrismCount() { return prismCount; }
	int GetItemCount() { return itemCount; }
};

