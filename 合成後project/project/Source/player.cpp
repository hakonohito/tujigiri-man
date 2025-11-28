#include "player.h"
#include "Battle.h"

Player::Player()
{
	hImage = LoadGraph("data/image/player.png");
	//x = 352; 
	//y = 512;
	//x1 = 800;
	x = 215;
	y = 280;
	x1 = 765;
}

Player::~Player()
{

}

void Player::Update()
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->gameState == STATE_WAIT) {
		if (change == true) {
			x -= 10;
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
		if (x < (move + 10))
			x += 1;
	}
}

void Player::Draw()
{
	DrawExtendGraph(x, y, x + 300, y + 440 + 30, hImage, 1);
	//800, 512
}

void Player::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
