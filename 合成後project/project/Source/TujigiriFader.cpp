#include "TujigiriFader.h"
#include "Screen.h"

Fader::Fader()
{
}

Fader::~Fader()
{
}

void Fader::Update() {

	if (isChange) {
		switch (fader) {

		case false:
			alpha += (255 / 60);
			if (alpha >= 255) {
				alpha = 255;
				fader = true;
				isChange = false;
			}
			break;

		case true:
			alpha -= (255 / 60);
			if (alpha <= 0) {
				alpha = 0;
				fader = false;
				isChange = false;
			}
			break;
		}
	}

}

void Fader::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}