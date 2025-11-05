#include "PlayScene.h"
#include "player.h"
#include "enemy.h"
#include "battle.h"

PlayScene::PlayScene()
{
	new Battle();
	new Player();
}

PlayScene::~PlayScene()
{

}

void PlayScene::Update()
{
	
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
