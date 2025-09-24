#include "TitleScene.h"
#include <DxLib.h>
#include "Input.h"

namespace
{
	int LEFT_TOP_X = 312;
	int LEFT_TOP_Y = 400;
	int RIGHT_X = 712;
	int RIGHT_Y = 800;
}

TitleScene::TitleScene()
{
	hBGImage_ = LoadGraph("image/Title_bg.jpg");
	hTitleImage_ = LoadGraph("image/ƒJƒNƒeƒ‹ƒƒS.png");
	hStartButtonImage_ = LoadGraph("image/Start.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		
		if (mouseX > LEFT_TOP_X && RIGHT_X > mouseX && mouseY > LEFT_TOP_Y && RIGHT_Y > mouseY)
		{
			SceneManager::ChangeScene("StageSelect");
		}
		

	}
	
}


void TitleScene::Draw()
{
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawExtendGraph(0, 0, 1024, 768, hBGImage_, false);
	DrawExtendGraph(50, 0, 500, 350, hTitleImage_, true);
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawExtendGraph(LEFT_TOP_X, LEFT_TOP_Y, RIGHT_X, RIGHT_Y, hStartButtonImage_, true);
}
