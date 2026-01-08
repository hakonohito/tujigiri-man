#pragma once
#include "../Library/GameObject.h"

class Back : public GameObject {
public:
	Back(int num);
	~Back();
	void Update() override;
	void Draw() override;
	bool start;
private:
	int scene;
	int hImage[4];
	int SEHandle = -1;
	bool FaderCheck = false;
	int Bcount;
	bool blink;
};