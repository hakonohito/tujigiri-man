#pragma once
#include "../Library/GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(int num);
	~Enemy();
	void Update() override;
	void Draw() override;
private:
	int hImage[3];
	int Enum;
};
