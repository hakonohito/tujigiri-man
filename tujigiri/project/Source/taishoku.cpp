#include "taishoku.h"
#include "battle.h"

Taishoku::Taishoku()
{
	hImage[0] = LoadGraph("data/image/Victory.png");
	hImage[1] = LoadGraph("data/image/Lose.png");
	hImage[2] = LoadGraph("data/image/hanko.png");

	Battle* battle = FindGameObject<Battle>();
}

Taishoku::~Taishoku()
{
}

void Taishoku::Update()
{
}

void Taishoku::Draw()
{
	DrawGraph(0, 0, hImage[0], 1);
}
