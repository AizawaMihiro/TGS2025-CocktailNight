#pragma once
#include "GameObject.h"
#include "globals.h"
#include <vector>
#include "Piece.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;	//背景（PlaySceneに移動予定）
	Rect areaRect_; // プレイエリアの矩形
	std::vector<Piece*> pieces_;
	bool isInPlayArea_ = false;
	bool isPush_;
	bool isHold_;
	Point selected_;
	int preSelect_;
	int playBGM_;	//（PlaySceneに移動予定）
	int pieceSelectSound_;
	int pieceSwapSound_;
public:
    Playarea();
    ~Playarea();
    void Update() override;
	void Draw() override;
	void SwapPosPiece(int a, int b);
};

