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
		
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TujigiriTitleScene::Draw()
{
	extern const char* Version();
	DrawGraph(0, 0, hImage[0], 1);
	DrawExtendGraph(95, 60, 1112 + 95, 261 + 60, hImage[1], 1);
	//4004, 942  (4004 / 3.6) + 95, (942 / 3.6) + 100
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
