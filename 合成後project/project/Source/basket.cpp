#include "Basket.h"

Basket::Basket(int imageHandle)
{
    x = 1280/2; //ラブレター初期位置
    y = 580;
    width = 90; 
    height = 30; 
    basketImage = imageHandle;
}


Basket::~Basket() {}

void Basket::Update()
{
    if (CheckHitKey(KEY_INPUT_A)) {
        x -= 6;// ← Aキーで左に6ピクセル移動 (赤ハートの倍)
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        x += 6;// ← Dキー
    }

    // loveletterが画面外に出ないように制限
    const int leftLimit = 400;
    const int rightLimit = 970;

    if (x < leftLimit) x = leftLimit;
    if (x > rightLimit - width) x = rightLimit - width;
}

void Basket::Draw()
{
    DrawRotaGraph(x, y, 1.0, 0.0, basketImage, TRUE); // love letter 画像サイズ　116＊71
    // 判定枠を中心基準で描画
    int left = x - width / 2;
    int right = x + width / 2;
    int top = y - height / 2;
    int bottom = y + height / 2;
    // 判定枠を可視化（デバッグ用）
    //DrawBox(left, top, right, bottom, GetColor(255, 0, 0), FALSE); // 赤枠
}

bool Basket::CheckCatch(float fx, float fy)
{
    const int fruitSize = 48; // 例：ハートの半径

    // 判定枠を中心基準に修正
    int left = x - width / 2;
    int right = x + width / 2;
    int top = y - height / 2;
    int bottom = y + height / 2;

    return (fx + fruitSize > left && fx - fruitSize < right &&
        fy + fruitSize > top && fy - fruitSize < bottom);
}
