#pragma once
#include <memory>

class PSManager;
class TowerManager;
class EnemyManager;
class WaveManager;
class BulletManager;

enum PlayerState 
{
    Alive = 0,
    Dead = 1,
    Victory = 2
};

class PlayerManager
{
private:

    PSManager *mgr_ps = nullptr;
    TowerManager *mgr_tower = nullptr;
    EnemyManager *mgr_enemy = nullptr;
    WaveManager *mgr_wave = nullptr;
    BulletManager *mgr_bullet = nullptr;

    PlayerState m_playerState = PlayerState::Alive;

public:
    PlayerManager() = default;
    ~PlayerManager() = default;

    void OnGameOver();
    bool IsGameOver() const;
    PlayerState GetPlayerState() const;
    void Update();
    void InjectDependencies(PSManager *psManager, TowerManager *towerManager, EnemyManager *enemyManager, WaveManager *waveManager, BulletManager *bulletManager);
    void Init();
};
