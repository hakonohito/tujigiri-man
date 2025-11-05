#include "enemy.h"

Enemy::Enemy(int num)
{
	Enum = num;
	hImage[0] = LoadGraph("data/image/enemy.png");
	hImage[1] = LoadGraph("data/image/enemy2.png");
	hImage[2] = LoadGraph("data/image/enemy3.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update() 
{

}

void Enemy::Draw()
{
	DrawRectGraph(800, 512, 0, 0, 128, 128, hImage[Enum], 1);

}