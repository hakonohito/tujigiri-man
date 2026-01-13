#include "SelectScene.h"
#include <assert.h>
#include "TujigiriFader.h"
#include "utility.h"
#include "Back.h"
#include "DxLib.h"
//#include "FaderManager.h"

SelectScene::SelectScene()
{
	SEHandle = LoadSoundMem("data/SE_BGM/selectscene/homeBGM.mp3");
	assert(SEHandle != -1);
	SEHandle2 = LoadSoundMem("data/SE_BGM/selectscene/Œˆ’è‰¹_10.mp3");
	assert(SEHandle2 != -1);
	ChangeVolumeSoundMem(100, SEHandle);
	PlaySoundMem(SEHandle, DX_PLAYTYPE_LOOP);
	new Back(0);
	new Fader();
	
}

SelectScene::~SelectScene()
{
	DeleteSoundMem(SEHandle);
	DeleteSoundMem(SEHandle2);
}

void SelectScene::Update()
{

	Fader* fader = FindGameObject<Fader>();
	Back* back = FindGameObject<Back>();

	if (fader->alpha == 255) {
		fader->isChange = true;
	}

	if (KeyUtility::CheckTrigger(KEY_INPUT_T) && back->start) {
		fader->isChange = true;
		PlaySoundMem(SEHandle2, DX_PLAYTYPE_BACK);
		FaderCheck = true;
	}
	if (fader->fader && FaderCheck) {
		SceneManager::ChangeScene("TUJIGIRITITLE");
	}

	//’Ç‰Á‚µ‚Ü‚µ‚½i–Ø‘ºj
	if (KeyUtility::CheckTrigger(KEY_INPUT_H) && back->start) {
		fader->isChange = true;
		PlaySoundMem(SEHandle2, DX_PLAYTYPE_BACK);
		HtoHeart = true;
	}
	if (fader->fader && HtoHeart) {
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
