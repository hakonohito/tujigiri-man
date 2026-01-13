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

	bool FaderCheck1 = false;
	bool FaderCheck2 = false;
	bool TitleFlag = false;

	//STATE_VS内で管理
	float Vy1 = 740; //修正前720
	float Vy2 = -840;
	
	bool early = false;
	
	int count;
	int count2 = 0; //フライング管理
	bool Scount = false; //SE管理
	bool Scount2 = false;
	int randomtime = 0;
	
	int level[3] = {40, 20, 14};//[GO]が出てから負け判定が出るまでの時間.{正式版数値40，20、14}
	void Random();

	int SEHandle = -1;
	int SEHandle2 = -1;
	int SEHandle3 = -1;
	int SEHandle4 = -1;
	int SEHandle5 = -1;
	int SEHandle6 = -1;

	int hImage[10];
};