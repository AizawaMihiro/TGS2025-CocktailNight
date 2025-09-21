#include "PlayScene.h"
#include <DxLib.h>
#include "Playarea.h"
#include <algorithm>

PlayScene::PlayScene()
{
	new Playarea();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{

	
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));

}
