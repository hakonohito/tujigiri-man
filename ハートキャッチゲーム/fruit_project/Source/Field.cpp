#include "Field.h"
#include "DxLib.h"

Field::Field()
{
    groundImage = LoadGraph("data/image/bgchar.png"); // © ‘‚Ì’n–Ê‰æ‘œi¶ã‚Ì•”•ªj
}

Field::~Field() {}

void Field::Draw()
{
    for (int x = 0; x < 12; x++)
    {
        DrawRectGraph(x * 64, 540, 0, 32, 64, 64, groundImage, TRUE);
    }
}
