#pragma once
#include "GameObject.h"
#include "globals.h"
class Piece :
    public GameObject
{
 private:
	int hImage_;
    Rect Pos_;
    int type_; 
	bool isSelected_;
	bool isDrawable_;
public:
	Piece();
	Piece(Rect pos ,int type);
	~Piece();
	void Update() override;
	void Draw() override;
	void SetPos(Rect pos);
	Rect GetPos();
};

