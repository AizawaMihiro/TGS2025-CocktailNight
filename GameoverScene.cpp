#include "GameoverScene.h"
#include <DxLib.h>

GameoverScene::GameoverScene()
{
}

GameoverScene::~GameoverScene()
{
}

void GameoverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("StageSelect");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void GameoverScene::Draw()
{
	DrawString(100, 100, "GAME OVER", GetColor(255, 255, 255));
	DrawString(100, 600, "Push [S]Key To StageSelect", GetColor(255, 255, 255));
}
