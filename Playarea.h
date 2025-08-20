#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;
	Rect areaRect_; // プレイエリアの矩形
	std::vector<Piece*> pieces_;
	bool isInPlayArea_ = false;
	bool isPush_;
	bool isHold_;
	Point selected_;
	int preSelect_;
	int playBGM_;
	int pieceSelectSound_;
	int pieceSwapSound_;
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
	void SwapPosPiece(int a, int b);
};

