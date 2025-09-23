#include "StageSelect.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include <assert.h>
#include "StageData.h"

StageSelect::StageSelect()
{
	hImage = LoadGraph("\\image\\sake 1\\sake\\ƒVƒ“ƒfƒŒƒ‰.png");
	for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
	{
		switch (i)
		{
		case 0:
			stageRect_[i] = { SELECT_MARGIN_LEFT, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
		break;
		case 1:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH + SELECT_WIDTH, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
		break;
		case 2:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH+ SELECT_GAP_WIDTH + SELECT_WIDTH*2, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		case 3:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH*2+ SELECT_GAP_WIDTH_MID + SELECT_WIDTH*3, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		case 4:
			stageRect_[i] = { SELECT_MARGIN_LEFT, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT+ SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		case 5:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH + SELECT_WIDTH, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		case 6:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH + SELECT_GAP_WIDTH + SELECT_WIDTH*2, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		case 7:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH * 2 + SELECT_GAP_WIDTH_MID + SELECT_WIDTH*3, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			break;
		default:
			break;
		}
	}
	SetAlive(true);
	SetPriority(0);
	AddGameObject(this);
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
		for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
		{
			if (mouseX >= stageRect_[i].x && mouseX < stageRect_[i].x + stageRect_[i].w && mouseY >= stageRect_[i].y && mouseY < stageRect_[i].y+ stageRect_[i].h)
			{
				clickstage = i + 1;
			}
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
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hImage_, 0);
	for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
	{
		DrawBox(stageRect_[i].x, stageRect_[i].y, stageRect_[i].x + stageRect_[i].w, stageRect_[i].y + stageRect_[i].h, GetColor(150, 70, 20), true);
	}
}
