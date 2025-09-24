#include "ClearScene.h"
#include "StageData.h"
#include <DxLib.h>
#include "globals.h"
#include "Input.h"

ClearScene::ClearScene()
	:csv_("data/�J�N�e���f�[�^.csv"),
	infomation_("errer"), content_(0), message_("errer")
{
	hImage_ = LoadGraph("image/Title_bg.jpg");
	cocktailImagte_ = -1;

	

	stagenum = StageData::stagenum;
	content_ = csv_.GetInt(stagenum-1, 7);
	infomation_ = csv_.GetString(stagenum-1, 8);
	message_ = csv_.GetString(stagenum-1, 9);

	switch (stagenum)
	{
	case 1:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�V���f����.png");

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;

	default:
		break;
	}
}

ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("StageSelect");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		
		SceneManager::ChangeScene("StageSelect");
	}

}

void ClearScene::Draw()
{
	DrawExtendGraph(0, 0, 1024, 768, hImage_, true);
	DrawBox(100, 100, 400, 300, GetColor(255, 255, 255), TRUE);
	DrawExtendGraph(100, 100, 400, 300, cocktailImagte_, true);
	
	SetFontSize(30);
	DrawFormatString(500, 200, GetColor(255, 255, 255), "�x���F %d\n", content_);
	DrawFormatString(500, 300, GetColor(255, 255, 255), "�J�N�e�����t�F %s\n", message_.c_str());

	SetFontSize(18);
	DrawFormatString(100, 520, GetColor(255, 255, 255), "�����F %s\n", infomation_.c_str());
	SetFontSize(20);
	DrawString(520, 700, "Left Click To StageSelect", GetColor(255, 255, 255));
}