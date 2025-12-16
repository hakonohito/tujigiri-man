#include "DxLib.h"
#include "SoundManager.h"

int SoundManager::bgmHandle;

void SoundManager::Init() {
    bgmHandle = LoadSoundMem("data/SE_BGM/heartgamescene/BGM.mp3");
}

void SoundManager::PlayBGM() {
    PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopBGM() {
    StopSoundMem(bgmHandle);
}