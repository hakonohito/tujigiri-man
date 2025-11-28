#include "fruit.h"
#include "DxLib.h"


fruit::fruit()
{
    // dropLeft, dropRight ÇÕ setDropArea() Ç≈ê›íËÇ≥ÇÍÇÈëOíÒ
    x = dropLeft + rand() % (dropRight - dropLeft);
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

    if (y > 720) //âÊñ â∫Ç‹Ç≈óàÇΩÇÁçƒê∂ê¨
    {
        type = rand() % 3;
        x = dropLeft + rand() % (dropRight - dropLeft); // îÕàÕÇégÇ§
        y = -64;
    }
}

void fruit::Draw()
{
    switch (type)
    {
    case 0: // Red
        DrawRotaGraph(x, y, 1.5, 0.0, redpict, TRUE);   // 1.5î{Ç…ägëÂ
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
