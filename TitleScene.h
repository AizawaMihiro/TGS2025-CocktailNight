#pragma once
#include "SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class TitleScene : public SceneBase
{
private:
	int hBGImage_;
	int hTitleImage_;
	int hStartButtonImage_;
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
};
