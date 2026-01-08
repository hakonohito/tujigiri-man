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
	bool showTutorial = true;

	bool isWiping = false;     // ワイプ中かどうか
	int wipeAlpha = 0;         // 黒板の透明度（0〜255）
	int wipeFrame = 0;         // 経過フレーム数
	int gameOverStartTime = 0; //GameOver→Ranking　切り替え
	bool goSelect = false; //Oキーでセレクトシーン切り替え




	std::vector<fruit> fruits;
};
