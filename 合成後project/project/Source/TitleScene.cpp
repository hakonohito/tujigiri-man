#include "TitleScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "HeartScene.h"
#include "Screen.h"
#include "SoundManager.h"

int logoHandle; // ロゴ画像のハンドル
int titlebackgroundHandle; //背景画像のハンドル

static const int WIDTH = 1280;
static const int HEIGHT = 720;

//効果音ハンドル
static int titleBGM;
static int selectSE;

TitleScene::TitleScene()
{
	logoHandle = LoadGraph("data/image/gamelogo.png");
	titlebackgroundHandle = LoadGraph("data/image/title_background.png");
	
	//BGMロード
	titleBGM = LoadSoundMem("data/SE_BGM/heartgamescene/BGM.mp3");
	PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP);


	selectSE = LoadSoundMem("data/SE_BGM/heartgamescene/select.mp3");
}

TitleScene::~TitleScene()
{
	StopSoundMem(titleBGM);
	DeleteGraph(logoHandle);
}

void TitleScene::Update()
{
	/*if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY"); //ゲーム開始！
	}*/ // コメントしました　齊藤

	// Pキー → プレイ
	if (CheckHitKey(KEY_INPUT_P) && !isWiping) {
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
		isWiping = true;
		wipeFrame = 0;
		nextScene = 0;
	}

	// Oキー → セレクト
	if (CheckHitKey(KEY_INPUT_O) && !isWiping) {
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
		isWiping = true;
		wipeFrame = 0;
		nextScene = 1;
	}

	// Rキー → ランキング
	if (CheckHitKey(KEY_INPUT_R) && !isWiping) {
		PlaySoundMem(selectSE, DX_PLAYTYPE_BACK);
		isWiping = true;
		wipeFrame = 0;
		nextScene = 2;
	}

	// ESCキー → 終了
	if (CheckHitKey(KEY_INPUT_ESCAPE) && !isWiping) {
		isWiping = true;
		wipeFrame = 0;
		nextScene = 3;
	}

	// ワイプ進行処理（Update の一番最後に追加）
	if (isWiping) {
		wipeFrame++;
		wipeAlpha = (int)(255.0 * wipeFrame / 30);

		if (wipeFrame >= 30) {
			switch (nextScene) {
			case 0: SceneManager::ChangeScene("HEART"); break;
			case 1: SceneManager::ChangeScene("SELECT"); break;
			case 2: SceneManager::ChangeScene("RANKING"); break;
			case 3: SceneManager::Exit(); break;
			}
		}
	}


}


void TitleScene::Draw()
{
	// タイトル画面背景表示する
	DrawExtendGraph(0, 0, 1280, 720, titlebackgroundHandle, TRUE);

	// ロゴ画像を読み込んだハンドルを logoHandle とする
	int logoW = 1130;
	int logoH = 408;

	// 表示したいサイズを決める（例：幅800、高さ300）
	int dispW = 800/1.2;
	int dispH = 300/1.2;

	// 中央に配置する座標を計算
	int logoX = (WIDTH - dispW) / 2;
	int logoY = 100;

	// 拡縮描画
	DrawExtendGraph(logoX, logoY, logoX + dispW, logoY + dispH, logoHandle, TRUE);


	// ボタン共通サイズ
	int btnW = 300, btnH = 80;
	int btnY = 500; // 同じ高さに配置

	// プレイボタン（左に配置）
	int playX = (WIDTH / 2) - btnW - 100;
	DrawBox(playX, btnY, playX + btnW, btnY + btnH, GetColor(0, 0, 255), TRUE);

	// プレイ文字（大きく）
	SetFontSize(28);
	DrawString(playX + 100, btnY + 20, "プレイ", GetColor(255, 255, 255));

	// キー案内（小さく、下に）
	SetFontSize(16);
	DrawString(playX + 110, btnY + 60, "[Pキー]", GetColor(200, 200, 200));

	// ランキングボタン（右に配置）
	int rankX = (WIDTH / 2) + 100;
	DrawBox(rankX, btnY, rankX + btnW, btnY + btnH, GetColor(0, 0, 255), TRUE);

	// ランキング文字（大きく）
	SetFontSize(28);
	DrawString(rankX + 70, btnY + 20, "ランキング", GetColor(255, 255, 255));

	// キー案内（小さく、下に）
	SetFontSize(16);
	DrawString(rankX + 110, btnY + 60, "[Rキー]", GetColor(200, 200, 200));

	DrawString(0, 0, "[O]Key 選択画面に戻る", GetColor(255, 255, 255));

	// 画面ワイプ描画（Draw の一番最後）
	if (isWiping) 
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, wipeAlpha);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


}

