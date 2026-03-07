#include <cstddef>
#include "../utility/debugutil.hpp"
#include "../namespaces/loading.hpp"
#include "../namespaces/music.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/enemies.hpp"
#include "../namespaces/bullets.hpp"
#include "game.hpp"

void Game::HandleInput()
{
    if (IsKeyPressed(KEY_P))
    {
        if (m_gameState == GameState::Started)
        {
            m_gameState = GameState::Menu;
        }
    }
}
void Game::UpdateDebug()
{
#ifdef RELEASE
    return;
#endif
    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
    if (IsKeyPressed(KEY_F1))
    {
        StartGame();
    }
    if (IsKeyPressed(KEY_M))
    {
        mgr_ps.AddMoney(3000);
    }
    if (IsKeyPressed(KEY_F3))
    {
        Settings::g_debugView = !Settings::g_debugView;
    }
    if (IsKeyPressed(KEY_F4))
    {
        if (m_gameState != GameState::Started)
        {
            return;
        }

        mgr_enemy.SpawnEnemy(EnemyType::Summoner);
    }
    if (IsKeyPressed(KEY_F5))
    {
        if (m_gameState != GameState::Started)
        {
            return;
        }

        mgr_enemy.SpawnEnemy(EnemyType::SkeletonKing);
    }
}
void Game::Update()
{
    UpdateDebug();

    const bool gameStarted = (m_gameState == GameState::Started);
    const float deltaTime = GetFrameTime() * Settings::g_gameSpeed;

    HandleInput();
    mgr_gui.SyncGameState(m_gameState);
    mgr_gui.Update(deltaTime);
    if (gameStarted)
    {

        mgr_enemy.Update(deltaTime);
        mgr_tile.Update();
        mgr_tower.Update(deltaTime);
        mgr_bullet.Update(deltaTime);
        mgr_wave.Update(deltaTime);
        mgr_player.Update();
        mgr_particle.Update(deltaTime);
        mgr_message.Update(deltaTime);
    }

    mgr_music.SyncGameState(m_gameState);
    mgr_music.Update();
}
void Game::MakeTextureFrame() const
{
    BeginTextureMode(m_frame);
    ClearBackground(BLACK);
    const bool gameStarted = (m_gameState == GameState::Started);
    constexpr uint8_t boundingWidth = 105;
    constexpr uint8_t screenOffset = boundingWidth;
    constexpr Color boundingColor = DARKGRAY;

    if (gameStarted)
    {
        Settings::g_boundingSize = boundingWidth;
        Settings::g_gameScale = 4;

        mgr_tile.Draw(screenOffset);
        mgr_enemy.Draw(screenOffset);
        mgr_tower.Draw(screenOffset);
        mgr_bullet.Draw(screenOffset);
        mgr_particle.Draw(screenOffset);
    }

    DrawRectangle(0, 0, boundingWidth, p_gameHeight, boundingColor);
    DrawRectangle(p_gameWidth - boundingWidth, 0, boundingWidth, p_gameHeight, boundingColor);

    mgr_gui.Draw();

    EndTextureMode();
}
void Game::Draw() const
{
    MakeTextureFrame();
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        m_frame.texture,
        {0, 0, static_cast<float>(p_gameWidth), static_cast<float>(-p_gameHeight)},
        {0, 0, static_cast<float>(p_scaledWidth), static_cast<float>(p_scaledHeight)},
        {0, 0},
        0.0f,
        WHITE);

    EndDrawing();
}
void Game::InitManagers()
{
    mgr_ps.Init();
    mgr_tile.Init();

    GameMap map;
    map.p_id = 1;
    map.p_tileIdMap = Loading::LoadTileTypes("src/resources/maps/Map1Tiles.png");
    map.p_pathDirections = Loading::LoadMapDirections("src/resources/maps/Map1Directions.png");
    mgr_tile.LoadMap(map);

    mgr_bullet.Init();
    mgr_enemy.InjectDependencies(&mgr_tile, &mgr_bullet, &mgr_ps);
    mgr_enemy.Init();

    mgr_tower.InjectDependencies(&mgr_tile, &mgr_enemy, &mgr_bullet, &mgr_ps, &mgr_particle, &mgr_message);
    mgr_tower.Init();

    mgr_wave.InjectDependencies(&mgr_enemy, &mgr_ps, &mgr_tower, &mgr_message);
    mgr_wave.Init();

    mgr_player.InjectDependencies(&mgr_ps, &mgr_tower, &mgr_enemy, &mgr_wave, &mgr_bullet);
    mgr_player.Init();

    mgr_music.InjectDependencies(&gui_mainMenu);
    mgr_music.Init();
    mgr_particle.Init();

    mgr_message.Init();
}
void Game::InitGui()
{
    gui_waveCounter.InjectDependencies(&mgr_wave, &mgr_gui, &mgr_player, &mgr_message);
    gui_waveCounter.Init();
    gui_towerSelect.InjectDependencies(&mgr_tower, &mgr_gui, &mgr_ps);
    gui_towerSelect.Init();
    gui_towerPlace.InjectDependencies(&mgr_tower, &mgr_gui);
    gui_towerPlace.Init();
    gui_playerStats.InjectDependencies(&mgr_gui, &mgr_ps);
    gui_playerStats.Init();
    gui_mainMenu.InjectDependencies(&mgr_gui, this);
    gui_mainMenu.Init();
    gui_enemyHover.InjectDependencies(&mgr_enemy, &mgr_gui);
    gui_enemyHover.Init();
    gui_speed.InjectDependencies(&mgr_gui);
    gui_speed.Init();
    gui_popup.InjectDependencies(&mgr_message, &mgr_gui);
    gui_popup.Init();
    gui_endGame.InjectDependencies(this, &mgr_player, &mgr_gui);
    gui_endGame.Init();
}
void Game::InitSprites()
{
    Sprites::LoadTextures();
}
void Game::InitAudio()
{
    GameMusic::InitAudio();
    GameMusic::LoadSounds();
    GameMusic::LoadMusic();
}
void Game::InitDatas()
{
    Towers::InitTowerData();
    Enemies::InitEnemyData();
    Bullets::InitBulletData();
}
void Game::InitMembers()
{
    m_frame = LoadRenderTexture(p_gameWidth, p_gameHeight);
}
void Game::InitGame()
{
    InitWindow(p_screenWidth, p_screenHeight, "Retro Siege TD");
    SetExitKey(KEY_NULL);
    SetTargetFPS(120);
    Settings::g_gameFont = LoadFontEx("src/resources/fonts/Vaticanus-G3yVG.ttf", 8, 0, 0);
    SetTextureFilter(Settings::g_gameFont.texture, TEXTURE_FILTER_POINT);
    m_gameState = GameState::Menu;
}
void Game::Shutdown()
{
    if (m_shutingDown)
    {
        return;
    }

    m_shutingDown = true;

    Sprites::UnloadTextures();
    GameMusic::UnloadSounds();
    GameMusic::UnloadMusic();
    GameMusic::UnloadAudio();

    UnloadRenderTexture(m_frame);
    CloseWindow();
}

void Game::StartGame()
{
    m_gameState = GameState::Started;
}
void Game::CloseGame()
{
    m_gameState = GameState::Ended;
}
void Game::Init()
{
    InitGame();
    InitSprites();
    InitDatas();
    InitMembers();
    InitManagers();
    InitAudio();
    InitGui();
}
void Game::Restart()
{
    mgr_enemy.ClearEnemiesVector();
    mgr_wave.ClearActiveWaves();
    mgr_wave.ClearUnactiveWaves();
    mgr_bullet.ClearBulletsVector();
    mgr_ps.SetMoney(0);
    InitManagers();
}
void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (IsWindowMinimized())
        {
            continue;
        }
        
        Update();
        Draw();

        if (m_gameState == GameState::Ended)
        {
            Shutdown();
        }
    }
    Shutdown();
}
