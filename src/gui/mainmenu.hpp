#pragma once

class GuiManager;
class Game;

class MainMenu
{
private:

    bool m_pauseMode = false;
    Game *mgr_game = nullptr;
    GuiManager *mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();
public:
    bool IsInPauseMode();
    void InjectDependencies(GuiManager *guiManager, Game *game);
    void Init();
};
