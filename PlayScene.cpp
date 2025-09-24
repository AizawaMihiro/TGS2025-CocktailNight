#include "PlayScene.h"
#include <DxLib.h>
#include "Playarea.h"
#include <algorithm>
#include "StageData.h"

PlayScene::PlayScene()
{
	int stage = StageData::stagenum;
	playarea = new Playarea(stage);
	AddGameObject(playarea);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_C)) {
		SceneManager::ChangeScene("CLEAR");
	}
	if (CheckHitKey(KEY_INPUT_O)) {
		SceneManager::ChangeScene("GAMEOVER");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}

	if (newObjects.size() > 0) {
		for (auto& obj : newObjects)
		{
			gameObjects.push_back(obj);
		}
		newObjects.clear();
	}


	for (auto& obj : gameObjects) {
		if (obj->IsAlive())
		{
			obj->Update();
		}
	}
	std::sort(gameObjects.begin(), gameObjects.end(), [](GameObject* a, GameObject* b) 
	{
		return a->GetPriority() < b->GetPriority();
	});
	for (auto& obj : gameObjects) {
		if (obj->IsAlive())
		{
			obj->Draw();
		}
	}
	for (auto it = gameObjects.begin(); it != gameObjects.end();) {
		if (!(*it)->IsAlive())
		{
			delete* it;
			it = gameObjects.erase(it);
		}
		else {
			it++;
		}
	}
	
}

void PlayScene::Draw()
{

}
