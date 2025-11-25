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
    case 0: // Red
        DrawRotaGraph(x, y, 1.5, 0.0, redpict, TRUE);   // 1.5倍に拡大
        break;
    case 1: // Blue
        DrawRotaGraph(x, y, 1.5, 0.0, bluepict, TRUE);
        break;
    case 2: // Yellow
        DrawRotaGraph(x, y, 1.5, 0.0, yellowpict, TRUE);
        break;
    }
}
