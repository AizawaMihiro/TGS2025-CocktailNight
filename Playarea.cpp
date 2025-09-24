#include "Playarea.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"


Playarea::Playarea(int stagenum):
	GameObject(), areaRect_({ PLAYAREA_MARGIN_LEFT, PLAYAREA_MARGIN_TOP, PLAYAREA_WIDTH, PLAYAREA_HEIGHT }),
	selected_({ -1, -1 }), preSelect_(-1), isHold_(false), isPush_(false)
{
	stagenum_ = stagenum;
	score_ = 0;
	csv_ = CsvReader("data/カクテルデータ.csv");
	maxType_ = csv_.GetInt(stagenum-1, 6);
	moveCount_ = csv_.GetInt(stagenum - 1, 2);
	hImage_ = LoadGraph("image/BG_bar.jpg");
	// 盤面の初期化
	do {
		GenerateRandomBoard(maxType_);// ランダムにピースを配置
	} while (!IsSolvable()); // 合法手がないならやり直し
	
	//BGMとSEの読み込み
	playBGM_ = LoadSoundMem("sound/ラスボス.mp3");
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
					if (SwapAndCheckChain(preSelect_, selectNum)) {
						moveCount_--;
						ProcessMatchesAndDrop(); // チェーン＆落下処理を開始

						if (score_ >= csv_.GetInt(stagenum_-1,5)) {
							// ステージクリア
							PlaySoundMem(pieceSwapSound_, DX_PLAYTYPE_BACK);
							SceneManager::ChangeScene("CLEAR");
							isAlive_ = false;
						}
						if (moveCount_==0)
						{
							SceneManager::ChangeScene("GAMEOVER");
							isAlive_ = false;
						}
						
					}

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
	DrawFormatString(10,100,GetColor(255,255,255),"score_: %d / %d",score_,csv_.GetInt(stagenum_-1,5));
	DrawFormatString(10, 200, GetColor(255, 255, 255), "lastmove: %d / %d", moveCount_, csv_.GetInt(stagenum_ - 1, 2));
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

//void Playarea::CheckPieceChaind(int a, int b) // チェーンの確認と消去
//{
//	bool chainFlag = false;
//
//	// 一旦ピースを入れ替え
//	SwapPosPiece(a, b);
//
//	// 縦方向のチェーン確認
//	for (int x = 0; x < PLAYAREA_GRID_NUM_X; x++) {
//		int chainCount = 1;
//		int prevType = pieces_[0][x]->GetType();
//
//		for (int y = 1; y < PLAYAREA_GRID_NUM_Y; y++) {
//			int currentType = pieces_[y][x]->GetType();
//
//			if (currentType == prevType) {
//				chainCount++;
//			}
//			else {
//				if (chainCount >= 3) {
//					for (int k = 0; k < chainCount; k++) {
//						pieces_[y - 1 - k][x]->SetVerticalChainFlag(true);
//					}
//					chainFlag = true;
//				}
//				chainCount = 1;
//				prevType = currentType;
//			}
//		}
//
//		// 最後のチェーンチェック
//		if (chainCount >= 3) {
//			for (int k = 0; k < chainCount; k++) {
//				pieces_[PLAYAREA_GRID_NUM_Y - 1 - k][x]->SetVerticalChainFlag(true);
//			}
//			chainFlag = true;
//		}
//	}
//
//	// 横方向のチェーン確認
//	for (int y = 0; y < PLAYAREA_GRID_NUM_Y; y++) {
//		int chainCount = 1;
//		int prevType = pieces_[y][0]->GetType();
//
//		for (int x = 1; x < PLAYAREA_GRID_NUM_X; x++) {
//			int currentType = pieces_[y][x]->GetType();
//
//			if (currentType == prevType) {
//				chainCount++;
//			}
//			else {
//				if (chainCount >= 3) {
//					for (int k = 0; k < chainCount; k++) {
//						pieces_[y][x - 1 - k]->SetHorizontalChainFlag(true);
//					}
//					chainFlag = true;
//				}
//				chainCount = 1;
//				prevType = currentType;
//			}
//		}
//
//		// 最後のチェーンチェック
//		if (chainCount >= 3) {
//			for (int k = 0; k < chainCount; k++) {
//				pieces_[y][PLAYAREA_GRID_NUM_X - 1 - k]->SetHorizontalChainFlag(true);
//			}
//			chainFlag = true;
//		}
//	}
//
//	// 消去処理または元に戻す
//	if (chainFlag) {
//		DeleteChaindPiece(); // チェーンしたピースを消す
//	}
//	else {
//		SwapPosPiece(a, b); // チェーンしなかったので元に戻す
//	}
//}


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

bool Playarea::IsSolvable() {
	for (int y = 0; y < PLAYAREA_GRID_NUM_Y; ++y) {
		for (int x = 0; x < PLAYAREA_GRID_NUM_X; ++x) {
			// 右とスワップ
			if (x + 1 < PLAYAREA_GRID_NUM_X) {
				std::swap(pieces_[y][x], pieces_[y][x + 1]);
				if (WouldMatch(x, y) || WouldMatch(x + 1, y)) {
					std::swap(pieces_[y][x], pieces_[y][x + 1]); // 戻す
					return true;
				}
				std::swap(pieces_[y][x], pieces_[y][x + 1]); // 戻す
			}

			// 下とスワップ
			if (y + 1 < PLAYAREA_GRID_NUM_Y) {
				std::swap(pieces_[y][x], pieces_[y + 1][x]);
				if (WouldMatch(x, y) || WouldMatch(x, y + 1)) {
					std::swap(pieces_[y][x], pieces_[y + 1][x]); // 戻す
					return true;
				}
				std::swap(pieces_[y][x], pieces_[y + 1][x]); // 戻す
			}
		}
	}
	return false;
}

bool Playarea::WouldMatch(int x, int y) {
	int type = pieces_[y][x]->GetType();

	// 横方向
	int count = 1;
	// 左
	for (int i = x - 1; i >= 0 && pieces_[y][i]->GetType() == type; --i) count++;
	// 右
	for (int i = x + 1; i < PLAYAREA_GRID_NUM_X && pieces_[y][i]->GetType() == type; ++i) count++;
	if (count >= 3) return true;

	// 縦方向
	count = 1;
	// 上
	for (int i = y - 1; i >= 0 && pieces_[i][x]->GetType() == type; --i) count++;
	// 下
	for (int i = y + 1; i < PLAYAREA_GRID_NUM_Y && pieces_[i][x]->GetType() == type; ++i) count++;
	if (count >= 3) return true;

	return false;
}


void Playarea::GenerateRandomBoard(int maxType) {
	for (int y = 0; y < PLAYAREA_GRID_NUM_Y; ++y) {
		for (int x = 0; x < PLAYAREA_GRID_NUM_X; ++x) {
			int newType;
			do {
				newType = rand() % maxType; // ランダムなタイプ
			} while (
				(x >= 2 &&
					pieces_[y][x - 1]->GetType() == newType &&
					pieces_[y][x - 2]->GetType() == newType) ||
				(y >= 2 &&
					pieces_[y - 1][x]->GetType() == newType &&
					pieces_[y - 2][x]->GetType() == newType)
				);
			float posx = x * PLAYAREA_GRID_WIDTH + PLAYAREA_MARGIN_LEFT;
			float posy = y * PLAYAREA_GRID_HEIGHT + PLAYAREA_MARGIN_TOP;
			pieces_[y][x] = new Piece(Rect{ posx, posy, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }, newType);
		}
	}
}

void Playarea::DropPieces(int maxType) {
	for (int x = 0; x < PLAYAREA_GRID_NUM_X; ++x) {
		for (int y = PLAYAREA_GRID_NUM_Y - 1; y >= 0; --y) {
			// ここでの pieces_[y][x] は non-null 前提（生成時に必ず埋める）
			if (!pieces_[y][x]->IsAlive()) {
				int above = y - 1;
				while (above >= 0 && !pieces_[above][x]->IsAlive()) {
					--above;
				}

				if (above >= 0) {
					// 下に落とす（ポインタを入れ替え＆見た目の位置も入れ替え）
					std::swap(pieces_[y][x], pieces_[above][x]);
					Rect tmp = pieces_[y][x]->GetPos();
					pieces_[y][x]->SetPos(pieces_[above][x]->GetPos());
					pieces_[above][x]->SetPos(tmp);
				}
				else {
					// **deleteしない**：古い死体は gameObjects に残しておき、
					// シーンの掃除ループに任せる
					int newType = rand() % maxType;
					float posx = x * PLAYAREA_GRID_WIDTH + PLAYAREA_MARGIN_LEFT;
					float posy = y * PLAYAREA_GRID_HEIGHT + PLAYAREA_MARGIN_TOP;
					pieces_[y][x] = new Piece(Rect{ posx, posy, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }, newType);
					// Piece の ctor が AddGameObject する仕様:contentReference[oaicite:3]{index=3}
				}
			}
		}
	}
}


void Playarea::ProcessMatchesAndDrop() {
	int delCount = 0;
	while (true) {
		ClearChainFlags();

		bool chainOccurred = false;

		delCount++;
		// チェーン確認（Swapなし、ただのチェック）
		chainOccurred = CheckAndMarkChains();

		if (!chainOccurred) break;

		const int piecePoint = 100;
		score_ += piecePoint * delCount;

		DeleteChaindPiece(); // チェーンしたピースを非表示にする
		DropPieces(maxType_); // 落下して空きに詰める
	}
}

void Playarea::ClearChainFlags() {
	for (int y = 0; y < PLAYAREA_GRID_NUM_Y; ++y) {
		for (int x = 0; x < PLAYAREA_GRID_NUM_X; ++x) {
			pieces_[y][x]->SetVerticalChainFlag(false);
			pieces_[y][x]->SetHorizontalChainFlag(false);
		}
	}
}

bool Playarea::SwapAndCheckChain(int a, int b) {
	SwapPosPiece(a, b);

	if (CheckAndMarkChains()) {
		return true; // 連鎖開始
	}

	// 連鎖がなければ戻す
	SwapPosPiece(a, b);
	return false;
}

bool Playarea::CheckAndMarkChains() {
	bool chainFlag = false;

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

	return chainFlag;
}
