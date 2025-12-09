#include "enemy.h"
#include "battle.h"

Enemy::Enemy()
{
	Enum = 0;
	hImage[0] = LoadGraph("data/image/jousi.png");
	hImage[1] = LoadGraph("data/image/kyokutyou.png");
	hImage[2] = LoadGraph("data/image/syatyou.png");
	//x = 800; 
	//y = 512;
	//x1 = 352;
	x = 765;
	y = 280;
	x1 = 215 - 125; //Changeèàóùå„ÇÃà íu  -125ïtÇØë´Çµ
}

Enemy::~Enemy()
{
}

void Enemy::Update() 
{
	Battle* battle = FindGameObject<Battle>();
	if (set == false && battle->gameState == STATE_WAIT) {
		Enum = battle->point;
		set = true;
		if (change == true) {
			x += 10;
			Change();
			change = false;
		}
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
		set = false;
	}

}

void Enemy::Draw()
{
	//DrawGraph(x, y, hImage[Enum], 1);
	//DrawExtendGraph(x, y - 50, x + 300 - 50, y + 440 + 10, hImage[1], 1);
	//352, 512
	Battle* battle = FindGameObject<Battle>();
	if (battle->gameState != STATE_TUTORIAL) {
		switch (Enum) {
		case 0:
			DrawExtendGraph(x, y - 50, x + 300, y + 440, hImage[Enum], 1);
			break;

		case 1:
			DrawExtendGraph(x, y - 50, x + 300 - 50, y + 440 + 10, hImage[Enum], 1);
			break;

		case 2:
			DrawExtendGraph(x, y - 50, x + 300, y + 440, hImage[Enum], 1);
			break;

		}
	}
	//DrawExtendGraph(x, y - 50, x + 300 - 50, y + 440, hImage[Enum], 1);
}

void Enemy::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
