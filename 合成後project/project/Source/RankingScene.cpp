#include "RankingScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"

int RankingbackgroundHandle;

//効果音ハンドル
static int rankingBGM;
int RselectSE;


RankingScene::RankingScene()
{
    RankingbackgroundHandle = LoadGraph("data/image/ranking_background.png");

    RselectSE = LoadSoundMem("data/SE_BGM/heartgamescene/select.mp3");

    //BGMロード
    rankingBGM = LoadSoundMem("data/SE_BGM/heartgamescene/BGM.mp3");
    PlaySoundMem(rankingBGM, DX_PLAYTYPE_LOOP);

}
RankingScene::~RankingScene() 
{
    StopSoundMem(rankingBGM);
}

void RankingScene::Update()
{
    // Tキーでタイトルへワイプ開始
    if (CheckHitKey(KEY_INPUT_T) && !isWiping) {
        PlaySoundMem(RselectSE, DX_PLAYTYPE_BACK);
        isWiping = true;
        wipeFrame = 0;
    }
    //ワイプ進行処理（Update の最後に追加）
    if (isWiping) {
        wipeFrame++;
        wipeAlpha = (int)(255.0 * wipeFrame / 30); // 30フレームで真っ黒

        if (wipeFrame >= 30) {
            SceneManager::ChangeScene("TITLE"); // ← タイトルへ
        }
    }

}

void RankingScene::Draw()
{

    // 背景画像を画面全体に表示
    DrawExtendGraph(0, 0, 1280, 720, RankingbackgroundHandle, TRUE);
   

    SetFontSize(80); // フォントサイズ
    DrawString(95, 70, "ランキング", GetColor(0, 0, 0));

    const auto& scores = ScoreManager::GetScores(); 
    SetFontSize(60); // フォントサイズ

    int lastScore = ScoreManager::GetLastScore();
    int rank = ScoreManager::GetRankOfLastScore(); // 最新スコアの順位（0〜2）
    bool blink = (GetNowCount() / 300) % 2 == 0;   // 300msごとにON/OFF

    // 女の子の画像をスコアに応じて選ぶ
    int girlHandle = 0;
    if (lastScore < 2000) {
        girlHandle = LoadGraph("data/image/woman_1.png");
    }
    else if (lastScore < 5000) {
        girlHandle = LoadGraph("data/image/woman_2.png");
    }
    else {
        girlHandle = LoadGraph("data/image/woman_3.png");
    }

    // 表示
    DrawGraph(980, 280, girlHandle, TRUE);
    int color1 = (rank == 0 && blink) ? GetColor(255, 0, 0) : GetColor(0, 0, 0);
    int color2 = (rank == 1 && blink) ? GetColor(255, 0, 0) : GetColor(0, 0, 0);
    int color3 = (rank == 2 && blink) ? GetColor(255, 0, 0) : GetColor(0, 0, 0);

    DrawFormatString(150, 240, color1, "１位：%05d", scores.size() > 0 ? scores[0] : 0);
    DrawFormatString(250, 400, color2, "２位：%05d", scores.size() > 1 ? scores[1] : 0);
    DrawFormatString(350, 560, color3, "３位：%05d", scores.size() > 2 ? scores[2] : 0);

    // 「あなたのスコア」を表示
    SetFontSize(50); 
    DrawString(800, 100, "あなたのスコアは", GetColor(0, 0, 0));
    
    SetFontSize(60);
    DrawFormatString(880, 100, GetColor(0, 0, 0),"\n %05d ", lastScore);

    //タイトルへ誘導
    SetFontSize(50); 
    DrawString(40, 540, "タイトルへ", GetColor(0, 0, 0));
    SetFontSize(40); 
    DrawString(100, 620, "Tキー", GetColor(0, 0, 0));

    // 画面ワイプ描画（Draw の最後）
    if (isWiping) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, wipeAlpha);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

}
