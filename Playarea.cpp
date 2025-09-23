#include "Playarea.h"
#include "DxLib.h"
#include "Input.h"

Playarea::Playarea():
	GameObject(), areaRect_(PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT),
	selected_(-1,-1),preSelect_(-1),isHold_(false),isPush_(false)
{
	hImage_ = LoadGraph("image/BG_bar.jpg");
	for (int i = 0; i < PLAYAREA_GRID_NUM_Y; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_X; j++)
		{
			float x = j * PLAYAREA_GRID_WIDTH + PLAYAREA_MARGIN_LEFT;
			float y = i * PLAYAREA_GRID_HEIGHT + PLAYAREA_MARGIN_TOP;
			pieces_[i][j] = new Piece({ x, y, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }, (i * PLAYAREA_GRID_NUM_X + j) % 7);
		}
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
					CheckPieceChaind(preSelect_, selectNum);
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
	int maxIndex = PLAYAREA_GRID_NUM_X * PLAYAREA_GRID_NUM_Y - 1;
	if (a <= maxIndex && b <= maxIndex)
	{
		int ax = a % PLAYAREA_GRID_NUM_X;
		int ay = a / PLAYAREA_GRID_NUM_X;
		int bx = b % PLAYAREA_GRID_NUM_X;
		int by = b / PLAYAREA_GRID_NUM_X;

		// 位置情報の交換
		Rect tempPos = pieces_[ay][ax]->GetPos();
		pieces_[ay][ax]->SetPos(pieces_[by][bx]->GetPos());
		pieces_[by][bx]->SetPos(tempPos);

		// 配列内の位置交換
		Piece* tempPiece = pieces_[ay][ax];
		pieces_[ay][ax] = pieces_[by][bx];
		pieces_[by][bx] = tempPiece;
		tempPiece = nullptr;
	}
}

void Playarea::CheckPieceChaind(int a, int b) // チェーンの確認と消去
{
	bool chainFlag = false;

	// 一旦ピースを入れ替え
	SwapPosPiece(a, b);

	// 縦方向のチェーン確認
	for (int x = 0; x < PLAYAREA_GRID_NUM_X; x++) {
		int chainCount = 1;
		int prevType = pieces_[0][x]->GetType();

		for (int y = 1; y < PLAYAREA_GRID_NUM_Y; y++) {
			int currentType = pieces_[y][x]->GetType();

			if (currentType == prevType) {
				chainCount++;
			}
			else {
				if (chainCount >= 3) {
					for (int k = 0; k < chainCount; k++) {
						pieces_[y - 1 - k][x]->SetVerticalChainFlag(true);
					}
					chainFlag = true;
				}
				chainCount = 1;
				prevType = currentType;
			}
		}

		// 最後のチェーンチェック
		if (chainCount >= 3) {
			for (int k = 0; k < chainCount; k++) {
				pieces_[PLAYAREA_GRID_NUM_Y - 1 - k][x]->SetVerticalChainFlag(true);
			}
			chainFlag = true;
		}
	}

	// 横方向のチェーン確認
	for (int y = 0; y < PLAYAREA_GRID_NUM_Y; y++) {
		int chainCount = 1;
		int prevType = pieces_[y][0]->GetType();

		for (int x = 1; x < PLAYAREA_GRID_NUM_X; x++) {
			int currentType = pieces_[y][x]->GetType();

			if (currentType == prevType) {
				chainCount++;
			}
			else {
				if (chainCount >= 3) {
					for (int k = 0; k < chainCount; k++) {
						pieces_[y][x - 1 - k]->SetHorizontalChainFlag(true);
					}
					chainFlag = true;
				}
				chainCount = 1;
				prevType = currentType;
			}
		}

		// 最後のチェーンチェック
		if (chainCount >= 3) {
			for (int k = 0; k < chainCount; k++) {
				pieces_[y][PLAYAREA_GRID_NUM_X - 1 - k]->SetHorizontalChainFlag(true);
			}
			chainFlag = true;
		}
	}

	// 消去処理または元に戻す
	if (chainFlag) {
		DeleteChaindPiece(); // チェーンしたピースを消す
	}
	else {
		SwapPosPiece(a, b); // チェーンしなかったので元に戻す
	}
}


void Playarea::DeleteChaindPiece()
{
	for (int i = 0; i < PLAYAREA_GRID_NUM_Y; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_X; j++)
		{
			Piece* tPiece = pieces_[i][j];
			if (tPiece->GetVerticalChainFlag() || tPiece->GetHorizontalChainFlag()) {
				tPiece->SetAlive(false);
			}
		}
	}

}
