#include "Piece.h"
#include "DxLib.h"

Piece::Piece():
	GameObject()
{
	Pos_ = { PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }; // 初期位置とサイズを設定
	type_ = 0; // ピースの種類を初期化
	hImage_ = LoadGraph("image/keyboard_0.png", 1);
	isSelected_ = false;
	SetAlive(true);
	AddGameObject(this);
}

Piece::Piece(Rect pos, int type) :
	GameObject(), Pos_(pos), type_(type)
{
	switch (type_)
	{
	case 0:
		hImage_ = LoadGraph("image/keyboard_0.png", 1);
		break;
	case 1:
		hImage_ = LoadGraph("image/keyboard_1.png", 1);
		break;
	case 2:
		hImage_ = LoadGraph("image/keyboard_2.png", 1);
		break;
	case 3:
		hImage_ = LoadGraph("image/keyboard_3.png", 1);
		break;
	case 4:
		hImage_ = LoadGraph("image/keyboard_4.png", 1);
		break;
	case 5:
		hImage_ = LoadGraph("image/keyboard_5.png", 1);
		break;
	case 6:
		hImage_ = LoadGraph("image/keyboard_6.png", 1);
		break;
	default:
		break;
	}
	isSelected_ = false;
	SetAlive(true);
	AddGameObject(this);
}

Piece::~Piece()
{
}

void Piece::Update()
{
}

void Piece::Draw()
{
	DrawExtendGraph(Pos_.x, Pos_.y, Pos_.x + Pos_.w, Pos_.y + Pos_.h, hImage_, 0);
}
