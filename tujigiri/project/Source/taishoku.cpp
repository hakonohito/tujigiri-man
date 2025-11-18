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
	Battle* battle = FindGameObject<Battle>();
	if (count == 120 && battle->isWin == true) {
		DrawGraph(0, 0, hImage[0], 1);
	}
	if (count == 120 && battle->isWin == false) {
		DrawGraph(0, 0, hImage[1], 1);
	}
	
}
