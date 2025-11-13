#include "player.h"
#include "Battle.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	x = 352; 
	y = 512;
	x1 = 800;
}

Player::~Player()
{

}

void Player::Update()
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->isAttack == true && change == false) {
		Change();
		change = true;
		move = x;
	}
	if (change) {
		if (x < (move + 10))
			x += 1;
	}
	if (battle->isAttack == false && change == true) {
		x -= 10;
		Change();
		change = false;
	}
}

void Player::Draw()
{
	DrawRectGraph(x, y, 0, 0, 128, 128, hImage, 1);
	//800, 512
}

void Player::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
