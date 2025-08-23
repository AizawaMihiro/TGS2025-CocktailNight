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
	bool isSelected_;	//選択されたか
	bool isDrawable_;	//描画されるか
	bool isChain_;		//連鎖確認中か
	int chainCounter_;
	bool isRemove_;		//マッチで消去される状態か
public:
	Piece();
	Piece(Rect pos ,int type);
	~Piece();
	void Update() override;
	void Draw() override;
	void SetPos(Rect pos);
	Rect GetPos();
};

