#pragma once
#include "../Library/GameObject.h"

class Taishoku : public GameObject {
public:
	Taishoku();
	~Taishoku();
	void Update() override;
	void Draw() override;
private:
	int hImage[4];
	int SEHandle = -1;
	int Enum = 0;
	int count = 0;
	int point = 0;
	float angle = 0.0f;
	bool isWin = false;
};