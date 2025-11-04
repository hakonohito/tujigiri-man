#include "battle.h"
#include "utility.h"
#include <iostream>
#include <random>

Battle::Battle()
{
	isWin = false;
	gameState = STATE_WAIT;
	level = 60; //[GO]が出てから負け判定が出るまでの時間
	count = 0; //実際の時間
}

Battle::~Battle()
{
}

void Battle::Update()
{

	switch (gameState) {

		//SPACEキーでスタート
	case STATE_WAIT:
			if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
				gameState = STATE_START;
				Random();
			}
			break;


		//勝敗の判定
	case STATE_START:
			count += 1;
			//SPACEキーの入力が間に合わなかった時の負け判定
			if (count > (randomtime + level)) {
				gameState = STATE_FINISH;
				isWin = false;
			}
			//SPACEキーで判定
			if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
				//勝ち判定
				if (count <= (randomtime + level) && count >= randomtime) {
					isWin = true;
				}
				//合図が出る前にキーを押した場合の負け判定
				if (count < randomtime) {
					isWin = false;
				}
				gameState = STATE_FINISH;
			}
			break;


		//SPACEキーでもう一度遊ぶ
	case STATE_FINISH:
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
				gameState = STATE_WAIT;
				isWin = false;
				count = 0;
		}
		break;
	}
}

void Battle::Draw()
{
	if (gameState == STATE_WAIT) {
		DrawString(525, 400, "Push [SPACE]Key To Start", GetColor(255, 255, 255));
	}
	if (count >= randomtime && gameState == STATE_START && randomtime != 0) {
		DrawString(620, 400, "GO!!", GetColor(255, 255, 255));
	}
	if (isWin == true && gameState == STATE_FINISH) {
		DrawString(620, 400, "WIN!!", GetColor(255, 255, 255));
	}
	if  (isWin == false && gameState == STATE_FINISH) {
		DrawString(620, 400, "LOSE!!", GetColor(255, 255, 255));
	}
}

void Battle::Random() //[GO]が出るまでの時間をランダムに生成
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(60, 420);  //ランダムに生成される[GO]が出るまでの最低時間と最大時間
	randomtime = dist(gen);
}
