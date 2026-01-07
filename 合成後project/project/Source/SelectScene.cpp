#include "SelectScene.h"
#include <assert.h>
#include "TujigiriFader.h"
#include "utility.h"
#include "Back.h"

#include "FaderManager.h"

SelectScene::SelectScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/selectscene/homeBGM.mp3");
	assert(SEHandle != -1);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	new Back(0);
	new Fader();
}

SelectScene::~SelectScene()
{
	DeleteSoundMem(SEHandle);
}

void SelectScene::Update()
{
	Fader* fader = FindGameObject<Fader>();

	if (fader->alpha == 255) {
		fader->isChange = true;
	}

	if (KeyUtility::CheckTrigger(KEY_INPUT_T)) {
		fader->isChange = true;
		FaderCheck = true;
	}
	if (fader->fader && FaderCheck) {
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
