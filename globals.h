#pragma once

namespace {
	//XGA SIZE
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;

	const int PLAYAREA_WIDTH = 560; // �v���C�G���A�̕�
	const int PLAYAREA_HEIGHT = 700; // �v���C�G���A�̍���
	const int PLAYAREA_MARGIN_LEFT = 232; // �v���C�G���A�̍��}�[�W��
	const int PLAYAREA_MARGIN_TOP = 34; // �v���C�G���A�̏�}�[�W��
	const int PLAYAREA_GRID_WIDTH = 70; // �O���b�h�̕�
	const int PLAYAREA_GRID_HEIGHT = 70; // �O���b�h�̍���
	const int PLAYAREA_GRID_NUM_X = PLAYAREA_WIDTH / PLAYAREA_GRID_WIDTH; // �O���b�h�̉���
	const int PLAYAREA_GRID_NUM_Y = PLAYAREA_HEIGHT / PLAYAREA_GRID_HEIGHT; // �O���b�h�̏c��
	const int SELECTABLE_STAGE_NUM = 8; // �I���\�ȃX�e�[�W��
	const int SELECT_MARGIN_LEFT = 70; // �X�e�[�W�Z���N�g�̍��}�[�W��
	const int SELECT_MARGIN_TOP = 70; // �X�e�[�W�Z���N�g�̏�}�[�W��
	const int SELECT_WIDTH = 200; // �X�e�[�W�Z���N�g�̕�
	const int SELECT_HEIGHT = 300; // �X�e�[�W�Z���N�g�̍���
	const int SELECT_GAP_WIDTH = 25; // �X�e�[�W�Z���N�g�̕��̊Ԋu
	const int SELECT_GAP_WIDTH_MID = 34;
	const int SELECT_GAP_HEIGHT = 28; // �X�e�[�W�Z���N�g�̍����̊Ԋu
	
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