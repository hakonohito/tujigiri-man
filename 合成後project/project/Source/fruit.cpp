#include "fruit.h"
#include "DxLib.h"


fruit::fruit()
{
    x = dropLeft + rand() % (dropRight - dropLeft);
    y = -64;
    type = rand() % 3;
    dptime = GetSpeedByType(type); // ← 関数で速度を決定
}

fruit::~fruit()
{
}

void fruit::Update()
{
    y += dptime;

    if (y > 720) {
        type = rand() % 3;
        x = dropLeft + rand() % (dropRight - dropLeft);
        y = -64;
        dptime = GetSpeedByType(type); // ← 再生成時も速度を更新
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

void fruit::setDropArea(int left, int right)
{
    dropLeft = left;
    dropRight = right;
}
