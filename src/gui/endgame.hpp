#pragma once

class Game;
class PlayerManager;
class GuiManager;

class EndGame
{
private:
    Game *mgr_game = nullptr;
    PlayerManager *mgr_player = nullptr;
    GuiManager *mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(Game *game, PlayerManager *playerManager, GuiManager *guiManager);
    void Init();
};
