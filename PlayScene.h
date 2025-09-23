#pragma once

#include "SceneBase.h"
#include "Playarea.h"
#include "Piece.h"

class PlayScene
	: public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	Playarea* playarea;
	

};
