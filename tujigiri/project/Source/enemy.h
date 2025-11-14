#pragma once
#include "../Library/GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
	void Change();
	void CharaSet();
private:
	bool change = false;
	bool set = false;
	int hImage[3];
	int Enum;
	int x = 0;
	int y = 0;
	int x1 = 0;
	int move = 0;
};
