#include "SelectScene.h"
#include <assert.h>

SelectScene::SelectScene()
{
	hImage = LoadGraph("data/image/homescene.png");
	SEHandle = LoadSoundMem("data/SE_BGM/selectscene/homeBGM.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
}

SelectScene::~SelectScene()
{
	DeleteSoundMem(SEHandle);
}

void SelectScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TUJIGIRITITLE");
	}
	if (CheckHitKey(KEY_INPUT_H)) {
		SceneManager::ChangeScene("TITLE");
	}
	//‰¼
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void SelectScene::Draw()
{
	//DrawString(0, 0, "Push[T] = Tujigiri", GetColor(255, 255, 255));
	//DrawString(0, 100, "Push[H] = Heart", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, 1280, 720, hImage, 1);
}
