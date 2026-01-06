#pragma once
#include "../Library/GameObject.h"
#include <iostream>
#include <vector>

enum GameState {
	STATE_TUTORIAL, //1回のみ
	STATE_VS, //waitの前
	STATE_WAIT,
	STATE_START,
	STATE_RESULT,
	STATE_FINISH
};

class Battle : public GameObject 
{
public:
	Battle();
	~Battle();
	void Update() override;
	void Draw() override;
	bool isAttack = false;
	int point;
	bool isWin;
	GameState gameState;
	
private:

	int Bcount;
	bool blink;

	//STATE_VS内で管理
	float Vx1 = 125;
	float Vx2 = 595;
	float Vy1 = 720;
	float Vy2 = -840;
	
	bool early = false;
	
	int count;
	int count2 = 0; //フライング管理
	int randomtime = 0;
	
	int level[3] = {100, 100, 100};//[GO]が出てから負け判定が出るまでの時間.{正式版数値100，20、10}
	void Random();

	int SEHandle = -1;
	int SEHandle2 = -1;
	int SEHandle3 = -1;
	int SEHandle4 = -1;

	int hImage[10];
};