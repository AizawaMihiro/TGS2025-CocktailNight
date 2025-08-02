#pragma once

namespace {
	//XGA SIZE
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	const int PLAYAREA_WIDTH = 560; // �v���C�G���A�̕�
	const int PLAYAREA_HEIGHT = 700; // �v���C�G���A�̍���
	const int PLAYAREA_MARGIN_LEFT = 232; // �v���C�G���A�̍��}�[�W��
	const int PLAYAREA_MARGIN_TOP = 34; // �v���C�G���A�̏�}�[�W��

	
}

extern float gDeltaTime; // �t���[���Ԃ̎��ԍ�

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
	float x, y;//������W�����
	float w, h;//x,y���猩�����΍��W�����

	inline Point GetCenter() const
	{
		return { x + w / 2,y + h / 2 };
	}
};