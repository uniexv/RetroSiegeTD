#include "../structs/label.hpp"

class PSManager;
class GuiManager;
class PlayerStats
{
private:
    GuiManager *mgr_gui = nullptr;
    PSManager *mgr_ps = nullptr;

private:
    void InitLabels();

public:
    void InjectDependencies(GuiManager *guiManager, PSManager *psManager);
    void Init();
};
