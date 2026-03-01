#pragma once

class EnemyManager;
class GuiManager;
class EnemyHover
{
private:
    EnemyManager *mgr_enemy = nullptr;
    GuiManager *mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(EnemyManager *enemyManager, GuiManager *guiManager);
    void Init();
};
