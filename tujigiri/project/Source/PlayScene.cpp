#include "PlayScene.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include <assert.h>

PlayScene::PlayScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/titlescene/ゲームのボタン音.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);

	SEHandle2 = LoadSoundMem("data/SE_BGM/playscene/オフィス電話.mp3");
	assert(SEHandle2 != -1);
	//PlaySoundMem(SEHandle2, DX_PLAYTYPE_BACK);

	SEHandle3 = LoadSoundMem("data/SE_BGM/playscene/キーボード_3.mp3");
	assert(SEHandle3 != -1);
	//PlaySoundMem(SEHandle3, DX_PLAYTYPE_BACK);
	
	new Battle();
	new Player();
}

PlayScene::~PlayScene()
{
	DeleteSoundMem(SEHandle);
	DeleteSoundMem(SEHandle2);
	DeleteSoundMem(SEHandle3);
}

void PlayScene::Update()
{
	//仮
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
