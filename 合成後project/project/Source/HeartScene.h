#pragma once
#include "../Library/SceneBase.h"
#include <vector>
#include "fruit.h"
#include "Basket.h"
#include "Field.h"


class HeartScene : public SceneBase
{
public:
	HeartScene();
	~HeartScene();
	void Update() override;
	void Draw() override;
	Basket basket;
	Field field;


private:

	int score;
	int timelimit;
	bool GameOver;
	bool isReadyToStart; // Spaceキー待ち状態
	int startTime; // PlaySceneに入った時刻（ミリ秒）



	std::vector<fruit> fruits;
};
