#pragma once
#include "AbstractScene.h"
#include"common.h"

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

	
    int count;

	Rainbow color;
	int current;

public:
    GameClearScene();

    void Update() override;
    void Draw() const override;
    AbstractScene* ChangeScene() override;
};

