#include "Playarea.h"
#include "DxLib.h"

Playarea::Playarea():
	GameObject(), areaRect_(PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT)
{
	SetAlive(true); // Playareaを生存状態に設定
	AddGameObject(this); // Playareaをゲームオブジェクトリストに追加
}

Playarea::~Playarea()
{
}

void Playarea::Update()
{
}

void Playarea::Draw()
{
	if (isAlive_)
	{
		DrawBox(areaRect_.x, areaRect_.y, areaRect_.x + areaRect_.w, areaRect_.y + areaRect_.h, GetColor(120, 120, 120), true);
		DrawBox(areaRect_.x, areaRect_.y, areaRect_.x + areaRect_.w, areaRect_.y + areaRect_.h, GetColor(255, 255, 255), false, 3);
	}
}
