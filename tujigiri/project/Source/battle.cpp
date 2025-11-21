#include "battle.h"
#include "utility.h"
#include "enemy.h"
#include "player.h"
#include <assert.h>
#include <iostream>
#include <random>
#include <vector>

Battle::Battle()
{
	SEHandle = LoadSoundMem("data/SE_BGM/playscene/和太鼓・尺八・和な場面転換.mp3");
	assert(SEHandle != -1);
	SEHandle2 = LoadSoundMem("data/SE_BGM/playscene/シャキン！.mp3");
	assert(SEHandle2 != -1);

	hImage[0] = LoadGraph("data/image/playfield.png");

	isWin = false;
	gameState = STATE_WAIT;
	count = 0; //実際の時間
	point = 0;
}

Battle::~Battle()
{
	DeleteSoundMem(SEHandle);
	DeleteSoundMem(SEHandle2);
}

void Battle::Update()
{

	switch (gameState) {

		//SPACEキーでスタート
	case STATE_WAIT:

		isAttack = false;

		count += 1;
		if (count == 60 * 5) {
			PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
			
		}
		if (count == 60 * 6) {
			count = 0;
			gameState = STATE_START;
			Random();
		}

		break;


		//勝敗の判定
	case STATE_START:
			count += 1;
			//SPACEキーの入力が間に合わなかった時の負け判定
			if (count > (randomtime + level[point]) && !early) {
				isWin = false;
				gameState = STATE_RESULT;
			}
			//SPACEキーで判定
			if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE) && !early) {
				PlaySoundMem(SEHandle2, DX_PLAYTYPE_BACK);
				isAttack = true;
				//勝ち判定
				if (count <= (randomtime + level[point]) && count >= randomtime) {
					isWin = true;
					point += 1;
					gameState = STATE_RESULT;
				}
				//合図が出る前にキーを押した場合の負け判定
				if (count < randomtime) {
					early = true;
					isWin = false;
					count2 = count;
					gameState = STATE_RESULT;
				}
				
			}
			
			break;


	case STATE_RESULT:
		
		//上記の続き
		if (early) {
			count += 1;
			if (early && count >= (count2 + 120)) {
				count2 = 0;
				early = false;
			}
		}
		
		if (point != 3) {
			//勝ちの場合
			if (isWin) {
				//次のステージへ
				if (KeyUtility::CheckTrigger(KEY_INPUT_N)) {
					gameState = STATE_WAIT;
					isWin = false;
					count = 0;
				}
			}
			//負けの場合
			if (!isWin) {
				//リトライ
				if (KeyUtility::CheckTrigger(KEY_INPUT_R)) {
					gameState = STATE_WAIT;
					count = 0;
					point = 0;
				}
			}
		}

		//タイトルに戻る
		if (KeyUtility::CheckTrigger(KEY_INPUT_T)) {
			SceneManager::ChangeScene("TITLE");
		}
		if (point == 3) {
			if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE)) {
				SceneManager::ChangeScene("TITLE");
			}
		}

		break;
	case STATE_FINISH:
		break;
	}

}

void Battle::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, hImage[0], 1);

	switch (gameState) {

	case STATE_WAIT:
		//DrawString(525, 400, "Push [SPACE]Key To Start", GetColor(255, 255, 255));
		break;

	case STATE_START:
		if (count < 180 && !early) {
			DrawString(580, 400, "この会社...", GetColor(255, 255, 255));
		}
		if (count >= randomtime && randomtime != 0 && !early) {
			DrawString(580, 400, "やめます！！", GetColor(255, 255, 255));
		}
		break;

	case STATE_RESULT:
		if (isWin) {
			DrawString(620, 400, "勝利!!", GetColor(255, 255, 255));
			if (point != 3) {
				DrawString(525, 430, "N:次のステージ T:タイトル", GetColor(255, 255, 255));
				//DrawExtendGraph(410, 15, 460 + 410, 690 + 15, hImage[0], 1); //1024::1536  2::3
			}
			else {
				DrawString(600, 430, "退職成功！！", GetColor(255, 255, 255));
			}
		}
		if (!isWin && !early) {
			DrawString(620, 400, "負け!!", GetColor(255, 255, 255));
			DrawString(550, 430, "R:リトライ T:タイトル", GetColor(255, 255, 255));
		}
		if (early) {
			DrawString(580, 400, "お手付き！！", GetColor(255, 255, 255));
		}
			break;
	}

	
	
		
	
}

void Battle::Random() //[GO]が出るまでの時間をランダムに生成
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(180, 540);  //ランダムに生成される[GO]が出るまでの最低時間と最大時間
	randomtime = dist(gen);
}
