#include "StageSelect.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include <assert.h>
#include "StageData.h"

StageSelect::StageSelect()
{
	
	hImage = LoadGraph("\\image\\sake 1\\sake\\ƒVƒ“ƒfƒŒƒ‰.png");
	
}

StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	int clickstage = -1;

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		if (mouseX >= 0 && mouseX < WIN_WIDTH / 4 && mouseY >= 0 && mouseY < WIN_HEIGHT / 2)
		{
			clickstage = 1;
		}
		else if (mouseX >= WIN_WIDTH && mouseX < WIN_WIDTH / 2 && mouseY >= 0 && mouseY < WIN_HEIGHT / 2)
		{
			clickstage = 2;
		}
		else if (mouseX >= WIN_WIDTH / 2 && mouseX < WIN_WIDTH / 4 * 3 && mouseY >= 0 && mouseY < WIN_HEIGHT / 2)
		{
			clickstage = 3;
		}
		else if (mouseX >= WIN_WIDTH / 4 * 3 && mouseX < WIN_WIDTH && mouseY >= 0 && mouseY < WIN_HEIGHT / 2)
		{
			clickstage = 4;
		}
		else if (mouseX >= 0 && mouseX < WIN_WIDTH / 4 && mouseY >= WIN_HEIGHT / 2 && mouseY < WIN_HEIGHT)
		{
			clickstage = 5;
		}
		else if (mouseX >= WIN_WIDTH / 4 && mouseX < WIN_WIDTH / 2 && mouseY >= WIN_HEIGHT / 2 && mouseY < WIN_HEIGHT)
		{
			clickstage = 6;
		}
		else if (mouseX >= WIN_WIDTH / 2 && mouseX < WIN_WIDTH / 4 * 3 && mouseY >= WIN_HEIGHT / 2 && mouseY < WIN_HEIGHT)
		{
			clickstage = 7;
		}
		else if (mouseX >= WIN_WIDTH / 4 * 3 && mouseX < WIN_WIDTH && mouseY >= WIN_HEIGHT / 2 && mouseY < WIN_HEIGHT)
		{
			clickstage = 8;
		}

	}

	switch (clickstage)
	{
	case 1:
		StageData::stagenum = clickstage;
		SceneManager::ChangeScene("PLAY");
		isAlive_ = false;

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;

	default:
		break;
	}
}

void StageSelect::Draw()
{
	DrawRectGraph(0, 0, WIN_WIDTH / 4, WIN_HEIGHT / 2, WIN_WIDTH / 4, WIN_HEIGHT / 2, hImage, TRUE);
	DrawBox(WIN_WIDTH / 4, 0, WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(0, 255, 0), TRUE);
	DrawBox(WIN_WIDTH / 2, 0, WIN_WIDTH / 4 * 3, WIN_HEIGHT / 2, GetColor(0, 0, 255), TRUE);
	DrawBox(WIN_WIDTH / 4 * 3, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(255, 255, 0), TRUE);

	DrawBox(0, WIN_HEIGHT / 2, WIN_WIDTH / 4, WIN_HEIGHT, GetColor(255, 0, 255), TRUE);
	DrawBox(WIN_WIDTH / 4, WIN_HEIGHT / 2, WIN_WIDTH / 2, WIN_HEIGHT, GetColor(0, 255, 255), TRUE);
	DrawBox(WIN_WIDTH / 2, WIN_HEIGHT / 2, WIN_WIDTH / 4 * 3, WIN_HEIGHT, GetColor(0, 255, 0), TRUE);
	DrawBox(WIN_WIDTH / 4 * 3, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 0, 0), TRUE);
}
