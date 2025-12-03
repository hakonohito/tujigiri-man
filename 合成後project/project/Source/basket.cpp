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

    // 判定枠を可視化（デバッグ用）
    DrawBox(x, y, x + width, y + height, GetColor(255, 0, 0), FALSE);
}

bool Basket::CheckCatch(float fx, float fy)
{
    const int fruitSize = 96; // 例：果物の半径やサイズ

    return (fx + fruitSize > x && fx - fruitSize < x + width &&
        fy + fruitSize > y && fy - fruitSize < y + height);
}
