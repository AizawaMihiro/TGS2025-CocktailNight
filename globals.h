#pragma once

namespace {
	//XGA SIZE
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	const int PLAYAREA_WIDTH = 560; // プレイエリアの幅
	const int PLAYAREA_HEIGHT = 700; // プレイエリアの高さ
	const int PLAYAREA_MARGIN_LEFT = 232; // プレイエリアの左マージン
	const int PLAYAREA_MARGIN_TOP = 34; // プレイエリアの上マージン
	const int PLAYAREA_GRID_WIDTH = 70; // グリッドの幅
	const int PLAYAREA_GRID_HEIGHT = 70; // グリッドの高さ
	const int PLAYAREA_GRID_NUM_X = PLAYAREA_WIDTH / PLAYAREA_GRID_WIDTH; // グリッドの横数
	const int PLAYAREA_GRID_NUM_Y = PLAYAREA_HEIGHT / PLAYAREA_GRID_HEIGHT; // グリッドの縦数
	const int SELECTABLE_STAGE_NUM = 8; // 選択可能なステージ数
	const int SELECT_MARGIN_LEFT = 70; // ステージセレクトの左マージン
	const int SELECT_MARGIN_TOP = 70; // ステージセレクトの上マージン
	const int SELECT_WIDTH = 200; // ステージセレクトの幅
	const int SELECT_HEIGHT = 300; // ステージセレクトの高さ
	const int SELECT_GAP_WIDTH = 25; // ステージセレクトの幅の間隔
	const int SELECT_GAP_WIDTH_MID = 34;
	const int SELECT_GAP_HEIGHT = 28; // ステージセレクトの高さの間隔
	
}

extern float gDeltaTime; // フレーム間の時間差

inline float GetDeltaTime()
{
	return gDeltaTime;
}

struct Point
{
	float x;
	float y;

	inline Point operator+(const Point& other) const
	{
		return { x + other.x, y + other.y };
	}
};

struct Rect
{
	float x, y;//左上座標を入力
	float w, h;//x,yから見た相対座標を入力

	inline Point GetCenter() const
	{
		return { x + w / 2,y + h / 2 };
	}
};