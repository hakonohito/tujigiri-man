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
	Bcount = 0;
	blink = false;
}

TujigiriTitleScene::~TujigiriTitleScene()
{
	DeleteSoundMem(BGMHandle);
	
}

void TujigiriTitleScene::Update()
{
		Bcount += 1;

	if (Bcount % 180 == 0) {
		Bcount = 0;
		blink = !blink;
	}




	if (CheckHitKey(KEY_INPUT_P)) {
		
		SceneManager::ChangeScene("TUJIGIRIPLAY");
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("SELECT");
	}
	//仮
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TujigiriTitleScene::Draw()
{
	extern const char* Version();
	DrawGraph(0, 0, hImage[0], 1);
	DrawExtendGraph(95, 60, 1112 + 95, 261 + 60, hImage[1], 1);
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	if (!blink) {
		DrawString(100, 400, "[P]を押してゲーム開始", GetColor(255, 255, 255));
	}
	//仮
	DrawString(0, 0, "[S]Key 選択画面に戻る", GetColor(255, 255, 255));
}
