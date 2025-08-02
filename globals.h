#pragma once

namespace {
	//XGA SIZE
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	const int PLAYAREA_WIDTH = 560; // プレイエリアの幅
	const int PLAYAREA_HEIGHT = 700; // プレイエリアの高さ
	const int PLAYAREA_MARGIN_LEFT = 232; // プレイエリアの左マージン
	const int PLAYAREA_MARGIN_TOP = 34; // プレイエリアの上マージン

	
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