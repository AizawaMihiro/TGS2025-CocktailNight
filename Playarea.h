#pragma once
#include "GameObject.h"
#include "globals.h"
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;	//�w�i�iPlayScene�Ɉړ��\��j
	Rect areaRect_; // �v���C�G���A�̋�`
	Piece pieces_[PLAYAREA_GRID_NUM_Y][PLAYAREA_GRID_NUM_X];//�s�[�X�̔z��
	bool isInPlayArea_ = false;
	bool isPush_;
	bool isHold_;
	Point selected_;
	int preSelect_;
	int playBGM_;	//�iPlayScene�Ɉړ��\��j
	int pieceSelectSound_;
	int pieceSwapSound_;
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
	void SwapPosPiece(int a, int b);
	void CheckPieceChaind();
};

