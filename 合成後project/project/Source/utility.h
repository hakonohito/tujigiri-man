#pragma once

#include <vector>

namespace KeyUtility
{
    void Init();
    bool CheckTrigger(int keyCode);     //  キー入力のトリガー取得
    bool CheckRepeat(int keyCode);      //  キー入力のリピート取得
}