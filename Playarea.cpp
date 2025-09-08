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
			pieces_[i][j] = Piece({ x, y, PLAYAREA_GRID_WIDTH, PLAYAREA_GRID_HEIGHT }, (i * PLAYAREA_GRID_NUM_X + j) % 7);
		}
	}
	playBGM_ = LoadSoundMem("sound/Tenacity.mp3");
	pieceSelectSound_ = LoadSoundMem("sound/se/���ъ�̂ӂ���߂�.mp3");
	pieceSwapSound_ = LoadSoundMem("sound/se/�j���b1.mp3");
	ChangeVolumeSoundMem(255 * 0.5, playBGM_);//BGM�̉��ʂ𒲐�
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
	SetAlive(false); // �v���C�G���A���A�N�e�B�u�ɂ���
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
	int maxIndex = PLAYAREA_GRID_NUM_X * PLAYAREA_GRID_NUM_Y - 1;
	if (a <= maxIndex && b <= maxIndex)
	{
		int ax = a % PLAYAREA_GRID_NUM_X;
		int ay = a / PLAYAREA_GRID_NUM_X;
		int bx = b % PLAYAREA_GRID_NUM_X;
		int by = b / PLAYAREA_GRID_NUM_X;

		// �ʒu���̌���
		Rect tempPos = pieces_[ay][ax].GetPos();
		pieces_[ay][ax].SetPos(pieces_[by][bx].GetPos());
		pieces_[by][bx].SetPos(tempPos);

		// �z����̈ʒu����
		Piece tempPiece = pieces_[ay][ax];
		pieces_[ay][ax] = pieces_[by][bx];
		pieces_[by][bx] = tempPiece;
	}
}

void Playarea::CheckPieceChaind()//�`�F�[���̊m�F�Ə���
{
	//����邱�ƁF��[�Ɖ��[�̏����̌������A����{���̊m�F
	//���������̊m�F
	for (int i = 0; i < PLAYAREA_GRID_NUM_X; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_Y; j++)
		{
			Piece tPiece = pieces_[j][i];
			int tType = tPiece.GetType();
			if (j - 1 > 0 && j + 1 < PLAYAREA_GRID_NUM_Y)//���ԕ�
			{
				if (tType == pieces_[j+1][i].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(1);
				}
				if (tType == pieces_[j-1][i].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(pieces_[j - 1][i].GetChainCounter() + 1);
				}
				if (tType != pieces_[j + 1][i].GetType())//������s��v�i�`�F�[�����Ȃ��j
				{
					if (tPiece.GetChainCounter() == 2)//��̏ꍇ�̂݌��݈ʒu�ƈ��̃t���O������
					{
						tPiece.SetChainFlag(false);
						pieces_[j - 1][i].SetChainFlag(false);
						tPiece.SetChainCounter(0);
						pieces_[j - 1][i].SetChainCounter(0);
					}
				}
			}
			else if (j + 1 < PLAYAREA_GRID_NUM_Y)//�ŏ㕔
			{
				if (tType == pieces_[j + 1][i].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(1);
				}
			}
			else
			{
				if (tType == pieces_[j - 1][i].GetType())//�ŉ���
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(pieces_[j - 1][i].GetChainCounter() + 1);
				}
				if (tPiece.GetChainCounter() <= 2)
				{
					tPiece.SetChainFlag(false);
					tPiece.SetChainCounter(0);
				}
			}
		}

		for (int j = 0; j < PLAYAREA_GRID_NUM_Y; j++)
		{
			Piece tPiece = pieces_[j][i];
			if (tPiece.GetChainFlag())
			{
				tPiece.SetChainFlag(false);
				tPiece.SetVerticalChainFlag(true);
			}
		}
	}

	//���������̊m�F
	for (int i = 0; i < PLAYAREA_GRID_NUM_Y; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_X; j++)
		{
			Piece tPiece = pieces_[i][j];
			int tType = tPiece.GetType();
			if (j - 1 > 0 && j + 1 < PLAYAREA_GRID_NUM_X)//���ԕ�
			{
				if (tType == pieces_[i][j + 1].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(1);
				}
				if (tType == pieces_[i][j - 1].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(pieces_[i][j - 1].GetChainCounter() + 1);
				}
				if (tType != pieces_[i][j + 1].GetType())//��E���s��v�i�`�F�[�����Ȃ��j
				{
					if (tPiece.GetChainCounter() == 2)//��̏ꍇ�̂݌��݈ʒu�ƈ���̃t���O������
					{
						tPiece.SetChainFlag(false);
						pieces_[i][j - 1].SetChainFlag(false);
						tPiece.SetChainCounter(0);
						pieces_[i][j - 1].SetChainCounter(0);
					}
				}
			}
			else if (j + 1 < PLAYAREA_GRID_NUM_X)//�ō���
			{
				if (tType == pieces_[i][j + 1].GetType())
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(1);
				}
			}
			else
			{
				if (tType == pieces_[i][j - 1].GetType())//�ŉE��
				{
					tPiece.SetChainFlag(true);
					tPiece.SetChainCounter(pieces_[i][j - 1].GetChainCounter() + 1);
				}
				if (tPiece.GetChainCounter() <= 2)
				{
					tPiece.SetChainFlag(false);
					tPiece.SetChainCounter(0);
				}
			}
		}
		for (int j = 0; j < PLAYAREA_GRID_NUM_X; j++)
		{
			Piece tPiece = pieces_[i][j];
			if (tPiece.GetChainFlag())
			{
				tPiece.SetChainFlag(false);
				tPiece.SetHorizontalChainFlag(true);
			}
		}
	}

	//����{���̊m�F(�ۗ�)

	//��������
	for (int i = 0; i < PLAYAREA_GRID_NUM_Y; i++)
	{
		for (int j = 0; j < PLAYAREA_GRID_NUM_X; j++)
		{
			Piece tPiece = pieces_[i][j];
			if (tPiece.GetVerticalChainFlag() || tPiece.GetHorizontalChainFlag()) {
				tPiece.SetAlive(false);
			}
		}
	}

}
