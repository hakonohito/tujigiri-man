#include "battle.h"
#include "utility.h"
#include "enemy.h"
#include "player.h"
#include "TujigiriFader.h"
#include <assert.h>
#include <iostream>
#include <random>
#include <vector>
#include "Screen.h"

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
	SEHandle5 = LoadSoundMem("data/SE_BGM/playscene/移動開始時音源.mp3");
	assert(SEHandle5 != -1);
	SEHandle6 = LoadSoundMem("data/SE_BGM/playscene/VS音源.mp3");
	assert(SEHandle6 != -1);
	
	
	

	hImage[0] = LoadGraph("data/image/tujigiriplayfield.png");
	hImage[1] = LoadGraph("data/image/ready.png");
	hImage[2] = LoadGraph("data/image/go.png");
	hImage[3] = LoadGraph("data/image/play.png");
	hImage[4] = LoadGraph("data/image/player_window.png");
	hImage[5] = LoadGraph("data/image/jousi_window.png");
	hImage[6] = LoadGraph("data/image/kyokutyou_window.png");
	hImage[7] = LoadGraph("data/image/syatyou_window.png");
	hImage[8] = LoadGraph("data/image/VS1.png");
	hImage[9] = LoadGraph("data/image/background.png");

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
	DeleteSoundMem(SEHandle5);
	DeleteSoundMem(SEHandle6);
}

void Battle::Update()
{

	Fader* fader = FindGameObject<Fader>();

	switch (gameState) {

	case STATE_TUTORIAL:

		if (!FaderCheck1) {
			fader->isChange = true;
			FaderCheck1 = true;
		}
		
		Bcount += 1;

		if (Bcount == 180) {
			Bcount = 0;
			blink = !blink;
		}

		if (KeyUtility::CheckTrigger(KEY_INPUT_P)) {
			fader->isChange = true;
			FaderCheck2 = true;
		}

		if (fader->fader && FaderCheck2) {
			gameState = STATE_VS;
			FaderCheck1 = false;
			FaderCheck2 = false;
			Bcount = 0;
			blink = false;
			fader->isChange = true;
		}

		break;

	case STATE_VS:

		if (!Scount) {
			Scount = true;
			PlaySoundMem(SEHandle5, DX_PLAYTYPE_BACK);
		}

		if (Vy1 > -50) {
			Vy1 -= 10;
		}

		if (Vy2 < -50) {
			Vy2 += 10;
		}
		
		if (Vy1 <= -50 && Vy2 >= -50) {
			count += 1;
			if (!Scount2) {
				Scount2 = true;
				PlaySoundMem(SEHandle6, DX_PLAYTYPE_BACK);
			}
		}

		if (count == 180 && !fader->fader) {
			fader->isChange = true;
		}

		if (count >= 180 && fader->fader) {
			gameState = STATE_WAIT;
			count = 0;
			Scount = false;
			Scount = false;
			fader->isChange = true;
			Vy1 = 740;
			Vy2 = -840;
		}

		break;

	case STATE_WAIT:



		isAttack = false;
		if (count == 0) {
			SEHandle4 = LoadSoundMem("data/SE_BGM/playscene/キーボード_3.mp3");
			assert(SEHandle4 != -1);
			PlaySoundMem(SEHandle4, DX_PLAYTYPE_BACK);
			PlaySoundMem(SEHandle3, DX_PLAYTYPE_BACK);
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

	case STATE_START:
			count += 1;
			//SPACEキーの入力が間に合わなかった時の負け判定
			if (count > (randomtime + level[point]) && !early) {
				isWin = false;
				//isAttack = true;
				gameState = STATE_RESULT;
				break;
			}
			//SPACEキーで判定
			if (KeyUtility::CheckTrigger(KEY_INPUT_SPACE) && !early) {
				PlaySoundMem(SEHandle2, DX_PLAYTYPE_BACK);
				//isAttack = true;
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
		
		isAttack = true;

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
					fader->isChange = true;
					
					count = 0;
				}
			}
			//負けの場合
			if (!isWin) {
				//リトライ
				if (KeyUtility::CheckTrigger(KEY_INPUT_R)) {
					fader->isChange = true;
					count = 0;
					count2 = 0;
					early = false;
				}
			}

			if (fader->fader) {
				if (!isWin) {
					point = 0;
				}
				gameState = STATE_VS;
				fader->isChange = true;
				isWin = false;
			}

		}

		//仮
		if (point == 3) {
			if (KeyUtility::CheckTrigger(KEY_INPUT_N)) {
				fader->isChange = true;
				TitleFlag = true;
			}
		}

		//タイトルに戻る
		if (KeyUtility::CheckTrigger(KEY_INPUT_T)) {
			fader->isChange = true;
			TitleFlag = true;
			
		}

		if (TitleFlag && fader->fader) {
			SceneManager::ChangeScene("TUJIGIRITITLE");
		}

		break;


	case STATE_FINISH:
		break;
	}
}

void Battle::Draw()
{
	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, hImage[0], 1);
	
	switch (gameState) {

	case STATE_TUTORIAL:
		DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, hImage[3], 1);
		if (!blink) {
			DrawString(555, 600, "[P]を押してゲーム開始", GetColor(255, 255, 255));
		}
		break;

	case STATE_VS:
		DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, hImage[9], 1);
		
		//DrawExtendGraph(125, -50, 560 + 125, 840 - 50, hImage[4], 1);

		//DrawExtendGraph(595, -50, 560 + 595, 840 - 50, hImage[5], 1);

		//比率2.5

		DrawExtendGraph(125, Vy1, 560 + 125, 840 + Vy1, hImage[4], 1);

		DrawExtendGraph(595, Vy2, 560 + 595, 840 + Vy2, hImage[5 + point], 1);

		DrawExtendGraph(490, 135, 300 + 490, 450 + 135, hImage[8], 1); //描写順位は最後

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

/*

SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 0, 0), TRUE);
SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

*/