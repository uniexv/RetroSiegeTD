#pragma once
#include "../structs/wave.hpp"
#include "../structs/tempmessage.hpp"

class MessageManager;
class TowerManager;
class EnemyManager;
class PSManager;

class WaveManager
{
private:
    std::vector<EnemyWave> m_unactiveWaves = {};
    std::vector<EnemyWave> m_activeWaves = {};
    float m_spawnTime = 0.0f;
    float m_waveTime = 0.0f;
    EnemyManager *mgr_enemy = nullptr;
    PSManager *mgr_ps = nullptr;
    TowerManager *mgr_tower = nullptr;
    MessageManager *mgr_message = nullptr;

private:
    void PreKillWave(const EnemyWave wave);
    void KillWave(const uint32_t waveId);
    void RemoveEnemySpawn(EnemyWave &wave, const size_t index);
    void ActivateWave(EnemyWave *wave);
    void RemoveUnactiveWave(const uint32_t id);
    void RemoveActiveWave(const uint32_t id);
    void UpdateUnactiveWaves();
    void UpdateActiveWaves(const float deltaTime);
    void LoadWaves();


public:
    WaveManager() = default;

    EnemyWave *GetNextWave();
    EnemyWave *GetCurrentWave();
    const bool ShouldWaveStart() const;
    bool IsSkipAllowed();
    void SkipWave();
    void ClearActiveWaves();
    void ClearUnactiveWaves();
    void Update(const float deltaTime);
    void InjectDependencies(EnemyManager *enemyManager, PSManager *psManager, TowerManager *towerManager, MessageManager *messageManager);
    void Init();

};
