#pragma once
#include"DxLib.h"
#include "AbstractScene.h"

// シーンマネージャークラス
class SceneManager : public AbstractScene {
private:
    AbstractScene* mScene;  // 現在のシーン

public:
    // コンストラクタ
    SceneManager(AbstractScene* scene)
        : mScene(scene) {}

    // デストラクタ
    ~SceneManager() 
    {
        delete mScene;
    }

    void Update() override;                     //描画以外の更新
    void Draw() const override;                 //描画に関すること
    AbstractScene* ChangeScene() override;      //シーンの遷移
};