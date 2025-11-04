#pragma once
#include "../Library/GameObject.h"

enum GameState {
	STATE_WAIT,
	STATE_START,
	STATE_FINISH
};

class Battle : public GameObject 
{
public:
	Battle();
	~Battle();
	void Update() override;
	void Draw() override;
private:

	GameState gameState;
	bool isWin;
	int count;
	int randomtime = 0;
	int level;
	void Random();
};