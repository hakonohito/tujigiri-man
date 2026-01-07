#include "TujigiriFader.h"
#include "Screen.h"
#include "FaderManager.h"

Fader::Fader()
{
	if (FaderManager::GetFader()) {
		alpha = 255;
	}
	else {
		alpha = 0;
	}
}

Fader::~Fader()
{
}



void Fader::Update() {

	
	fader = FaderManager::GetFader();

	if (isChange) {
		switch(fader) {

		case false:
			alpha += (255.0f / 30.0f);
			if (alpha >= 255) {
				alpha = 255;
				FaderManager::SetFader(true);
				isChange = false;
			}
			break;

		case true:
			alpha -= (255.0f / 30.0f);
			if (alpha <= 0) {
				alpha = 0;
				FaderManager::SetFader(false);
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