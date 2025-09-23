#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
	hBGImage_ = LoadGraph("image/Title_bg.jpg");
	hTitleImage_ = LoadGraph("image/ÉJÉNÉeÉãÉçÉS.png");

}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("StageSelect");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawExtendGraph(0, 0, 1024, 768, hBGImage_, false);
	DrawExtendGraph(50, 0, 500, 350, hTitleImage_, true);
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
