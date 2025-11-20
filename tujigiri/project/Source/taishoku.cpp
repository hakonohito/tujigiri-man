#include "taishoku.h"
#include "battle.h"
#include <assert.h>

Taishoku::Taishoku()
{
	hImage[0] = LoadGraph("data/image/Victory.png");
	hImage[1] = LoadGraph("data/image/Lose.png");
	hImage[2] = LoadGraph("data/image/hanko.png");

	SEHandle = LoadSoundMem("data/SE_BGM/playscene/ÇΩÇ¢Ç÷ÇÒÇÊÇ≠Ç≈Ç´Ç‹ÇµÇΩÅB.mp3");
	assert(SEHandle != -1);

	
}

Taishoku::~Taishoku()
{
	DeleteSoundMem(SEHandle);
}

void Taishoku::Update()
{
	Battle* battle = FindGameObject<Battle>();
	if (battle->gameState == STATE_WAIT) {
		count = 0;
	}
	if (battle->gameState == STATE_RESULT) {
		count += 1;
	}
	if (count >= 120) {
		count = 120;
	}
}

void Taishoku::Draw()
{
	if (count >= 120) {
		DrawExtendGraph(0 + 420, 0 + 35, 440 + 420, 650 + 35, hImage[0], 0);
		DrawExtendGraph(0 + 445, 0 + 312, 100 + 445, 100 + 312, hImage[2], 0);
		DrawExtendGraph(0 + 590, 0 + 312, 100 + 590, 100 + 312, hImage[2], 0);
		DrawExtendGraph(0 + 735, 0 + 312, 100 + 735, 100 + 312, hImage[2], 0);
	}
	
	/*Battle* battle = FindGameObject<Battle>();
	if (count == 120 && battle->isWin == true) {
		DrawExtendGraph(0, 0, 440, 650, hImage[0], 1);
	}
	if (count == 120 && battle->isWin == false) {
		DrawExtendGraph(0, 0, hImage[1], 1);
	}*/
	
}
