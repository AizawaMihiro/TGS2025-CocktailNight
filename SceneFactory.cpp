#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include "StageData.h"
#include "BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "StageSelectScene.h"
#include "ClearScene.h"
#include "GameoverScene.h"
SceneBase* SceneFactory::CreateFirst()
{
	return new BootScene();
}

SceneBase * SceneFactory::Create(const std::string & name)
{
	if (name == "TITLE")
	{
		return new TitleScene();
	}
	if (name == "StageSelect")
	{
		return new StageSelectScene();
	}
	if (name == "PLAY")
	{
		return new PlayScene();
	}
	if (name == "CLEAR")
	{
		return new ClearScene();
	}
	if (name == "GAMEOVER")
	{
		return new GameoverScene();
	}
	
	MessageBox(NULL, ("���̃V�[���͂���܂���\n" + name).c_str(), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
