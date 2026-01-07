#include "SelectScene.h"
#include <assert.h>
#include "TujigiriFader.h"
#include "utility.h"
#include "Back.h"

SelectScene::SelectScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/selectscene/homeBGM.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	new Back(0);
	new Fader(0);
}

SelectScene::~SelectScene()
{
	DeleteSoundMem(SEHandle);
}

void SelectScene::Update()
{
	Fader* fader = FindGameObject<Fader>();

	if (KeyUtility::CheckTrigger(KEY_INPUT_T)) {
		fader->isChange = true;
	}
	if (fader->fader) {
		SceneManager::ChangeScene("TUJIGIRITITLE");
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_H)) {
		SceneManager::ChangeScene("TITLE");
	}
	//‰¼
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void SelectScene::Draw()
{
}
