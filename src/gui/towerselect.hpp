#pragma once
#include <vector>
#include "../structs/button.hpp"
#include "../structs/label.hpp"

class TowerManager;
class GuiManager;
class PSManager;
class TowerSelect
{
private:
    TowerManager *mgr_tower = nullptr;
    GuiManager *mgr_gui = nullptr;
    PSManager *mgr_ps = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(TowerManager *towerManager, GuiManager *guiManager, PSManager *psManager);
    void Init();
};
