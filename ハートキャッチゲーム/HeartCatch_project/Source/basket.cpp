#include "Basket.h"

Basket::Basket(int imageHandle)
{
    x = 320;
    y = 580;
    width = 80;
    height = 80;
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
    const int leftLimit = 320+25;
    const int rightLimit = 960-58;

    if (x < leftLimit) x = leftLimit;
    if (x > rightLimit - width) x = rightLimit - width;
}

void Basket::Draw()
{
    DrawGraph(x, y, basketImage, TRUE); // ← Boxではなく画像を描画
}

bool Basket::CheckCatch(float fx, float fy)
{
    const int fruitSize = 96; // 例：果物の半径やサイズ

    return (fx + fruitSize > x && fx - fruitSize < x + width &&
        fy + fruitSize > y && fy - fruitSize < y + height);
}
