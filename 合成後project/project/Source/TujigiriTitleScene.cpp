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
	
	new Back();
	new Fader(0);
}

TujigiriTitleScene::~TujigiriTitleScene()
{
	DeleteSoundMem(BGMHandle);
}

void TujigiriTitleScene::Update()
{
	Fader* fader = FindGameObject<Fader>();

	if (CheckHitKey(KEY_INPUT_P)) {
		fader->isChange = true;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		SceneManager::ChangeScene("SELECT");
	}
	//‰¼
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}

	if (fader->fader) {
		SceneManager::ChangeScene("TUJIGIRIPLAY");
		faderCheck = true;
	}

	if (!fader->fader && faderCheck) {
		
	}

}


void TujigiriTitleScene::Draw()
{
	//extern const char* Version();
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));

}
