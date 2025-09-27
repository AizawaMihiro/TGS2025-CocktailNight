#pragma once
#include "globals.h"
#include "GameObject.h"



class StageSelect
	: public GameObject
{
private:
	int hBGImage_;
	Rect stageRect_[SELECTABLE_STAGE_NUM];
	int hNumImage_[SELECTABLE_STAGE_NUM];
	int hSelectSound_;
	int selectedStage_ = -1;
public:

	StageSelect();
	~StageSelect();
	void Update() override;
	void Draw() override;
};
