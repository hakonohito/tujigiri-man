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
	bool isReadyToStart; // SpaceƒL[‘Ò‚¿ó‘Ô



	std::vector<fruit> fruits;
};
