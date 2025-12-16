#pragma once
class SoundManager
{
public:
    static void Init();
    static void PlayBGM();
    static void StopBGM();
private:
    static int bgmHandle;

};

