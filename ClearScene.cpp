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
		cocktailImagte_ = LoadGraph("image/sake 1/sake/���q�[�g.png");
		break;
	case 3:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�W���g�j�b�N.png");
		break;
	case 4:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�X�N�����[�h���C�o�[.png");
		break;
	case 5:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�u���b�f�B�}���[.png");
		break;
	case 6:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�e�L�[���T�����C�Y.png");
		break;
	case 7:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/���X���.png");
		break;
	case 8:
		cocktailImagte_ = LoadGraph("image/sake 1/sake/�}�e�B�[�j.png");
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
	DrawExtendGraph(0, 0, 1024, 768, hImage_, false);
	DrawBox(100, 400, 400, 600, GetColor(255, 255, 255), TRUE);
	DrawExtendGraph(100, 400, 400, 600, cocktailImagte_, true);
	
	DrawFormatString(520, 100, GetColor(255, 255, 255), "�����F %s\n", infomation_.c_str());
	DrawFormatString(520, 300, GetColor(255, 255, 255), "�x���F %d\n", content_);
	DrawFormatString(520, 500, GetColor(255, 255, 255), "�J�N�e�����t�F %s\n", message_.c_str());
	DrawString(520, 700, "Push [S]Key To StageSelect", GetColor(255, 255, 255));
}