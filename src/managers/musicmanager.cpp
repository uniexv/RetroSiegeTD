#include "musicmanager.hpp"
#include "../gui/mainmenu.hpp"
#include "../namespaces/music.hpp"
#include <cassert>


void MusicManager::SyncGameState(const GameState gameState)
{
    m_gameState = gameState;
}
void MusicManager::Update() 
{
    GameMusic::UpdateMusic();


    if (m_gameState == GameState::Started)
    {
        if (IsMusicStreamPlaying(GameMusic::g_towerDefenseMenu))
        {
            StopMusicStream(GameMusic::g_towerDefenseMenu);
        }
        if (!IsMusicStreamPlaying(GameMusic::g_towerDefenseMain))
        {
            PlayMusicStream(GameMusic::g_towerDefenseMain);
        }
    }
    else if(!gui_mainMenu->IsInPauseMode())
    {
        if (IsMusicStreamPlaying(GameMusic::g_towerDefenseMain))
        {
            StopMusicStream(GameMusic::g_towerDefenseMain);
        }
        if (!IsMusicStreamPlaying(GameMusic::g_towerDefenseMenu))
        {
            PlayMusicStream(GameMusic::g_towerDefenseMenu);
        }
    }
        
}
void MusicManager::InjectDependencies(MainMenu* mainMenuGui)
{
    gui_mainMenu = mainMenuGui;
}
void MusicManager::Init() 
{
    assert(gui_mainMenu != nullptr && "gui_mainMenu dependency wasn't injected");
}
