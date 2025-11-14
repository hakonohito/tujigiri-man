#include "fruit.h"
#include "DxLib.h"

fruit::fruit()
{
    x = rand() % 640;
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
        x = rand() % 640;
        y = -64;
    }
}

void fruit::Draw()
{
    switch (type)
    {
    case 0: // ‚¢‚¿‚²
        DrawRectGraph(x, y, 0, 0, 64, 64, itigopict, TRUE);
        break;
    case 1: // ‚Ý‚©‚ñ
        DrawRectGraph(x, y, 0, 256, 64, 64, mikannpict, TRUE);
        break;
    case 2: // ‚Ô‚Ç‚¤
        DrawRectGraph(x, y, 0, 384, 64, 64, budoupict, TRUE);
        break;
    }
}
