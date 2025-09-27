#pragma once
#include "SceneBase.h"


class GameoverScene : public SceneBase
{
private:
	int hGameoverSound_;
public:
	GameoverScene();
	~GameoverScene();
	void Update() override;
	void Draw() override;
};
