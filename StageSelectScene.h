#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class StageSelectScene : public SceneBase
{
public:
	StageSelectScene();
	~StageSelectScene();
	void Update() override;
	void Draw() override;
};
