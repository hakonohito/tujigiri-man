#include "RankingScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"

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
    DrawGraph(950, 260, RankingplayerHandle, TRUE);

    SetFontSize(80); // フォントサイズ
    DrawString(90, 60, "ランキング", GetColor(0, 0, 0));

    SetFontSize(60); // フォントサイズ
    DrawString(150, 220, "１位：", GetColor(0, 0, 0));

    DrawString(250, 330, "２位：", GetColor(0, 0, 0));

    DrawString(350, 440, "３位：", GetColor(0, 0, 0));

    DrawString(460, 550, "４位：", GetColor(0, 0, 0));

    //タイトルへ誘導
    SetFontSize(50); // フォントサイズ
    DrawString(60, 520, "タイトルへ", GetColor(0, 0, 0));
    DrawString(120, 600, "Tキー", GetColor(0, 0, 0));


}
