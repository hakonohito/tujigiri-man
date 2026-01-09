#include "taishoku.h"
#include "battle.h"
#include <assert.h>

Taishoku::Taishoku()
{
	hImage[0] = LoadGraph("data/image/Victory.png");
	hImage[1] = LoadGraph("data/image/Lose.png");
	hImage[2] = LoadGraph("data/image/approval.png");
	hImage[3] = LoadGraph("data/image/No.png");
	hImage[4] = LoadGraph("data/image/clear.png");
	SEHandle = LoadSoundMem("data/SE_BGM/playscene/ÇΩÇ¢Ç÷ÇÒÇÊÇ≠Ç≈Ç´Ç‹ÇµÇΩÅB.mp3");
	assert(SEHandle != -1);

}

Taishoku::~Taishoku()
{
	DeleteSoundMem(SEHandle);
	for (int i = 0; i < 5; i += 1) {
		DeleteGraph(hImage[i]);
	}
}

void Taishoku::Update()
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->gameState == STATE_VS) {
		isWin = false;
		count = 0;
	}
	if (battle->gameState == STATE_RESULT) {
		isWin = battle->isWin;
		count += 1;
		point = battle->point;
	}
	if (count == 240 && isWin) {
		PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
	}
}

void Taishoku::Draw()
{
	//DrawExtendGraph(0 + 455, 0 + 195, 383 + 455, 303 + 195, hImage[4], 1);

	if (!isWin) {
		if (count >= 120) {
			if (point >= 0) {
				DrawExtendGraph(0 + 420, 0 + 35, 440 + 420, 650 + 35, hImage[1], 0);
				if (point >= 1) {
					DrawExtendGraph(0 + 427, 0 + 288, 115 + 427, 115 + 288, hImage[2], 1);
					if (point >= 2) {
						DrawExtendGraph(0 + 583, 0 + 288, 115 + 583, 115 + 288, hImage[2], 1);
					}
				}
			}
		}
		if (count >= 240) {
			DrawGraph(455, 195, hImage[3], 1);
		}
	}

	if (isWin) {
		switch (point) {

		case 1:
			if (count >= 120) {
				DrawExtendGraph(0 + 420, 0 + 35, 440 + 420, 650 + 35, hImage[0], 0);
				if (count >= 240) {
					DrawExtendGraph(0 + 445, 0 + 312, 100 + 445, 100 + 312, hImage[2], 1);
				}
			}
			break;

		case 2:
			if (count >= 120) {
				DrawExtendGraph(0 + 420, 0 + 35, 440 + 420, 650 + 35, hImage[0], 0);
				DrawExtendGraph(0 + 445, 0 + 312, 100 + 445, 100 + 312, hImage[2], 1);
				if (count >= 240) {
					DrawExtendGraph(0 + 590, 0 + 312, 100 + 590, 100 + 312, hImage[2], 1);
				}
			}
			break;

		case 3:
			if (count >= 120) {
				DrawExtendGraph(0 + 420, 0 + 35, 440 + 420, 650 + 35, hImage[0], 0);
				DrawExtendGraph(0 + 445, 0 + 312, 100 + 445, 100 + 312, hImage[2], 1);
				DrawExtendGraph(0 + 590, 0 + 312, 100 + 590, 100 + 312, hImage[2], 1);
				if (count >= 240) {
					DrawExtendGraph(0 + 735, 0 + 312, 100 + 735, 100 + 312, hImage[2], 1);
					if (count >= 420) {
						DrawExtendGraph(-30 + 455, 0 + 195, 413 + 455, 303 + 195, hImage[4], 1);
					}
				}
			}
			break;

		default:
			break;
		}
	}
	
}
