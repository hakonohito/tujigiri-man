#pragma once
#include "../Library/GameObject.h"
#include <iostream>
#include <vector>

enum GameState {
	STATE_WAIT,
	STATE_START,
	STATE_RESULT,
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
	bool isAttack = false;
private:

	GameState gameState;
	bool isWin;
	bool early = false;
	
	int count;
	int count2 = 0; //フライング管理
	int randomtime = 0;
	int level[3] = {180, 60, 25};//[GO]が出てから負け判定が出るまでの時間
	void Random();
	int point;

	int SEHandle = -1;
	int SEHandle2 = -1;

	int hImage;
};