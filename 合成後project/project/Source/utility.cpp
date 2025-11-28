#include <sstream>
#include <DxLib.h>
#include "Utility.h"
#include "time.h"
#include "../Library/Time.h"

namespace KeyBuffer
{
    static const float REPEAT_TIME = 0.5f;      //  キーリピート間隔(sec)

    static bool triggerKeyBufferArray[0xff];    //  トリガーキーバッファ
    static float repeatKeyBufferArray[0xff];    //  リピートキーバッファ
}

//  キー関連処理の初期化
void KeyUtility::Init()
{
    for (int i = 0; i < 0xff; i++)
    {
        KeyBuffer::triggerKeyBufferArray[i] = false;
        KeyBuffer::repeatKeyBufferArray[i] = 0.0f;
    }
}

//  キー入力のトリガー取得
bool KeyUtility::CheckTrigger(int keyCode)
{
    bool triggerFlag = false;

    //  該当キーが押されている
    if (CheckHitKey(keyCode) != 0)
    {
        //  前フレームで押されていなかった＝トリガー
        if (!KeyBuffer::triggerKeyBufferArray[keyCode])
        {
            triggerFlag = true;
        }
        //キーバッファに登録
        KeyBuffer::triggerKeyBufferArray[keyCode] = true;
    }
    else
    {
        //キーバッファに登録
        KeyBuffer::triggerKeyBufferArray[keyCode] = false;
    }

    return triggerFlag;
}

//  キー入力のリピート取得
bool KeyUtility::CheckRepeat(int keyCode)
{
    bool repeatFlag = false;

    //  該当キーが押されている
    if (CheckHitKey(keyCode) != 0)
    {
        //  初回入力はリピート入力あり
        if (abs(KeyBuffer::repeatKeyBufferArray[keyCode] - 0.0f) < DBL_EPSILON)     //  float同士の比較(精度を考慮)
        {
            KeyBuffer::repeatKeyBufferArray[keyCode] = Time::DeltaTime();
            repeatFlag = true;
        }
        else
        {
            //  リピート間隔時間押されていたら、リピート入力とする
            KeyBuffer::repeatKeyBufferArray[keyCode] += Time::DeltaTime();
            if (KeyBuffer::repeatKeyBufferArray[keyCode] >= KeyBuffer::REPEAT_TIME)
            {
                repeatFlag = true;
            }
        }
    }
    else
    {
        //キーバッファに登録
        KeyBuffer::repeatKeyBufferArray[keyCode] = 0.0f;
    }

    return repeatFlag;
}

