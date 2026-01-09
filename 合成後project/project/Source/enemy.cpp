#include "enemy.h"
#include "battle.h"

Enemy::Enemy()
{
	Enum = 0;
	hImage[0] = LoadGraph("data/image/jousi.png");
	hImage[1] = LoadGraph("data/image/kyokutyou_10.png");
	hImage[2] = LoadGraph("data/image/syatyou.png");
	hImage[3] = LoadGraph("data/image/jousi_lose.png");
	hImage[4] = LoadGraph("data/image/kyokutyou_lose_11.jpg");
	hImage[5] = LoadGraph("data/image/syatyou_2.png");
	hImage[6] = LoadGraph("data/image/jousi_win.png");
	hImage[7] = LoadGraph("data/image/kyokutyou_win_12.png");
	hImage[8] = LoadGraph("data/image/syatyou_win.png");
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
	if (!set && battle->gameState == STATE_WAIT) {
		Enum = battle->point;
		set = true;
		if (change) {
			x += 10;
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
		if (x > (move - 10))
		x -= 1;
	}
	if (!battle->isAttack && change) {
		set = false;
	}

}

void Enemy::Draw()
{
	//DrawGraph(x, y, hImage[Enum], 1);
	//DrawExtendGraph(x, y - 50, x + 300 - 50, y + 440 + 10, hImage[1], 1);
	//352, 512
	Battle* battle = FindGameObject<Battle>();

	if (battle->gameState != STATE_TUTORIAL && battle->gameState != STATE_VS) {
		if (!change) {
			switch (Enum) {
			case 0:
				DrawExtendGraph(x, y - 50, x + 300, y + 440, hImage[Enum], 1);
				break;

			case 1:
				DrawExtendGraph(x, y - 50, x + 300 - 50, y + 440 + 10, hImage[Enum], 1);
				break;

			case 2:
				DrawExtendGraph(x, y - 50 + 10, x + 300, y + 440 + 10, hImage[Enum], 1);
				break;

			}
		}

		if (battle->gameState != STATE_WAIT && change) {

			if (!battle->isWin) {
				switch (Enum) {
				case 0:
					DrawExtendGraph(x, y - 50, x + 300, y + 440, hImage[Enum + 6], 1);
					break;

				case 1:
					DrawExtendGraph(x + 20, y - 50, x + 300 - 50- 20, y + 440 + 10 + 15, hImage[Enum + 6], 1);
					break;

				case 2:
					DrawExtendGraph(x, y - 50 + 10, x + 300, y + 440 + 10, hImage[Enum + 6], 1);
					break;

				}
			}

			if (battle->isWin) {
				switch (Enum) {
				case 0:
					DrawExtendGraph(x, y - 50 + 50 + 25, x + 300, y + 440 + 50, hImage[Enum + 3], 1);
					break;

				case 1:
					DrawExtendGraph(x - 20, y + 50, x + 300 - 50 + 20, y + 440 + 10, hImage[Enum + 3], 1);
					break;

				case 2:
					DrawExtendGraph(x - 50, y + 215, x + 320, y + 455, hImage[Enum + 3], 1);
					break;

				}
			}

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
