#pragma once
#include "GameObject.h"
#include "globals.h"
#include "Piece.h"
#include "CsvReader.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;	//�w�i�iPlayScene�Ɉړ��\��j
	Rect areaRect_; // �v���C�G���A�̋�`
	Piece* pieces_[PLAYAREA_GRID_NUM_Y][PLAYAREA_GRID_NUM_X];//�s�[�X�̔z��
	bool isInPlayArea_ = false;
	bool isPush_;
	bool isHold_;
	Point selected_;
	int preSelect_;
	int playBGM_;	//�iPlayScene�Ɉړ��\��j
	int pieceSelectSound_;
	int pieceSwapSound_;

	CsvReader csv_;
	int maxType_;
	int score;
public:
    Playarea(int stagenum);
    ~Playarea();
    void Update() override;
	void Draw() override;
	void SwapPosPiece(int a, int b);
	//void CheckPieceChaind(int a, int b);
	void DeleteChaindPiece();
	bool IsSolvable(); // ���@�肪���邩
	bool WouldMatch(int a, int b); // ����������A�����邩
	void GenerateRandomBoard(int maxType);// �����_���ɔՖʂ𐶐�
	void DropPieces(int maxType);// ��������
	void ProcessMatchesAndDrop();// �`�F�[���m�F�Ɨ��������̃��[�v
	void ClearChainFlags();// �`�F�[���t���O���N���A
	bool SwapAndCheckChain(int a, int b);// �������ă`�F�[���m�F
	bool CheckAndMarkChains();// �`�F�[���m�F�ƃt���O�ݒ�
	void SetScore();
};

