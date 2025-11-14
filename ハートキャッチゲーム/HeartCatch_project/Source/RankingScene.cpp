#include "RankingScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"

RankingScene::RankingScene() {}
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
    // 背景
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);

    // ランキング画面の見出し
    SetFontSize(48);
    DrawString(400, 100, "ランキング", GetColor(255, 255, 255));

    // 仮のランキング表示（後でデータと連携）
    SetFontSize(24);
    DrawString(500, 200, "1位：さくらこ　100点", GetColor(255, 200, 200));
    DrawString(500, 240, "2位：AIちゃん　80点", GetColor(200, 200, 255));
    DrawString(500, 280, "3位：ねこまる　60点", GetColor(200, 255, 200));

    // 戻る案内
    SetFontSize(20);
    DrawString(500, 600, "[Tキー] タイトルに戻る", GetColor(255, 255, 255));
}
