#include "Basket.h"

Basket::Basket(int imageHandle)
{
    x = 320;
    y = 400;
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

    // 画面外に出ないように制限
    if (x < 0) x = 0;
    if (x > 640 - width) x = 640 - width;
}

void Basket::Draw()
{
    DrawGraph(x, y, basketImage, TRUE); // ← Boxではなく画像を描画
}

bool Basket::CheckCatch(float fx, float fy)
{
    const int fruitSize = 64; // 例：果物の半径やサイズ

    return (fx + fruitSize > x && fx - fruitSize < x + width &&
        fy + fruitSize > y && fy - fruitSize < y + height);
}
