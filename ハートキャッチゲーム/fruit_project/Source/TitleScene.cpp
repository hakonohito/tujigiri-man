#include "TitleScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "PlayScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY"); //ゲーム開始！
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	SetFontSize(48); // ← ここで文字サイズを大きく設定
	DrawString(100, 300, "果物キャッチャー", GetColor(255, 255, 0));

	SetFontSize(16);
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawFormatString(100, 100, GetColor(255,255,255), "%4.1f", 1.0f / Time::DeltaTime());
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	
}

