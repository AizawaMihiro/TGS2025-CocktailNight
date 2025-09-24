#include "StageSelect.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include <assert.h>
#include "StageData.h"

StageSelect::StageSelect()
{
	hBGImage_ = LoadGraph("image/Title_bg.jpg");
	for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
	{
		switch (i)
		{
		case 0:
			stageRect_[i] = { SELECT_MARGIN_LEFT, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_1_outline.png");
		break;
		case 1:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH + SELECT_WIDTH, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_2_outline.png");
		break;
		case 2:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH+ SELECT_GAP_WIDTH + SELECT_WIDTH*2, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_3_outline.png");
			break;
		case 3:
			stageRect_[i] = { SELECT_MARGIN_LEFT+ SELECT_GAP_WIDTH*2+ SELECT_GAP_WIDTH_MID + SELECT_WIDTH*3, SELECT_MARGIN_TOP, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_4_outline.png");
			break;
		case 4:
			stageRect_[i] = { SELECT_MARGIN_LEFT, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT+ SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_5_outline.png");
			break;
		case 5:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH + SELECT_WIDTH, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_6_outline.png");
			break;
		case 6:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH + SELECT_GAP_WIDTH + SELECT_WIDTH*2, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_7_outline.png");
			break;
		case 7:
			stageRect_[i] = { SELECT_MARGIN_LEFT + SELECT_GAP_WIDTH * 2 + SELECT_GAP_WIDTH_MID + SELECT_WIDTH*3, SELECT_MARGIN_TOP+ SELECT_GAP_HEIGHT + SELECT_HEIGHT, SELECT_WIDTH, SELECT_HEIGHT };
			hNumImage_[i] = LoadGraph("image/number/keyboard_8_outline.png");
			break;
		default:
			break;
		}
	}
}

StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
		{
			if (mouseX >= stageRect_[i].x && mouseX < stageRect_[i].x + stageRect_[i].w && mouseY >= stageRect_[i].y && mouseY < stageRect_[i].y+ stageRect_[i].h)
			{
				selectedStage_ = i + 1;
			}
		}

	}

	if (selectedStage_ != -1)
	{
		StageData::stagenum = selectedStage_;
		SceneManager::ChangeScene("PLAY");
		isAlive_ = false;
	}
	
}

void StageSelect::Draw()
{
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBGImage_, 0);
	for (int i = 0; i < SELECTABLE_STAGE_NUM; i++)
	{
		DrawBox(stageRect_[i].x, stageRect_[i].y, stageRect_[i].x + stageRect_[i].w, stageRect_[i].y + stageRect_[i].h, GetColor(150, 70, 20), true);
		DrawExtendGraph(stageRect_[i].x, stageRect_[i].y, stageRect_[i].x + stageRect_[i].w, stageRect_[i].y + stageRect_[i].h, hNumImage_[i], true);
	}
}
