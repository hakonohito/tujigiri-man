#include "HeartScene.h"
#include "DxLib.h"
#include "../Library/SceneManager.h"
#include "fruit.h"
#include <cstdlib> // rand()
#include <ctime>   // time()
#include "ScoreManager.h"
#include "SoundManager.h"


namespace {
    int tutorialHandle;
    int backgroundHandle;
    int pict;
    int woman_1; // woman_1.png（スコア2000未満）
    int woman_2;    // woman_2.png（スコア2000以上5000未満）
    int woman_3;    // woman_3.png（スコア5000以上）
};

// ハートの種類に応じて速度を返す関数
int GetSpeedByType(int type) {
    switch (type) {
    case 0: 
        return 2; // 基準速度
    case 1: 
        return 2; 
    case 2: // 黄
        return 4; // 赤青の2倍
    default:
        return 2; // 安全策
    }
}

// 効果音ハンドル
static int playBGM;
int catchSE;
int beepSE;

// コンストラクタ：ゲーム開始時の初期化
HeartScene::HeartScene()
    : basket(LoadGraph("data/image/loveletter.jpg")) // ← ここで初期化！
{
    //BGMロード
    playBGM = LoadSoundMem("data/SE_BGM/heartgamescene/BGM.mp3");
    PlaySoundMem(playBGM, DX_PLAYTYPE_LOOP);

    //チュートリアル画像ロード
    tutorialHandle = LoadGraph("data/image/heart_Tutorial.png");
    showTutorial = true;

	//サウンドロード
    catchSE = LoadSoundMem("data/SE_BGM/heartgamescene/catchsound.mp3");
    beepSE = LoadSoundMem("data/SE_BGM/heartgamescene/ビープ音4.mp3");

    backgroundHandle = LoadGraph("data/image/playfield.png"); // 画像パスは適宜変更

    woman_1 = LoadGraph("data/image/woman_1.png"); //女の子の画像ロード
    woman_2 = LoadGraph("data/image/woman_2.png");
    woman_3 = LoadGraph("data/image/woman_3.png");


    // 既存の初期化のあとに追加
    isReadyToStart = false; // 最初は待機状態
    startTime = GetNowCount(); // ← PlaySceneに入った瞬間の時刻を記録

    srand((unsigned int)time(nullptr)); // 乱数初期化

    const int fruitCount = 5; //ハート落下個数　調整場所

    //ハート画像をロード
    int redpict = LoadGraph("data/image/heart_red.png");
    int bluepict = LoadGraph("data/image/heart_blue.png");
    int yellowpict = LoadGraph("data/image/heart_yellow.png");

    // ハート生成
    const int dropAreaLeft = 320 + 96;
    const int dropAreaRight = 960 - 96;

    for (int i = 0; i < fruitCount; ++i)
    {
        fruit f;
        f.setDropArea(dropAreaLeft, dropAreaRight);

        f.x = dropAreaLeft + rand() % (dropAreaRight - dropAreaLeft); // 中央枠に限定
        f.y = rand() % 480 - 480;
        f.type = rand() % 3;

        //ここを関数呼び出しに変更
        f.dptime = GetSpeedByType(f.type);

        // 画像ハンドルを渡す
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

// デストラクタ
HeartScene::~HeartScene()
{
    StopSoundMem(playBGM); //シーン終了時にBGMを止める
    DeleteGraph(backgroundHandle);
}


void HeartScene::Update()
{
    
    if (showTutorial) {

        // Pキーでチュートリアル終了 → ワイプ開始
        if (CheckHitKey(KEY_INPUT_P) && !isWiping) {
            isWiping = true;
            wipeFrame = 0;
        }

        // ワイプ進行
        if (isWiping) {
            wipeFrame++;
            wipeAlpha = (int)(255.0 * wipeFrame / 30); // 30フレームで暗転

            if (wipeFrame >= 30) {
                // チュートリアル終了
                showTutorial = false;

                // ゲーム開始の準備
                startTime = GetNowCount();
                isReadyToStart = false;

                // ワイプ解除
                isWiping = false;
                wipeAlpha = 0;
            }
        }

        return;
    }


    if (GameOver)
    {
        //3秒経ったらワイプ開始
        if (!isWiping) {
            int elapsed = GetNowCount() - gameOverStartTime;
            if (elapsed >= 3000) { // 3000ms = 3秒
                isWiping = true;
                wipeFrame = 0;
            }
        }

        //ワイプ進行
        if (isWiping) {
            wipeFrame++;
            wipeAlpha = (int)(255.0 * wipeFrame / 30);

            if (wipeFrame >= 60) {
                SceneManager::ChangeScene("RANKING"); // ← 自動でランキングへ
            }
        }

        return;
    }



    // 終了状態なら何もしない

     // Spaceキー待ち状態
    if (!isReadyToStart) {
        int elapsed = GetNowCount() - startTime; // 経過時間を計算
        if (elapsed >= 3000) { // 3000ミリ秒 = 3秒
            isReadyToStart = true; // ゲーム開始！
        }
        return; // まだゲーム開始してないので処理しない
    }

    // Oキーでセレクトシーンへワイプ開始
    if (CheckHitKey(KEY_INPUT_O) && !isWiping) {
        isWiping = true;
        wipeFrame = 0;
        goSelect = true;
    }


    for (auto& f : fruits)
    {
        f.Update(); // ハートの位置を更新
    }

    basket.Update(); // ラブレターの移動

    for (auto& f : fruits)
    {
        f.Update(); // ハートの移動

        // ラブレターに当たった瞬間に消える＆得点加算
        if (basket.CheckCatch(f.x, f.y)) {
            
            // ハートの種類ごとに得点を変える
            if (f.type == 0) {        // 赤ハート
                score += 100;
                PlaySoundMem(catchSE, DX_PLAYTYPE_BACK); // ← 赤ハート音
            }
            else if (f.type == 1) { // 青ハート
                score -= 50;
                PlaySoundMem(beepSE, DX_PLAYTYPE_BACK); // ← 赤ハート音
            }
            else if (f.type == 2) { // 黄色ハート
                score += 300;
                PlaySoundMem(catchSE, DX_PLAYTYPE_BACK); // ← 黄色ハート音
            }

            // ハートの生成を中央エリアに限定
            const int dropAreaLeft = 320 + 96;
            const int dropAreaRight = 960 - 96;

            f.setDropArea(dropAreaLeft, dropAreaRight);

            f.x = dropAreaLeft + rand() % (dropAreaRight - dropAreaLeft);
            f.y = rand() % 480 - 480;
            f.type = rand() % 3;

            //ここを関数呼び出しに変更
            f.dptime = GetSpeedByType(f.type);

            f.spwandelay = rand() % 60;
            f.active = false;

        }
    }

    timelimit--; // 1フレームごとに減少（60fpsなら1秒で60減る）

    if (timelimit <= 0) {
        GameOver = true;
        gameOverStartTime = GetNowCount();
        ScoreManager::AddScore(score); // ← スコア保存！ 
    }

    //Oキー用ワイプ進行（通常プレイ中）
    if (isWiping && goSelect && !GameOver && !showTutorial) {
        wipeFrame++;
        wipeAlpha = (int)(255.0 * wipeFrame / 30); // 30フレームで暗転

        if (wipeFrame >= 30) {
            SceneManager::ChangeScene("SELECT");
        }
    }

}

// 描画処理：毎フレーム画面に描画
void HeartScene::Draw()
{
    //チュートリアル画像を表示
    if (showTutorial) {
        DrawExtendGraph(0, 0, 1280, 720, tutorialHandle, TRUE);
        //return; // ← チュートリアル中は他の描画をしない
    }

    if (!showTutorial)
    {
        // 背景画像を画面全体に表示
        DrawExtendGraph(0, 0, 1280, 720, backgroundHandle, TRUE);

        //女の子の表情変化
        int girlImage;

        if (score < 2000) {
            girlImage = woman_1;
        }
        else if (score < 5000) {
            girlImage = woman_2;
        }
        else {
            girlImage = woman_3;
        }

        DrawGraph(950, 260, girlImage, TRUE); // ← 表示位置はそのまま
        //DrawRotaGraph(1110, 442, 1.2, 0.0, girlImage, TRUE);

        // 以下、バスケット・フルーツ・スコアなどの描画
        SetFontSize(16);
        DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));

        //スタート表示　※必要なら
        if (!isReadyToStart) {
            SetFontSize(30);
            DrawString(440, 300, "Ready... 3秒後にスタート！", GetColor(0, 0, 0));
        }


        for (auto& f : fruits)
        {
            f.Draw(); // ハートを描画
        }

        basket.Draw();

        if (GameOver) {
            SetFontSize(150);
            DrawString(380, 280, "TIME UP", GetColor(255, 0, 0));
        }

        // スコアや時間の表示（必要なら追加）

        SetFontSize(50); // フォントサイズ設定

        //  Time文字表示
        DrawString(155, 90, "Time", GetColor(0, 0, 0));

        //  Score文字表示  
        DrawString(130, 240, "Score", GetColor(0, 0, 0));
        SetFontSize(72);
        //  TimeLimit表示（秒数）残り10秒以下で点滅
        int timeSec = timelimit / 60;
        int timeColor;
        if (timeSec <= 10) {
            bool blink = (GetNowCount() / 300) % 2 == 0;  // 300msごとに点滅
            timeColor = blink ? GetColor(255, 0, 0) : GetColor(0, 0, 0);
        }
        else {
            timeColor = GetColor(0, 0, 0); // 通常は黒
        }

        DrawFormatString(190, 160, timeColor, "%d", timeSec);
        SetFontSize(70);

        //  Scorenumber表示（得点）  スコアを5桁ゼロ埋めで表示
        DrawFormatString(80, 300, GetColor(0, 0, 0), "%05d", score);


        //ハートごとの得点表示
        SetFontSize(40); // ← ここで文字サイズを大きく設定
        DrawFormatString(170, 440, GetColor(0, 0, 0), "+100点");
        DrawFormatString(170, 535, GetColor(0, 0, 0), "-50点");
        DrawFormatString(170, 630, GetColor(0, 0, 0), "+300点");

    }

    // 画面ワイプ処理
    if (isWiping) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, wipeAlpha);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 元に戻す
    }


    // ハート生成範囲を赤線で表示
    //const int dropAreaLeft = 320 + 96;
    //const int dropAreaRight = 960 - 96;

    // 上下の位置は画面全体に合わせて線を引く
    //DrawLine(dropAreaLeft, 0, dropAreaLeft, 720, GetColor(255, 0, 0));   // 左の赤線
    //DrawLine(dropAreaRight, 0, dropAreaRight, 720, GetColor(255, 0, 0)); // 右の赤線

}
