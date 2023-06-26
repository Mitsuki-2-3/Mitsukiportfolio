#include "Controll.h"
#include "SceneManager.h"

// �����o�ϐ��̒l������������̂��A�b�v�f�[�g�֐�
void SceneManager::Update() {
    Controll::Update();
    KeyManager::Update();
    // ���݃V�[���̃A�b�v�f�[�g�����s
    mScene->Update();
}

// �`�揈���݂̂��s���֐�
void SceneManager::Draw() const {
    // ���݃V�[���̕`��֐������s
        mScene->Draw();
}

AbstractScene* SceneManager::ChangeScene()
{
    AbstractScene* nextScene = mScene;

    nextScene = mScene->ChangeScene();

    // ���̃V�[�������݃V�[���ƈႤ�ꍇ�؂�ւ���
    if (nextScene != mScene) {
        delete mScene;
        mScene = nextScene;
    }

    if (KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE) || Controll::JudgePressButton(XINPUT_BUTTON_BACK))
    {
        return nullptr;
    }

    return nextScene;
}