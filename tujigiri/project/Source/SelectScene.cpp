#include "SelectScene.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TujigiriTITLE");
	}
}

void SelectScene::Draw()
{
	DrawString(0, 0, "Push[T] = Tujigiri", GetColor(255, 255, 255));
}
