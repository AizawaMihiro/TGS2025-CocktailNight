#include "Piece.h"
#include "DxLib.h"

Piece::Piece():
	GameObject()
{
	Pos_ = { PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }; // 初期位置とサイズを設定
	type_ = 0; // ピースの種類を初期化
	hImage_ = LoadGraph("image/test/keyboard_0.png", 1);
	isSelected_ = false;
	isDrawable_ = false;
	SetAlive(true);
	AddGameObject(this);
}

Piece::Piece(Rect pos, int type) :
	GameObject(), Pos_(pos), type_(type), VerchainCounter_(0), HorchainCounter_(0)
{
	switch (type_)
	{
	case 0:
		hImage_ = LoadGraph("image/piece/Piece1.png", 1);
		break;
	case 1:
		hImage_ = LoadGraph("image/piece/Piece2.png", 1);
		break;
	case 2:
		hImage_ = LoadGraph("image/piece/Piece3.png", 1);
		break;
	case 3:
		hImage_ = LoadGraph("image/piece/Piece4.png", 1);
		break;
	case 4:
		hImage_ = LoadGraph("image/piece/Piece5.png", 1);
		break;
	case 5:
		hImage_ = LoadGraph("image/piece/Piece6.png", 1);
		break;
	case 6:
		hImage_ = LoadGraph("image/piece/Piece7.png", 1);
		break;
	case 7:
		hImage_ = LoadGraph("image/piece/Piece8.png", 1);
		break;
	default:
		break;
	}
	isSelected_ = false;
	isDrawable_ = true;
	isChain_ = false;
	isVerticalChain_ = false;
	isHorizontalChain_ = false;
	SetAlive(true);
	SetPriority(40);
	AddGameObject(this);
}

Piece::~Piece()
{
	if (hImage_ != -1) {
		DeleteGraph(hImage_);
		hImage_ = -1;
	}
	isAlive_ = false;
}

void Piece::Update()
{
}

void Piece::Draw()
{
	if (isDrawable_)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		//DrawExtendGraph(Pos_.x, Pos_.y, Pos_.x + Pos_.w, Pos_.y + Pos_.h, hImage_, 0);
		//縮小表示中
		DrawExtendGraph(Pos_.x+3, Pos_.y+3, Pos_.x + Pos_.w-3, Pos_.y + Pos_.h-3, hImage_, 0);
	}
}

