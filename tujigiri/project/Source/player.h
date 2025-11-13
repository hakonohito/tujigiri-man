#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	void Change();
private:
	bool change = false;
	int hImage;
	int x = 0;
	int y = 0;
	int x1 = 0;
	int move = 0;
};

