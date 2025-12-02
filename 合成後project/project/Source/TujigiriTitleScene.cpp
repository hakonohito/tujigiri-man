#include "TujigiriTitleScene.h"
#include <assert.h>
#include "utility.h"

TujigiriTitleScene::TujigiriTitleScene()
{
	BGMHandle = LoadSoundMem("data/SE_BGM/titlescene/Driving_Wheel.mp3");
	assert(BGMHandle != -1);
	PlaySoundMem(BGMHandle, DX_PLAYTYPE_LOOP);
	hImage[0] = LoadGraph("data/image/background.png");
	hImage[1] = LoadGraph("data/image/title.png");
	
}

TujigiriTitleScene::~TujigiriTitleScene()
{
	DeleteSoundMem(BGMHandle);
	
}

void TujigiriTitleScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_P)) {
		
		SceneManager::ChangeScene("tujigiriPLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("SELECT");
	}
}


void TujigiriTitleScene::Draw()
{
	extern const char* Version();
	DrawGraph(0, 0, hImage[0], 1);
	DrawExtendGraph(95, 60, 1112 + 95, 261 + 60, hImage[1], 1);
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
