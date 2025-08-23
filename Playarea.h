#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;	//�w�i�iPlayScene�Ɉړ��\��j
	Rect areaRect_; // �v���C�G���A�̋�`
	std::vector<Piece*> pieces_;
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
};

