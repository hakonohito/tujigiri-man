#include "PlayScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "fruit.h"
#include <cstdlib> // rand()
#include <ctime>   // time()

// コンストラクタ：ゲーム開始時の初期化
PlayScene::PlayScene()
{

    // 既存の初期化のあとに追加
    isReadyToStart = false; // 最初は待機状態

    srand((unsigned int)time(nullptr)); // 乱数初期化

    const int fruitCount = 3;
    int pict = LoadGraph("data/image/mob.png");

    for (int i = 0; i < fruitCount; ++i)
    {
        fruit f;
        f.x = rand() % 640;           // 横位置ランダム
        f.y = rand() % 480 - 480;     // 画面外の上からランダムにスタート
        f.dptime = 1 + rand() % 2;    // 落下速度ランダム（1〜2）
        f.type = rand() % 3;          // 果物の種類ランダム

        // 画像ハンドル設定（同じ画像を使い分け）
        f.itigopict = pict;
        f.mikannpict = pict;
        f.budoupict = pict;

        fruits.push_back(f);// リストに追加
    }

    basket = Basket();


    score = 0;
    timelimit = 60 * 60; // 60秒（60fps換算）
    GameOver = false;
}

// デストラクタ：今は特に何もしない
PlayScene::~PlayScene()
{
}


void PlayScene::Update()
{
    if (GameOver)
    {
        if (CheckHitKey(KEY_INPUT_RETURN))
        {
            SceneManager::ChangeScene("TITLE");
        }

        return;
    }
    // 終了状態なら何もしない

     // Spaceキー待ち状態
    if (!isReadyToStart) {
        if (CheckHitKey(KEY_INPUT_SPACE)) 
        {
            isReadyToStart = true; // ゲーム開始！
        }
        return; // まだゲーム開始してないので処理しない
    }

    for (auto& f : fruits)
    {
        f.Update(); // 果物の位置を更新
    }

   
    field.Draw(); // 地面の描画（果物より下に表示）

    basket.Update(); // カゴの移動

    for (auto& f : fruits)
    {
        f.Update(); // 果物の移動

        // カゴに当たった瞬間に消える＆得点加算
        if (basket.CheckCatch(f.x, f.y)) {
            score += 10;

            // 果物を再出現させる
            f.x = rand() % 640;
            f.y = rand() % 480 - 480;
            f.dptime = 1 + rand() % 2;
            f.spwandelay = rand() % 60;
            f.type = rand() % 3;
            f.active = false;
        }
    }

    timelimit--; // 1フレームごとに減少（60fpsなら1秒で60減る）

    if (timelimit <= 0) {
        GameOver = true;
    }

}

// 描画処理：毎フレーム画面に描画
void PlayScene::Draw()
{
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));


    if (!isReadyToStart) {
        DrawString(270, 300, "Press [Space] to Start", GetColor(255, 255, 255));
    }
   

    for (auto& f : fruits)
    {
        f.Draw(); // 果物を描画
    }

    basket.Draw();

    field.Draw(); // 地面の描画（果物より下に表示）


    if (GameOver) {
        SetFontSize(48); // ← ここで文字サイズを大きく設定
        DrawFormatString(240, 130, GetColor(255, 0, 0), "ゲーム終了");
        SetFontSize(16);
        DrawFormatString(270, 230, GetColor(255, 255, 255), "あなたのスコア: %d", score);
        DrawString(260, 300, "Press [Enter] To Title", GetColor(255, 255, 255));
       // DrawString(180, 310, "Press [Space] To Play Again", GetColor(255, 255, 255));
    }

    // スコアや時間の表示（必要なら追加）
    DrawFormatString(600, 30, GetColor(255, 255, 0), "Score: %d", score);
    DrawFormatString(20, 30, GetColor(255, 255, 0), "Time: %d", timelimit / 60); //秒表示
}
