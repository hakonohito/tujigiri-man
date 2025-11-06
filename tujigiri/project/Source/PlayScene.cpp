#include "PlayScene.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include <assert.h>

PlayScene::PlayScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/titlescene/ÉQÅ[ÉÄÇÃÉ{É^Éìâπ.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	new Battle();
	new Player();
}

PlayScene::~PlayScene()
{
	DeleteSoundMem(SEHandle);
}

void PlayScene::Update()
{
	//âº
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
