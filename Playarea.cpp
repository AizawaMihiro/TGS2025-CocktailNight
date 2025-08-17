#include "Playarea.h"
#include "DxLib.h"
#include "Input.h"

Playarea::Playarea():
	GameObject(), areaRect_(PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT),selected_(-1,-1),preSelect_(-1)
{
	for (int i = 0; i < PLAYAREA_GRID_NUM_X * PLAYAREA_GRID_NUM_Y; i++) {
		float x = (i % (PLAYAREA_GRID_NUM_X)) * PLAYAREA_GRID_WIDTH + PLAYAREA_MARGIN_LEFT;
		float y = (i / (PLAYAREA_GRID_NUM_X)) * PLAYAREA_GRID_HEIGHT + PLAYAREA_MARGIN_TOP;
		pieces_.push_back(new Piece({ x, y, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT },i%7));
	}
	SetAlive(true);
	AddGameObject(this);
}

Playarea::~Playarea()
{
	for (auto piece : pieces_) {
		delete piece; // 各ピースのメモリを解放
	}
	pieces_.clear(); // ピースのリストをクリア
	SetAlive(false); // プレイエリアを非アクティブにする
}

void Playarea::Update()
{
    int mouseX, mouseY;
    if (GetMousePoint(&mouseX, &mouseY) == -1)
    {
        return;
    }
	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		isHold_ = true;
	}
	isInPlayArea_ = (mouseX > areaRect_.x && mouseX < areaRect_.x + areaRect_.w &&
        mouseY > areaRect_.y && mouseY < areaRect_.y + areaRect_.h);
	if (isInPlayArea_) {
		selected_.x = (mouseX - areaRect_.x) / PLAYAREA_GRID_WIDTH;
		selected_.y = (mouseY - areaRect_.y) / PLAYAREA_GRID_HEIGHT;
		int selectNum = (int)selected_.y * PLAYAREA_GRID_NUM_X + (int)selected_.x;
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", selectNum);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", preSelect_);

		if (isHold_)
		{
			DrawFormatString(0, 40, GetColor(255, 255, 255), "HOLD!");
			if (preSelect_ != selectNum)
			{
				int sub = preSelect_ - selectNum;
				DrawFormatString(0, 60, GetColor(255, 255, 255), "%d", sub);
				SwapPosPiece(preSelect_, selectNum);
			}
			isHold_ = false;
		}
		preSelect_ = selectNum;
	}
}

void Playarea::Draw()
{
	if (isAlive_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
		DrawBox(areaRect_.x, areaRect_.y, areaRect_.x + areaRect_.w, areaRect_.y + areaRect_.h, GetColor(120, 120, 120), true);
		for (int i = 0; i < PLAYAREA_GRID_NUM_X; i++)
		{
			DrawLine(areaRect_.x + i * PLAYAREA_GRID_WIDTH, areaRect_.y, areaRect_.x + i * PLAYAREA_GRID_WIDTH, areaRect_.y + areaRect_.h, GetColor(255, 255, 255));
			for (int j = 0; j < PLAYAREA_GRID_NUM_Y; j++)
			{
				DrawLine(areaRect_.x, areaRect_.y + j * PLAYAREA_GRID_HEIGHT, areaRect_.x + areaRect_.w, areaRect_.y + j * PLAYAREA_GRID_HEIGHT, GetColor(255, 255, 255));
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawBox(areaRect_.x, areaRect_.y, areaRect_.x + areaRect_.w, areaRect_.y + areaRect_.h, GetColor(255, 255, 255), false, 3);
	}
}

void Playarea::SwapPosPiece(int a, int b)
{
	if (a <= pieces_.size() && b <= pieces_.size())
	{
		Piece* blankP = new Piece;
		blankP->SetPos(pieces_[a]->GetPos());
		pieces_[a]->SetPos(pieces_[b]->GetPos());
		pieces_[b]->SetPos(blankP->GetPos());
		blankP->SetAlive(false);
	}
}
