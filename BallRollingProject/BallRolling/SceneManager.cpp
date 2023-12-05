#include "Controll.h"
#include "SceneManager.h"

// メンバ変数の値を書き換えるのがアップデート関数
void SceneManager::Update() {
    Controll::Update();
    KeyManager::Update();
    // 現在シーンのアップデートを実行
    mScene->Update();
}

// 描画処理のみを行う関数
void SceneManager::Draw() const {
    // 現在シーンの描画関数を実行
        mScene->Draw();
}

AbstractScene* SceneManager::ChangeScene()
{
    AbstractScene* nextScene = mScene;

    //現在のシーンから次のシーンを受け取る
    nextScene = mScene->ChangeScene();

    // 次のシーンが現在シーンと違う場合切り替える
    if (nextScene != mScene) {
        delete mScene;
        mScene = nextScene;
    }

    if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE) || Controll::JudgePressButton(XINPUT_BUTTON_BACK))
    {
        //キーボードのエスケープかコントローラーのBACKを押したとき強制終了
        return nullptr;
    }

    return nextScene;
}