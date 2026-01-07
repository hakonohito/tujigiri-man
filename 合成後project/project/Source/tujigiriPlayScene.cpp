#include "TujigiriPlayScene.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include "Taishoku.h"
#include "TujigiriFader.h"
#include <assert.h>

TujigiriPlayScene::TujigiriPlayScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/titlescene/ÉQÅ[ÉÄÇÃÉ{É^Éìâπ.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	
	new Battle();
	new Player();
	new Enemy();
	new Taishoku();
	new Fader(255);
}

TujigiriPlayScene::~TujigiriPlayScene()
{
	DeleteSoundMem(SEHandle);
}

void TujigiriPlayScene::Update()
{
	//âº
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	
}

void TujigiriPlayScene::Draw()
{
	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
}
