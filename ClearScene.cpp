#include "ClearScene.h"
#include "StageData.h"
#include <DxLib.h>

ClearScene::ClearScene()
	:csv_("data/カクテルデータ.csv"),
	infomation_("errer"), content_(0), message_("errer")
{
	hImage_ = LoadGraph("image/Title_bg.jpg");
	cocktailImagte_ = -1;

	int stagenum = StageData::stagenum;
	content_ = csv_.GetInt(stagenum-1, 7);
	infomation_ = csv_.GetString(stagenum-1, 8);
	message_ = csv_.GetString(stagenum-1, 9);
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
}

void ClearScene::Draw()
{
	DrawExtendGraph(0, 0, 1024, 768, hImage_, false);
	DrawExtendGraph(100, 400, 400, 600, cocktailImagte_, true);
	DrawFormatString(520, 100, GetColor(255, 255, 255), "説明： %s\n", infomation_.c_str());
	DrawFormatString(520, 300, GetColor(255, 255, 255), "度数： %d\n", content_);
	DrawFormatString(520, 500, GetColor(255, 255, 255), "カクテル言葉： %s\n", message_.c_str());
	DrawString(520, 700, "Push [S]Key To StageSelect", GetColor(255, 255, 255));
}