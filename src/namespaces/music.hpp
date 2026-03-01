#pragma once
#include <raylib.h>

namespace GameMusic
{
    extern bool g_playMusic;
    extern Music g_towerDefenseMain;
    extern Music g_towerDefenseMenu;

    void InitAudio();
    void UpdateMusic();
    void LoadSounds();
    void LoadMusic();
    void UnloadMusic();
    void UnloadSounds();
    void UnloadAudio();
}
