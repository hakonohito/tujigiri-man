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
        DrawGraph(x, y, redpict, TRUE);
        break;
    case 1: // Blue
        DrawGraph(x, y, bluepict, TRUE);
        break;
    case 2: // Yellow
        DrawGraph(x, y, yellowpict, TRUE);
        break;
    }
}
