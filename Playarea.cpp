#include "Playarea.h"
#include "DxLib.h"

Playarea::Playarea():
	GameObject(), areaRect_(PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT)
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
