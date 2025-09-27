#include "DxLib.h"
#include "GameObject.h"
#include "globals.h"
#include "input.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include "Playarea.h"
#include "BootScene.h"

namespace
{
	const int BGCOLOR[3] = {0, 0, 0}; // �w�i�F{ 255, 250, 205 }; // �w�i�F
	int crrTime;
	int prevTime;
}


std::vector<GameObject*> gameObjects;
std::vector<GameObject*> newObjects;

float gDeltaTime = 0.0f; // �t���[���Ԃ̎��ԍ�

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("�ʎ��m��");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0],BGCOLOR[1],BGCOLOR[2]);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "�E�B���h�E�̃e�X�g");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	SceneManager::Init();

	//ChangeWindowMode(false);// �t���X�N���[���ɕύX
	//SetMouseDispFlag(true);// �}�E�X�J�[�\����\������

	crrTime = GetNowCount();
	prevTime = GetNowCount();

	//Playarea* playarea = new Playarea(); // �v���C�G���A�̏�����
	BootScene* bootscene = new BootScene();

	srand((unsigned int)time(NULL));

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate(); // �L�[���͂̏�Ԃ��X�V

		crrTime = GetNowCount(); // ���݂̎��Ԃ��擾
		// �O��̎��ԂƂ̍������v�Z
		float deltaTime = (crrTime - prevTime) / 1000.0f; // �b�P�ʂɕϊ�
		gDeltaTime = deltaTime; // �O���[�o���ϐ��ɕۑ�

		
		//�����ɂ�肽������������
		

		SceneManager::Update();
		SceneManager::Draw();


		
		
		
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime; // ���݂̎��Ԃ�O��̎��ԂƂ��ĕۑ�

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}