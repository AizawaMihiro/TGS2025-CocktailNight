#pragma once
#include "globals.h"
#include "GameObject.h"



class StageSelect
	: public GameObject
{
private:
	int hImage_;
	Rect stageRect_[SELECTABLE_STAGE_NUM];
public:

	StageSelect();
	~StageSelect();
	void Update() override;
	void Draw() override;

};
