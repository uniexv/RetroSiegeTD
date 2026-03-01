#include "music.hpp"
#include <raylib.h>

namespace GameMusic
{
    bool g_playMusic = true;

    Music g_towerDefenseMain = {};
    Music g_towerDefenseMenu = {};

    void InitAudio()
    {
        InitAudioDevice();
    }

    void UpdateMusic()
    {
        if (!g_playMusic)
        {
            if (IsMusicStreamPlaying(g_towerDefenseMain))
            {
                UpdateMusicStream(g_towerDefenseMain);
            }
            if (IsMusicStreamPlaying(g_towerDefenseMenu))
            {
                UpdateMusicStream(g_towerDefenseMenu);
            }
        }
    }

    void LoadSounds()
    {
    }

    void LoadMusic()
    {
        g_towerDefenseMain = LoadMusicStream("src/resources/audio/calm1.ogg");
        SetMusicVolume(g_towerDefenseMain, 0.15f);
        g_towerDefenseMenu = LoadMusicStream("src/resources/audio/calm2.ogg");
        SetMusicVolume(g_towerDefenseMenu, 0.15f);
    }

    void UnloadMusic()
    {
        if (g_towerDefenseMain.ctxData)
        {
            if (IsMusicStreamPlaying(g_towerDefenseMain))
                StopMusicStream(g_towerDefenseMain);
            UnloadMusicStream(g_towerDefenseMain);
            g_towerDefenseMain = {};
        }

        if (g_towerDefenseMenu.ctxData)
        {
            if (IsMusicStreamPlaying(g_towerDefenseMenu))
                StopMusicStream(g_towerDefenseMenu);
            UnloadMusicStream(g_towerDefenseMenu);
            g_towerDefenseMenu = {};
        }
    }

    void UnloadSounds()
    {
    }

    void UnloadAudio()
    {
        CloseAudioDevice();
    }
}
