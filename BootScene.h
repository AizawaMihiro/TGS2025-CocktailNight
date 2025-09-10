#pragma once

#include "SceneBase.h"

class BootScene : public SceneBase
{
public:
	BootScene();
	~BootScene();
	void Update() override;
	void Draw() override;
};