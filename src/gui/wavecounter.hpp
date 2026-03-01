#pragma once
#include "../structs/tempmessage.hpp"

class PlayerManager;
class WaveManager;
class GuiManager;
class MessageManager;

class WaveCounter
{
private:
    PlayerManager *mgr_player = nullptr;
    WaveManager *mgr_wave = nullptr;
    GuiManager *mgr_gui = nullptr;
    MessageManager *mgr_message = nullptr;

private:
    void InitButtons();

public:
    void InjectDependencies(WaveManager *waveManager, GuiManager *guiManager, PlayerManager *playerManager, MessageManager *messageManager);
    void Init();
};