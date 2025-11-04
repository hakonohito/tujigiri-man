#include "enemy.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/image/enemy.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update() 
{

}

void Enemy::Draw()
{
	DrawRectGraph(800, 512, 0, 0, 128, 128, hImage, 1);

	//‰E’[À•W1280
}