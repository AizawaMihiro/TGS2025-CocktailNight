#include "GameoverScene.h"
#include <DxLib.h>
#include "Input.h"

GameoverScene::GameoverScene()
{
}

GameoverScene::~GameoverScene()
{
}

void GameoverScene::Update()
{
	
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{

		SceneManager::ChangeScene("StageSelect");
	}

}

void GameoverScene::Draw()
{
	DrawString(100, 100, "GAME OVER", GetColor(255, 255, 255));
	//DrawString(100, 600, "Push [S]Key To StageSelect", GetColor(255, 255, 255));
}
