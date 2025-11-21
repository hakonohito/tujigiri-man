#include "enemy.h"
#include "battle.h"

Enemy::Enemy()
{
	Enum = 0;
	hImage[0] = LoadGraph("data/image/jousi.png");
	hImage[1] = LoadGraph("data/image/enemy2.png");
	hImage[2] = LoadGraph("data/image/enemy3.png");
	//x = 800; 
	//y = 512;
	//x1 = 352;
	x = 765;
	y = 280;
	x1 = 215;
}

Enemy::~Enemy()
{
}

void Enemy::Update() 
{
	Battle* battle = FindGameObject<Battle>();
	if (set == false && battle->gameState == STATE_WAIT) {
		Enum = battle->point;
		set == true;
	}
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
		set == false;
	}

}

void Enemy::Draw()
{
	//DrawGraph(x, y, hImage[Enum], 1);
	//352, 512
	DrawExtendGraph(x, y, x + 300, y + 440, hImage[Enum], 1);
}

void Enemy::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
