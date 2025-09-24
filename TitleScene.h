#pragma once
#include "SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
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
