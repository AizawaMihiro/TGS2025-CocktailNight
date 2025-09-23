#include "StageSelectScene.h"
#include "DxLib.h"
#include "globals.h"
#include "StageSelect.h"

StageSelectScene::StageSelectScene()
{
	
	stageselect = new StageSelect;

	AddGameObject(stageselect);
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update()
{
	stageselect->Update();
}

void StageSelectScene::Draw()
{
	stageselect->Draw();

}
