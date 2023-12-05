#pragma once
#include"DxLib.h"
#include "AbstractScene.h"

// �V�[���}�l�[�W���[�N���X
class SceneManager : public AbstractScene {
private:
    AbstractScene* mScene;  // ���݂̃V�[��

public:
    // �R���X�g���N�^
    SceneManager(AbstractScene* scene)
        : mScene(scene) {}

    // �f�X�g���N�^
    ~SceneManager() 
    {
        delete mScene;
    }

    void Update() override;                     //�`��ȊO�̍X�V
    void Draw() const override;                 //�`��Ɋւ��邱��
    AbstractScene* ChangeScene() override;      //�V�[���̑J��
};