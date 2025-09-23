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
	int chainCounter_;//連鎖数
	bool isVerticalChain_;
	bool isHorizontalChain_;
public:
	Piece();
	Piece(Rect pos ,int type);
	~Piece();
	void Update() override;
	void Draw() override;
	void SetPos(Rect pos) { Pos_ = pos; }
	Rect GetPos() { return Pos_; }
	int GetType() { return type_; }
	void SetType(int type) { type_ = type; }
	void SetChainFlag(bool flag) { isChain_ = flag; }
	bool GetChainFlag() { return isChain_; }
	void SetChainCounter(int count) { chainCounter_ = count; }
	int GetChainCounter() { return chainCounter_; }
	void SetVerticalChainFlag(bool flag) { isVerticalChain_ = flag; }
	bool GetVerticalChainFlag() { return isVerticalChain_; }
	void SetHorizontalChainFlag(bool flag) { isHorizontalChain_ = flag; }
	bool GetHorizontalChainFlag() { return isHorizontalChain_; }
	void CopyFrom(Piece* other) {
		this->type_ = other->type_;
		this->isSelected_ = other->isSelected_;
		this->isDrawable_ = other->isDrawable_;
		this->isChain_ = other->isChain_;
		this->chainCounter_ = other->chainCounter_;
		this->isVerticalChain_ = other->isVerticalChain_;
		this->isHorizontalChain_ = other->isHorizontalChain_;
	}
};

