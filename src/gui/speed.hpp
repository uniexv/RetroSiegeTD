#pragma once

class GuiManager;

class Speed
{
private:
    GuiManager *mgr_gui = nullptr;

public:
    void InjectDependencies(GuiManager *guiManager);
    void InitLabels();
    void InitButtons();
    void Init();
};
