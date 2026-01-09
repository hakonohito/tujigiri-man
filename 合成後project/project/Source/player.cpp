#include "player.h"
#include "Battle.h"

Player::Player()
{
	hImage[0] = LoadGraph("data/image/player.png");
	hImage[1] = LoadGraph("data/image/player_win.png");
	hImage[2] = LoadGraph("data/image/player_lose.png");
	//x = 352; 
	//y = 512;
	//x1 = 800;
	x = 215;
	y = 280;
	x1 = 765 + 125; //Changeˆ—Œã‚ÌˆÊ’u@+125•t‚¯‘«‚µ
}

Player::~Player()
{
	for (int i = 0; i < 3; i += 10) {
		DeleteGraph(hImage[i]);
	}
}

void Player::Update()
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->gameState == STATE_WAIT) {
		if (change) {
			x -= 10;
			Change();
			change = false;
		}
	}
	if (battle->isAttack && !change) {
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
	Battle* battle = FindGameObject<Battle>();

	if (battle->gameState != STATE_TUTORIAL && battle->gameState != STATE_VS) {

		if (!change) {
			DrawExtendGraph(x, y, x + 300, y + 440 + 30, hImage[0], 1);
			//800, 512
		}

		if (battle->gameState != STATE_WAIT && change) {

			if (battle->isWin) {
				DrawExtendGraph(x, y - 32, x + 300, y + 440 + 30 - 32, hImage[1], 1);
			}

			if (!battle->isWin) {
				DrawExtendGraph(x, y + 75, x + 300, y + 440 + 10, hImage[2], 1);
			}
		}
	}
}

void Player::Change()
{
	int num = x1;
	x1 = x;
	x = num;
}
