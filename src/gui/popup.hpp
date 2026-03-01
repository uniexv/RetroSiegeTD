#pragma once
#include <vector>

class MessageManager;
class GuiManager;
class Popup
{
private:
    MessageManager *mgr_message = nullptr;
    GuiManager *mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(MessageManager *messageManager, GuiManager *guiManager);
    void Init();
};
