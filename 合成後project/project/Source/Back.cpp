#include "Back.h"
#include "Screen.h"

Back::Back()
{
	hImage[0] = LoadGraph("data/image/background.png");
	hImage[1] = LoadGraph("data/image/title.png");
	Bcount = 0;
	blink = false;

}

Back::~Back()
{
}

void Back::Update()
{
	Bcount += 1;

	if (Bcount == 180) {
		Bcount = 0;
		blink = !blink;
	}
}

void Back::Draw()
{
	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, hImage[0], 1);
	DrawExtendGraph(95, 60, 1112 + 95, 261 + 60, hImage[1], 1);
	if (!blink) {
		DrawString(170, 330, "[P]を押してゲーム開始", GetColor(255, 255, 255));
	}
	DrawString(0, 0, "仮 [S]Key 選択画面に戻る", GetColor(255, 255, 255));
}
