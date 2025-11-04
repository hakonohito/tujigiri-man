#include "battle.h"
#include "utility.h"
#include <iostream>
#include <random>

Battle::Battle()
{
	start = false;
	finish = false;
	result = false;
	level = 25; //[GO]が出てから負け判定が出るまでの時間
	count = 0; //実際の時間
}

Battle::~Battle()
{
}

void Battle::Update()
{

	//SPACEキーでスタート
	if (start == false) {
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
			start = true;
			Random();
		}
	}	

	//勝敗の判定
	if (start == true && finish == false) {
		count += 1;
		//SPACEキーの入力が間に合わなかった時の負け判定
		if (count > (randomtime + level)) {
			finish = true;
			result = false;
		}
		//SPACEキーで判定
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
			//勝ち判定
			if (count <= (randomtime + level) && count >= randomtime) {
					result = true;
			}
			//合図が出る前にキーを押した場合の負け判定
			if (count < randomtime) {
					result = false;
			}
				finish = true;
		}
	}


	//SPACEキーでもう一度遊ぶ
	if (start == true && finish == true) {
		if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
			start = false;
			finish = false;
			result = false;
			count = 0;
		}
	}
}

void Battle::Draw()
{
	if (start == false) {
		DrawString(525, 400, "Push [SPACE]Key To Start", GetColor(255, 255, 255));
	}
	if (count >= randomtime && finish == false && randomtime != 0) {
		DrawString(620, 400, "GO!!", GetColor(255, 255, 255));
	}
	if (result == true && finish == true) {
		DrawString(620, 400, "WIN!!", GetColor(255, 255, 255));
	}
	if  (result == false && finish == true) {
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
