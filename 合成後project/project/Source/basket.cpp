#include "Basket.h"

Basket::Basket(int imageHandle)
{
    x = 320;
    y = 580;
    width = 116;
    height = 71;
    basketImage = imageHandle;
}


Basket::~Basket() {}

void Basket::Update()
{
    if (CheckHitKey(KEY_INPUT_A)) {
        x -= 5;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        x += 5;
    }

    // loveletterが画面外に出ないように制限
    const int leftLimit = 320 + 110;
    const int rightLimit = 960 + 4;

    if (x < leftLimit) x = leftLimit;
    if (x > rightLimit - width) x = rightLimit - width;
}

void Basket::Draw()
{
    DrawRotaGraph(x, y, 1.5, 0.0, basketImage, TRUE); // love letter 画像　1.5倍拡大
    // 判定枠を中心基準で描画
    int left = x - width / 2;
    int right = x + width / 2;
    int top = y - height / 2;
    int bottom = y + height / 2;
    // 判定枠を可視化（デバッグ用）
    DrawBox(left, top, right, bottom, GetColor(255, 0, 0), FALSE); // 赤枠
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
