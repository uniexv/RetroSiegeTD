#pragma once

#include "../enums/gamestate.hpp"
class MainMenu;
class MusicManager
{
private:

    GameState m_gameState = GameState::Menu;
    MainMenu* gui_mainMenu = nullptr;

public:
    MusicManager() = default;

    void SyncGameState(const GameState gameState);
    void Update();
    void InjectDependencies(MainMenu* mainMenuGui);
    void Init();
};
