#pragma once
#include <raylib.h>
#include "../enums/gamestate.hpp"
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/playermanager.hpp"
#include "../managers/musicmanager.hpp"
#include "../managers/particlemanager.hpp"
#include "../managers/messagemanager.hpp"
#include "../gui/wavecounter.hpp"
#include "../gui/towerselect.hpp"
#include "../gui/towerplace.hpp"
#include "../gui/playerstats.hpp"
#include "../gui/speed.hpp"
#include "../gui/mainmenu.hpp"
#include "../gui/enemyhover.hpp"
#include "../gui/popup.hpp"
#include "../gui/endgame.hpp"


class Game
{
private:

    bool m_shutingDown = false;
    RenderTexture2D m_frame = {};
    GameState m_gameState = GameState::Menu;

    TileManager mgr_tile = {};
    EnemyManager mgr_enemy = {};
    TowerManager mgr_tower = {};
    BulletManager mgr_bullet = {};
    WaveManager mgr_wave = {};
    GuiManager mgr_gui = {};
    PSManager mgr_ps = {};
    PlayerManager mgr_player = {};
    MusicManager mgr_music = {};
    ParticleManager mgr_particle = {};
    MessageManager mgr_message = {};

    EnemyHover gui_enemyHover = {};
    MainMenu gui_mainMenu = {};
    WaveCounter gui_waveCounter = {};
    TowerSelect gui_towerSelect = {};
    TowerPlace gui_towerPlace = {};
    PlayerStats gui_playerStats = {};
    Speed gui_speed = {};
    Popup gui_popup = {};
    EndGame gui_endGame = {};

private: 

    void HandleInput();
    void UpdateDebug();
    void Update();
    void MakeTextureFrame() const;
    void Draw() const;
    void InitManagers();
    void InitGui();
    void InitSprites();
    void InitAudio();
    void InitDatas();
    void InitMembers();
    void InitGame();

    void Shutdown();
public: 
    const int p_gameHeight = 270;
    const int p_gameWidth = 480;
    const int p_scaledHeight = 1080;
    const int p_scaledWidth = 1920;
    const int p_screenHeight = 1080;
    const int p_screenWidth = 1920;

public: 
    Game() = default;
    ~Game() = default;

    void StartGame();
    void CloseGame();

    void Init();
    void Restart();
    void Run();
};