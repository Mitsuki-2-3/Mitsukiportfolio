#pragma once
#include"common.h"
#include"C3DPrism.h"

#define ONE_ 30 * DX_PI_F / 180;
#define MOVE_ONRCE ONE_ / 90

class FloorManager
{
private:
	VECTOR nowWorldPosi;						//現在の座標
	ST_Angle localAngle;						//現在の三次元角度
	int prismCount = 5;							//床と壁の総数
	int itemCount = 12;							//アイテムの総数
	ACCELERATION acce[4] = { false,0.0f };		//床の四方それぞれの傾き
	C3DPrism** prisms;							//床と壁
	C3DPrism** items;							//アイテム

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

