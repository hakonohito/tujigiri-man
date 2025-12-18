#include "RankingScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "ScoreManager.h"

int RankingbackgroundHandle;

int RankingplayerHandle;

RankingScene::RankingScene()
{

    RankingbackgroundHandle = LoadGraph("data/image/ranking_background.png");

    RankingplayerHandle = LoadGraph("data/image/woman_1.png");


}
RankingScene::~RankingScene() {}

void RankingScene::Update()
{
    // Tキーでタイトルに戻る
    if (CheckHitKey(KEY_INPUT_T)) {
        SceneManager::ChangeScene("TITLE");
    }
}

void RankingScene::Draw()
{

    // 背景画像を画面全体に表示
    DrawExtendGraph(0, 0, 1280, 720, RankingbackgroundHandle, TRUE);

    //女の子を表示
    DrawGraph(980, 280, RankingplayerHandle, TRUE); // ← 表示位置はそのまま

    SetFontSize(80); // フォントサイズ
    DrawString(95, 70, "ランキング", GetColor(0, 0, 0));

    const auto& scores = ScoreManager::GetScores(); 
    SetFontSize(60); // フォントサイズ

    int lastScore = ScoreManager::GetLastScore();
    int rank = ScoreManager::GetRankOfLastScore(); // 最新スコアの順位（0〜2）
    bool blink = (GetNowCount() / 300) % 2 == 0;   // 300msごとにON/OFF

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
    DrawFormatString(880, 100, GetColor(0, 0, 255),"\n %05d ", lastScore);

    //タイトルへ誘導
    SetFontSize(50); 
    DrawString(40, 540, "タイトルへ", GetColor(0, 0, 0));
    SetFontSize(40); 
    DrawString(100, 620, "Tキー", GetColor(0, 0, 0));


}
