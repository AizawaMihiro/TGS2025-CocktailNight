#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	Rect areaRect_; // プレイエリアの矩形
	std::vector<Piece*> pieces_;
	bool isInPlayArea_ = false;
	bool isHold_;
	Point selected_;
	int preSelect_;
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
	void SwapPosPiece(int a, int b);
};

