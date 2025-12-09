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
	//仮
	SetFontSize(20);

	SEHandle = LoadSoundMem("data/SE_BGM/playscene/和太鼓・尺八・和な場面転換.mp3");
	assert(SEHandle != -1);
	SEHandle2 = LoadSoundMem("data/SE_BGM/playscene/シャキン！.mp3");
	assert(SEHandle2 != -1);
	SEHandle3 = LoadSoundMem("data/SE_BGM/playscene/オフィス電話.mp3");
	assert(SEHandle3 != -1);
	PlaySoundMem(SEHandle3, DX_PLAYTYPE_BACK);
	
	

	hImage[0] = LoadGraph("data/image/tujigiriplayfield.png");
	hImage[1] = LoadGraph("data/image/ready.png");
	hImage[2] = LoadGraph("data/image/go.png");
	hImage[3] = LoadGraph("data/image/play.png");

	Bcount = 0;
	blink = false;

	isWin = false;
	gameState = STATE_TUTORIAL;
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

	case STATE_TUTORIAL:

		Bcount += 1;

		if (Bcount == 180) {
			Bcount = 0;
			blink = !blink;
		}

		if (KeyUtility::CheckTrigger(KEY_INPUT_P)) {
			gameState = STATE_WAIT;
			Bcount = 0;
			blink = false;
		}
		break;

	case STATE_WAIT:

		isAttack = false;
		if (count == 0) {
			SEHandle4 = LoadSoundMem("data/SE_BGM/playscene/キーボード_3.mp3");
			assert(SEHandle4 != -1);
			PlaySoundMem(SEHandle4, DX_PLAYTYPE_BACK);
		}

		count += 1;
		if (count == 60 * 3) {
			DeleteSoundMem(SEHandle3);
		}
		if (count == 60 * 3.5) {
			DeleteSoundMem(SEHandle4);
		}
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
				isAttack = true;
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
					count2 = 0;
					early = false;
				}
			}
		}

		//仮
		if (point == 3) {
			if (KeyUtility::CheckTrigger(KEY_INPUT_N)) {
				SceneManager::ChangeScene("TUJIGIRITITLE");
			}
		}

		//タイトルに戻る
		if (KeyUtility::CheckTrigger(KEY_INPUT_T)) {
			SceneManager::ChangeScene("TUJIGIRITITLE");
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

	case STATE_TUTORIAL:
		DrawExtendGraph(0, 0, 1280, 720, hImage[3], 1);
		if (!blink) {
			DrawString(555, 600, "[P]を押してゲーム開始", GetColor(255, 255, 255));
		}
		break;

	case STATE_WAIT:
		break;

	case STATE_START:
		if (count < 180 && !early) {
			DrawExtendGraph(315 -250, 50, 640 + 325 - 250, 50 + 190, hImage[1], 1);
		}
		if (count >= randomtime && randomtime != 0 && !early) {
			DrawExtendGraph(315 - 250, 50, 640 + 325 - 250, 50 + 190, hImage[2], 1);
		}
		break;

	case STATE_RESULT:
		if (isWin) {
			DrawString(620, 400, "勝利!!", GetColor(255, 255, 255));
		}
		if (!isWin && !early) {
			DrawString(620, 400, "負け!!", GetColor(255, 255, 255));
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
