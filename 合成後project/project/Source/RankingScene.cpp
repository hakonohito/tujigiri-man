#include "RankingScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "ScoreManager.h"

int RankingbackgroundHandle;

int RankingplayerHandle;

RankingScene::RankingScene()
{

    RankingbackgroundHandle = LoadGraph("data/image/ranking.png");

    RankingplayerHandle = LoadGraph("data/image/woman_3.png");


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
    DrawRotaGraph(1110, 442, 1.2, 0.0, RankingplayerHandle, TRUE);

    SetFontSize(80); // フォントサイズ
    DrawString(90, 60, "ランキング", GetColor(0, 0, 0));

    const auto& scores = ScoreManager::GetScores(); 
    SetFontSize(60); // フォントサイズ

    DrawFormatString(150, 220, GetColor(0, 0, 0), "１位：%05d", scores.size() > 0 ? scores[0] : 0);
    DrawFormatString(250, 330, GetColor(0, 0, 0), "２位：%05d", scores.size() > 1 ? scores[1] : 0);
    DrawFormatString(350, 440, GetColor(0, 0, 0), "３位：%05d", scores.size() > 2 ? scores[2] : 0);
    DrawFormatString(460, 550, GetColor(0, 0, 0), "４位：%05d", scores.size() > 3 ? scores[3] : 0);

    //タイトルへ誘導
    SetFontSize(50); // フォントサイズ
    DrawString(60, 520, "タイトルへ", GetColor(0, 0, 0));
    DrawString(120, 600, "Tキー", GetColor(0, 0, 0));


}
