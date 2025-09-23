#pragma once
#include "GameObject.h"
#include "globals.h"
#include "Piece.h"
#include "CsvReader.h"
class Playarea :
    public GameObject
{
private:
	int hImage_;	//背景（PlaySceneに移動予定）
	Rect areaRect_; // プレイエリアの矩形
	Piece* pieces_[PLAYAREA_GRID_NUM_Y][PLAYAREA_GRID_NUM_X];//ピースの配列
	bool isInPlayArea_ = false;
	bool isPush_;
	bool isHold_;
	Point selected_;
	int preSelect_;
	int playBGM_;	//（PlaySceneに移動予定）
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
	bool IsSolvable(); // 合法手があるか
	bool WouldMatch(int a, int b); // 交換したら連鎖するか
	void GenerateRandomBoard(int maxType);// ランダムに盤面を生成
	void DropPieces(int maxType);// 落下処理
	void ProcessMatchesAndDrop();// チェーン確認と落下処理のループ
	void ClearChainFlags();// チェーンフラグをクリア
	bool SwapAndCheckChain(int a, int b);// 交換してチェーン確認
	bool CheckAndMarkChains();// チェーン確認とフラグ設定
	void SetScore();
};

