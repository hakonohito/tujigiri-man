#include "fruit.h"
#include "DxLib.h"

fruit::fruit()
{
    x = 400 + rand() % 480; // 中央オレンジエリアに限定
    y = -64;
    dptime = 4;
    type = rand() % 3;
}

fruit::~fruit()
{
}

void fruit::Update()
{
    y += dptime;

    if (y > 480)
    {
        type = rand() % 3;
        x = 400 + rand() % 480; // 再生成時も中央に限定
        y = -64;
    }
}

void fruit::Draw()
{
    switch (type)
    {
    case 0: // いちご
        DrawRectGraph(x, y, 0, 0, 64, 64, itigopict, TRUE);
        break;
    case 1: // みかん
        DrawRectGraph(x, y, 0, 256, 64, 64, mikannpict, TRUE);
        break;
    case 2: // ぶどう
        DrawRectGraph(x, y, 0, 384, 64, 64, budoupict, TRUE);
        break;
    }
}
