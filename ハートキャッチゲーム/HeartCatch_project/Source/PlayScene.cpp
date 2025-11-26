#include "PlayScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "fruit.h"
#include <cstdlib> // rand()
#include <ctime>   // time()

int backgroundHandle;
int pict;
int playerHandle;

// コンストラクタ：ゲーム開始時の初期化
PlayScene::PlayScene()
    : basket(LoadGraph("data/image/loveletter.jpg")) // ← ここで初期化！
{
    
        backgroundHandle = LoadGraph("data/image/playfield.png"); // 画像パスは適宜変更
        
        playerHandle = LoadGraph("data/image/woman_1.png"); //女の子の画像ロード
    

    // 既存の初期化のあとに追加
    isReadyToStart = false; // 最初は待機状態

    srand((unsigned int)time(nullptr)); // 乱数初期化

    const int fruitCount = 3;

    //ハート画像をロード
    int redpict = LoadGraph("data/image/heart_red.png");
    int bluepict = LoadGraph("data/image/heart_blue.png");
    int yellowpict = LoadGraph("data/image/heart_yellow.png");

    // ハート生成
    const int dropAreaLeft = 320;
    const int dropAreaRight = 960;

    for (int i = 0; i < fruitCount; ++i)
    {
        fruit f;
        // ここで範囲を渡す！
        f.setDropArea(dropAreaLeft, dropAreaRight);

        f.x = dropAreaLeft + rand() % (dropAreaRight - dropAreaLeft);// 中央枠に限定
        f.y = rand() % 480 - 480;
        f.dptime = 1 + rand() % 2;
        f.type = rand() % 3;

        //ここでロード済みハンドルを渡す
        f.redpict = redpict;
        f.bluepict = bluepict;
        f.yellowpict = yellowpict;

        fruits.push_back(f);
    }

    //バスケット画像をロード
    int basketImage = LoadGraph("data/image/loveletter.jpg");
    //Basket に画像ハンドルを渡す
    basket = Basket(basketImage);


    score = 0;
    timelimit = 40 * 60; // 40秒（60fps換算）
    GameOver = false;
}

// デストラクタ：今は特に何もしない
PlayScene::~PlayScene()
{
    DeleteGraph(backgroundHandle);
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

    basket.Update(); // カゴの移動

    for (auto& f : fruits)
    {
        f.Update(); // 果物の移動

        // カゴに当たった瞬間に消える＆得点加算
        if (basket.CheckCatch(f.x, f.y)) {
            score += 10;

            // ハートの生成を中央エリアに限定
            const int dropAreaLeft = 320 + 96;
            const int dropAreaRight = 960 - 96;

            f.setDropArea(dropAreaLeft, dropAreaRight); //ここでも渡す！

            f.x = dropAreaLeft + rand() % (dropAreaRight - dropAreaLeft);
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

    // 背景画像を画面全体に表示
    DrawExtendGraph(0, 0, 1280, 720, backgroundHandle, TRUE);

    //女の子を表示
    DrawGraph(950, 220, playerHandle, TRUE);

    // 以下、バスケット・フルーツ・スコアなどの描画

    
    SetFontSize(16);
    DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));


    if (!isReadyToStart) {
        DrawString(270, 300, "Press [Space] to Start", GetColor(255, 255, 255));
    }
   

    for (auto& f : fruits)
    {
        f.Draw(); // 果物を描画
    }

    basket.Draw();



    if (GameOver) {
        SetFontSize(48); // ← ここで文字サイズを大きく設定
        DrawFormatString(240, 130, GetColor(255, 0, 0), "ゲーム終了");
        SetFontSize(16);
        DrawFormatString(270, 230, GetColor(255, 255, 255), "あなたのスコア: %d", score);
        DrawString(260, 300, "Press [Enter] To Title", GetColor(255, 255, 255));
       // DrawString(180, 310, "Press [Space] To Play Again", GetColor(255, 255, 255));
    }

    // スコアや時間の表示（必要なら追加）

    SetFontSize(60); // フォントサイズは共通で設定

    // ① Time文字表示
    DrawString(155, 100, "Time", GetColor(0, 0, 0));

    // ② TimeLimit表示（秒数）
    DrawFormatString(220, 160, GetColor(0, 0, 0), "%d", timelimit / 60);

    // ③ Score文字表示
    DrawString(120, 260, "Score", GetColor(0, 0, 0));
     
    // ④ Scorenumber表示（得点）
    DrawFormatString(240, 320, GetColor(0, 0, 0), "%d", score);


    //ハートごとの得点表示
    SetFontSize(40); // ← ここで文字サイズを大きく設定
    DrawFormatString(170, 440, GetColor(0, 0, 0), "+100点");
    DrawFormatString(170, 535, GetColor(0, 0, 0), "-50点"); 
    DrawFormatString(170, 630, GetColor(0, 0, 0), "+300点");

    // ハート生成範囲を赤線で表示
    const int dropAreaLeft = 320 + 96;
    const int dropAreaRight = 960 - 96;

    // 上下の位置は画面全体に合わせて線を引く
    DrawLine(dropAreaLeft, 0, dropAreaLeft, 720, GetColor(255, 0, 0));   // 左の赤線
    DrawLine(dropAreaRight, 0, dropAreaRight, 720, GetColor(255, 0, 0)); // 右の赤線

}
