#pragma once
#include "SceneBase.h"


class GameoverScene : public SceneBase
{
private:
public:
	GameoverScene();
	~GameoverScene();
	void Update() override;
	void Draw() override;
};
