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
	bool isSelected_;	//�I�����ꂽ��
	bool isDrawable_;	//�`�悳��邩
	bool isChain_;		//�A���m�F����
	int chainCounter_;
	bool isRemove_;		//�}�b�`�ŏ���������Ԃ�
public:
	Piece();
	Piece(Rect pos ,int type);
	~Piece();
	void Update() override;
	void Draw() override;
	void SetPos(Rect pos) { Pos_ = pos; }
	Rect GetPos() { return Pos_; }
	int GetType() { return type_; }
	void SetChainFlag(bool flag) { isChain_ = flag; }
	void SetChainCounter(int count) { chainCounter_ = count; }
	int GetChainCounter() { return chainCounter_; }
	void SetRemoveFlag(bool flag) { isRemove_ = flag; }
};

