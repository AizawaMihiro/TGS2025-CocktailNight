#include "Playarea.h"
#include "DxLib.h"
#include "Input.h"

Playarea::Playarea():
	GameObject(), areaRect_(PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT),
	selected_(-1,-1),preSelect_(-1),isHold_(false),isPush_(false)
{
	hImage_ = LoadGraph("image/BG_bar.jpg");
	for (int i = 0; i < PLAYAREA_GRID_NUM_X * PLAYAREA_GRID_NUM_Y; i++) {
		float x = (i % (PLAYAREA_GRID_NUM_X)) * PLAYAREA_GRID_WIDTH + PLAYAREA_MARGIN_LEFT;
		float y = (i / (PLAYAREA_GRID_NUM_X)) * PLAYAREA_GRID_HEIGHT + PLAYAREA_MARGIN_TOP;
		pieces_.push_back(new Piece({ x, y, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT },i%7));
	}
	playBGM_ = LoadSoundMem("sound/Tenacity.mp3");
	pieceSelectSound_ = LoadSoundMem("sound/se/炊飯器のふたを閉める.mp3");
	pieceSwapSound_ = LoadSoundMem("sound/se/ニュッ1.mp3");
	ChangeVolumeSoundMem(255 * 0.5, playBGM_);//BGMの音量を調整
	PlaySoundMem(playBGM_, DX_PLAYTYPE_LOOP);
	SetAlive(true);
	SetPriority(10);
	AddGameObject(this);
}

Playarea::~Playarea()
{
	for (auto piece : pieces_) {
		delete piece; // 各ピースのメモリを解放
	}
	pieces_.clear(); // ピースのリストをクリア
	if (hImage_ != -1) {
		DeleteGraph(hImage_);
		hImage_ = -1;
	}
	if (playBGM_ != -1) {
		DeleteSoundMem(playBGM_);
		playBGM_ = -1;
	}
	SetAlive(false); // プレイエリアを非アクティブにする
}

void Playarea::Update()
{
    int mouseX, mouseY;
    if (GetMousePoint(&mouseX, &mouseY) == -1)
    {
        return;
    }
	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		PlaySoundMem(pieceSelectSound_, DX_PLAYTYPE_BACK);
		isPush_ = true;
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
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", selectNum);
		//DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", preSelect_);

		if (isHold_)
		{
			if (isPush_)
			{
				if (preSelect_ != selectNum)
				{
					SwapPosPiece(preSelect_, selectNum);
					PlaySoundMem(pieceSwapSound_, DX_PLAYTYPE_BACK);

					CheckPieceChaind();
					isPush_ = false;
				}
			}
		}
		isHold_ = false;
		preSelect_ = selectNum;
	}
}

void Playarea::Draw()
{
	if (isAlive_)
	{
		DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hImage_,0);
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
		//位置情報の交換
		Piece* blankP = new Piece;
		blankP->SetPos(pieces_[a]->GetPos());
		pieces_[a]->SetPos(pieces_[b]->GetPos());
		pieces_[b]->SetPos(blankP->GetPos());
		blankP->SetAlive(false);

		//配列内の位置交換
		std::vector<Piece*> swaped = pieces_;
		swaped.erase(swaped.begin() + a);
		swaped.insert(swaped.begin() + a, pieces_[b]);
		swaped.erase(swaped.begin() + b);
		swaped.insert(swaped.begin() + b, pieces_[a]);
		pieces_.swap(swaped);
		swaped.clear();
	}
}

void Playarea::CheckPieceChaind()
{
	//垂直方向の確認
	for (int i = 0; i < PLAYAREA_GRID_NUM_X; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_Y; j++)
		{
			if (i-1>=0 && i+1<PLAYAREA_GRID_NUM_X)
			{
				int checkPoint = i * PLAYAREA_GRID_NUM_X + j;
				int tTester = pieces_[checkPoint]->GetType();
				if (tTester == pieces_[(i+1)*PLAYAREA_GRID_NUM_X +j]->GetType())
				{
					pieces_[checkPoint]->SetChainFlag(true);
					pieces_[checkPoint]->SetChainCounter(1);
				}
				if (tTester == pieces_[(i - 1) * PLAYAREA_GRID_NUM_X + j]->GetType())
				{
					pieces_[checkPoint]->SetChainCounter(pieces_[(i - 1) * PLAYAREA_GRID_NUM_X + j]->GetChainCounter()+1);
				}

			}
		}
	}

	//水平方向の確認

	//特殊ボムの確認

	//消去処理
}
