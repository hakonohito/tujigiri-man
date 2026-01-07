#include "Back.h"
#include "Screen.h"

Back::Back(int num)
{
	hImage[0] = LoadGraph("data/image/background.png");
	hImage[1] = LoadGraph("data/image/title.png");
	hImage[2] = LoadGraph("data/image/homescene.png");
	Bcount = 0;
	blink = false;
	scene = num;
}

Back::~Back()
{
}

void Back::Update()
{

	switch (scene) {

	case 0:
		break;

	case 1:
		Bcount += 1;

		if (Bcount == 180) {
			Bcount = 0;
			blink = !blink;
		}
		break;
	}
	
}

void Back::Draw()
{
	switch (scene) {

	case 0:
		DrawExtendGraph(0, 0, 1280, 720, hImage[2], 1);
		break;

	case 1:
		DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, hImage[0], 1);
		DrawExtendGraph(95, 60, 1112 + 95, 261 + 60, hImage[1], 1);
		if (!blink) {
			DrawString(170, 330, "[P]を押してゲーム開始", GetColor(255, 255, 255));
		}
		DrawString(0, 0, "仮 [S]Key 選択画面に戻る", GetColor(255, 255, 255));
		break;
	}
	
}
