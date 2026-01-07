#pragma once
#include "../Library/GameObject.h"

class Fader : public GameObject {
public:
	Fader();
	~Fader();
	void Update() override;
	void Draw() override;
	bool isChange = false;
	bool fader = false;
	float alpha = 0;
private:
	
};
