#pragma once
#include "../Library/GameObject.h"

class Back : public GameObject {
public:
	Back(int num);
	~Back();
	void Update() override;
	void Draw() override;
private:
	int scene;
	int hImage[3];
	int Bcount;
	bool blink;
};