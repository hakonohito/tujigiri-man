#pragma once
#include "../Library/GameObject.h"
#include <iostream>
#include <vector>

enum GameState {
	STATE_WAIT,
	STATE_START,
	STATE_FINISH
};

class Enemy;

class Battle : public GameObject 
{
public:
	Battle();
	~Battle();
	void Update() override;
	void Draw() override;
	std::vector<Enemy*>enemy;

private:

	GameState gameState;
	bool isWin;
	int count;
	int randomtime = 0;
	int level;
	void Random();
	int point;
};