#pragma once
#include "AbstractScene.h"
#include"common.h"

//色
struct Rainbow
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	bool operator==(Rainbow color)
	{
		if (this->red == color.red) {
			if (this->green == color.green) {
				if (this->blue == color.blue) {
					return true;
				}
			}
		}
		return false;
	}
};

class GameClearScene :
    public AbstractScene
{
private:

	Rainbow color;		//色
	int current;		//次の色の配列番号

public:
    GameClearScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* ChangeScene() override;
};

