#pragma once
#include "../Library/GameObject.h"

class Taishoku : public GameObject {
public:
	Taishoku();
	~Taishoku();
	void Update() override;
	void Draw() override;
private:
	int hImage[3];
	int Enum = 0;
};