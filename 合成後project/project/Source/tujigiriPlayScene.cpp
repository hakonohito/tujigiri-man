#include "tujigiriPlayScene.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include "Taishoku.h"
#include <assert.h>

tujigiriPlayScene::tujigiriPlayScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/titlescene/ÉQÅ[ÉÄÇÃÉ{É^Éìâπ.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	
	new Battle();
	new Player();
	new Enemy();
	new Taishoku();
}

tujigiriPlayScene::~tujigiriPlayScene()
{
	DeleteSoundMem(SEHandle);
}

void tujigiriPlayScene::Update()
{
	//âº
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	
}

void tujigiriPlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
