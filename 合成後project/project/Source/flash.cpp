#include "flash.h"
#include "Screen.h"

Flash::Flash()
{
	alpha = 0;
	count = 0;
}

Flash::~Flash()
{
}

void Flash::Update()
{
	if (isChange) {
		alpha = 255;
		count += 1;
		if (count == 3) {
			isChange = false;
			alpha = 0;
			count = 0;
		}
	}
}

void Flash::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
