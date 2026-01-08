#include "TujigiriTitleScene.h"
#include <assert.h>
#include "utility.h"
#include "Screen.h"
#include "TujigiriFader.h"
#include "Back.h"

TujigiriTitleScene::TujigiriTitleScene()
{
	SetFontSize(20);
	BGMHandle = LoadSoundMem("data/SE_BGM/titlescene/Driving_Wheel.mp3");
	assert(BGMHandle != -1);
	PlaySoundMem(BGMHandle, DX_PLAYTYPE_LOOP);
	
	new Back(1);
	new Fader();
}

TujigiriTitleScene::~TujigiriTitleScene()
{
	DeleteSoundMem(BGMHandle);
}

void TujigiriTitleScene::Update()
{
	Fader* fader = FindGameObject<Fader>();

	if (!FaderCheck1){
		fader->isChange = true;
		FaderCheck1 = true;
	}

	if (KeyUtility::CheckTrigger(KEY_INPUT_P)) {
		FaderCheck2 = true;
		fader->isChange = true;
	}
	if (KeyUtility::CheckTrigger(KEY_INPUT_O)) {
		FaderCheck3 = true;
		fader->isChange = true;
	}
	if (fader->fader && FaderCheck3) {
		SceneManager::ChangeScene("SELECT");
	}
	//‰¼
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}

	if (fader->fader && FaderCheck2) {
		SceneManager::ChangeScene("TUJIGIRIPLAY");
	}

}


void TujigiriTitleScene::Draw()
{
	//extern const char* Version();
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));

}
