#pragma once
#include "globals.h"
#include "GameObject.h"



class StageSelect
	: public GameObject
{
public:

	StageSelect();
	~StageSelect();
	void Update() override;
	void Draw() override;
private:
	int hImage = -1;

};
