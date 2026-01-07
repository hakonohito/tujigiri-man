#pragma once
#include "../Library/GameObject.h"

class Back : public GameObject {
public:
	Back();
	~Back();
	void Update() override;
	void Draw() override;
private:
	int hImage[2];
	int Bcount;
	bool blink;
};