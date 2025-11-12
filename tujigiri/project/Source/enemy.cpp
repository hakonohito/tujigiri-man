#include "enemy.h"
#include "Battle.h"

Enemy::Enemy(int num)
{
	Enum = num;
	hImage[0] = LoadGraph("data/image/enemy.png");
	hImage[1] = LoadGraph("data/image/enemy2.png");
	hImage[2] = LoadGraph("data/image/enemy3.png");
	x = 800; 
	y = 512;
	x1 = 352;
}

Enemy::~Enemy()
{
}

void Enemy::Update() 
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->isAttack == true && change == false) {
		Change();
		change = true;
		move = x;
	}
	if (change) {
		if (x > (move - 10))
		x -= 1;
	}
	if (battle->isAttack == false && change == true) {
		x += 10;
		Change();
		change = false;
	}

}

void Enemy::Draw()
{
	DrawGraph(x, y, hImage[Enum], 1);
	//352, 512
}

void Enemy::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
