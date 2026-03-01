#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "psmanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/messagemanager.hpp"
#include "../utility/debugutil.hpp"
#include <cassert>


void WaveManager::PreKillWave(const EnemyWave wave)
{
    mgr_message->InsertMessage(TempMessageKeys::Mes_WaveCounter, TempMessage{"Cleared: $" + std::to_string(wave.p_moneyReward) + "+", 3.0f, 3.0f});
    mgr_ps->AddMoney(wave.p_moneyReward);
}
void WaveManager::KillWave(const uint32_t waveId)
{
    for (EnemyWave &wave : m_activeWaves)
    {
        if (wave.p_id == waveId)
        {
            PreKillWave(wave);
            RemoveActiveWave(waveId);
            return;
        }
    }
}
void WaveManager::RemoveEnemySpawn(EnemyWave &wave, const size_t index)
{
    if (index < wave.p_enemySpawns.size())
    {
        wave.p_enemySpawns.erase(wave.p_enemySpawns.begin() + index);
    }
}
void WaveManager::ActivateWave(EnemyWave *wave)
{
    if (wave)
    {
        m_activeWaves.push_back(*wave);
        RemoveUnactiveWave(wave->p_id);
    }
}
void WaveManager::RemoveUnactiveWave(const uint32_t id)
{
    const auto eraseLambda = [id](const EnemyWave &wave)
    {
        return wave.p_id == id;
    };
    m_unactiveWaves.erase(std::remove_if(m_unactiveWaves.begin(), m_unactiveWaves.end(), eraseLambda), m_unactiveWaves.end());
}
void WaveManager::RemoveActiveWave(const uint32_t id)
{
    const auto eraseLambda = [id](const EnemyWave &wave)
    {
        return wave.p_id == id;
    };
    m_activeWaves.erase(std::remove_if(m_activeWaves.begin(), m_activeWaves.end(), eraseLambda), m_activeWaves.end());
}
void WaveManager::UpdateUnactiveWaves()
{
    if (!m_activeWaves.empty() || !ShouldWaveStart())
    {
        return;
    }

    EnemyWave *nextWave = GetNextWave();
    ActivateWave(nextWave);
}
void WaveManager::UpdateActiveWaves(const float deltaTime)
{
    if (m_activeWaves.empty())
    {
        return;
    }

    m_spawnTime += deltaTime;
    m_waveTime += deltaTime;

    int indexToDelete = -1;
    for (EnemyWave &wave : m_activeWaves)
    {
        for (size_t i = 0; i < wave.p_enemySpawns.size(); i++)
        {
            if (wave.p_enemySpawns[i].first < m_spawnTime)
            {
                mgr_enemy->SpawnEnemy(wave.p_enemySpawns[i].second);
                m_spawnTime = 0.0f;
                indexToDelete = i;
                break;
            }
        }
        if (indexToDelete != -1)
        {
            RemoveEnemySpawn(wave, indexToDelete);
        }
        if (wave.p_enemySpawns.empty() && mgr_enemy->IsEnemiesEmpty())
        {
            m_waveTime = 0.0f;
            KillWave(wave.p_id);
            return;
        }
    }
}
void WaveManager::LoadWaves()
{
    auto getTotalWaveTime = [](const EnemyWave wave)
    {
        float totalTime = 0.0f;
        for (auto &enemySpawn : wave.p_enemySpawns)
        {
            totalTime += enemySpawn.first;
        }
        return totalTime;
    };

    std::vector<std::pair<float, EnemyType>> enemySpawns1 = {};
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave1 = {};
    wave1.p_id = 1;
    wave1.p_moneyReward = 125;
    wave1.p_enemySpawns = enemySpawns1;
    wave1.p_totalWaveTime = getTotalWaveTime(wave1);
    m_unactiveWaves.push_back(wave1);

    std::vector<std::pair<float, EnemyType>> enemySpawns2 = {};
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave2 = {};
    wave2.p_id = 2;
    wave2.p_moneyReward = 150;
    wave2.p_enemySpawns = enemySpawns2;
    wave2.p_totalWaveTime = getTotalWaveTime(wave2);
    m_unactiveWaves.push_back(wave2);

    std::vector<std::pair<float, EnemyType>> enemySpawns3 = {};
    enemySpawns3.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns3.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns3.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns3.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns3.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns3.push_back({3.0f, EnemyType::QuickSlime});
    enemySpawns3.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns3.push_back({1.5f, EnemyType::QuickSlime});
    EnemyWave wave3 = {};
    wave3.p_id = 3;
    wave3.p_moneyReward = 175;
    wave3.p_enemySpawns = enemySpawns3;
    wave3.p_totalWaveTime = getTotalWaveTime(wave3);
    m_unactiveWaves.push_back(wave3);

    std::vector<std::pair<float, EnemyType>> enemySpawns4 = {};
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns4.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns4.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns4.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns4.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns4.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave4 = {};
    wave4.p_id = 4;
    wave4.p_moneyReward = 200;
    wave4.p_enemySpawns = enemySpawns4;
    wave4.p_totalWaveTime = getTotalWaveTime(wave4);
    m_unactiveWaves.push_back(wave4);

    std::vector<std::pair<float, EnemyType>> enemySpawns5 = {};
    enemySpawns5.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns5.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns5.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns5.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns5.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({3.0f, EnemyType::RedSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns5.push_back({1.5f, EnemyType::QuickSlime});
    EnemyWave wave5 = {};
    wave5.p_id = 5;
    wave5.p_moneyReward = 225;
    wave5.p_enemySpawns = enemySpawns5;
    wave5.p_totalWaveTime = getTotalWaveTime(wave5);
    m_unactiveWaves.push_back(wave5);

    std::vector<std::pair<float, EnemyType>> enemySpawns6 = {};
    enemySpawns6.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns6.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns6.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns6.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns6.push_back({3.0f, EnemyType::RedSlime});
    enemySpawns6.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns6.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns6.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns6.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns6.push_back({3.0f, EnemyType::RedSlime});
    enemySpawns6.push_back({1.0f, EnemyType::RedSlime});
    EnemyWave wave6 = {};
    wave6.p_id = 6;
    wave6.p_moneyReward = 250;
    wave6.p_enemySpawns = enemySpawns6;
    wave6.p_totalWaveTime = getTotalWaveTime(wave6);
    m_unactiveWaves.push_back(wave6);

    std::vector<std::pair<float, EnemyType>> enemySpawns7 = {};
    enemySpawns7.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns7.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns7.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns7.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns7.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns7.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns7.push_back({1.5f, EnemyType::QuickSlime});
    enemySpawns7.push_back({1.5f, EnemyType::QuickSlime});
    EnemyWave wave7 = {};
    wave7.p_id = 7;
    wave7.p_moneyReward = 275;
    wave7.p_enemySpawns = enemySpawns7;
    wave7.p_totalWaveTime = getTotalWaveTime(wave7);
    m_unactiveWaves.push_back(wave7);

    std::vector<std::pair<float, EnemyType>> enemySpawns8 = {};
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns8.push_back({1.5f, EnemyType::SmallSlime});
    enemySpawns8.push_back({1.5f, EnemyType::SmallSlime});
    enemySpawns8.push_back({1.5f, EnemyType::SmallSlime});
    EnemyWave wave8 = {};
    wave8.p_id = 8;
    wave8.p_moneyReward = 300;
    wave8.p_enemySpawns = enemySpawns8;
    wave8.p_totalWaveTime = getTotalWaveTime(wave8);
    m_unactiveWaves.push_back(wave8);

    std::vector<std::pair<float, EnemyType>> enemySpawns9 = {};
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns9.push_back({1.0f, EnemyType::SmallSlime});
    EnemyWave wave9 = {};
    wave9.p_id = 9;
    wave9.p_moneyReward = 325;
    wave9.p_enemySpawns = enemySpawns9;
    wave9.p_totalWaveTime = getTotalWaveTime(wave9);
    m_unactiveWaves.push_back(wave9);

    std::vector<std::pair<float, EnemyType>> enemySpawns10 = {};
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::RedSlime});
    enemySpawns10.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns10.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns10.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns10.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns10.push_back({1.0f, EnemyType::SmallSlime});
    enemySpawns10.push_back({3.0f, EnemyType::BigSlime});
    EnemyWave wave10 = {};
    wave10.p_id = 10;
    wave10.p_moneyReward = 350;
    wave10.p_enemySpawns = enemySpawns10;
    wave10.p_totalWaveTime = getTotalWaveTime(wave10);
    m_unactiveWaves.push_back(wave10);

    std::vector<std::pair<float, EnemyType>> enemySpawns11 = {};
    enemySpawns11.push_back({1.0f, EnemyType::Zombie});
    enemySpawns11.push_back({1.0f, EnemyType::Zombie});
    enemySpawns11.push_back({1.0f, EnemyType::Zombie});
    enemySpawns11.push_back({1.0f, EnemyType::Zombie});
    enemySpawns11.push_back({1.0f, EnemyType::Zombie});
    enemySpawns11.push_back({3.0f, EnemyType::BigSlime});
    enemySpawns11.push_back({3.0f, EnemyType::BigSlime});
    enemySpawns11.push_back({3.0f, EnemyType::BigSlime});
    EnemyWave wave11 = {};
    wave11.p_id = 11;
    wave11.p_moneyReward = 375;
    wave11.p_enemySpawns = enemySpawns11;
    wave11.p_totalWaveTime = getTotalWaveTime(wave11);
    m_unactiveWaves.push_back(wave11);

    std::vector<std::pair<float, EnemyType>> enemySpawns12 = {};
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns12.push_back({1.0f, EnemyType::Zombie});
    enemySpawns12.push_back({1.0f, EnemyType::Zombie});
    enemySpawns12.push_back({1.0f, EnemyType::Zombie});
    EnemyWave wave12 = {};
    wave12.p_id = 12;
    wave12.p_moneyReward = 400;
    wave12.p_enemySpawns = enemySpawns12;
    wave12.p_totalWaveTime = getTotalWaveTime(wave12);
    m_unactiveWaves.push_back(wave12);

    std::vector<std::pair<float, EnemyType>> enemySpawns13 = {};
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns13.push_back({0.5f, EnemyType::ElectricSlime});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({2.0f, EnemyType::ElectricSlime});
    enemySpawns13.push_back({0.5f, EnemyType::ElectricSlime});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({1.0f, EnemyType::Zombie});
    enemySpawns13.push_back({3.0f, EnemyType::ArmoredZombie});
    EnemyWave wave13 = {};
    wave13.p_id = 13;
    wave13.p_moneyReward = 425;
    wave13.p_enemySpawns = enemySpawns13;
    wave13.p_totalWaveTime = getTotalWaveTime(wave13);
    m_unactiveWaves.push_back(wave13);

    std::vector<std::pair<float, EnemyType>> enemySpawns14 = {};
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::ElectricSlime});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns14.push_back({1.5f, EnemyType::Skeleton});
    EnemyWave wave14 = {};
    wave14.p_id = 14;
    wave14.p_moneyReward = 450;
    wave14.p_enemySpawns = enemySpawns14;
    wave14.p_totalWaveTime = getTotalWaveTime(wave14);
    m_unactiveWaves.push_back(wave14);

    std::vector<std::pair<float, EnemyType>> enemySpawns15 = {};
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({2.0f, EnemyType::ArmoredZombie});
    enemySpawns15.push_back({2.0f, EnemyType::ArmoredZombie});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({1.5f, EnemyType::Skeleton});
    enemySpawns15.push_back({3.0f, EnemyType::Summoner});
    EnemyWave wave15 = {};
    wave15.p_id = 15;
    wave15.p_moneyReward = 475;
    wave15.p_enemySpawns = enemySpawns15;
    wave15.p_totalWaveTime = getTotalWaveTime(wave15);
    m_unactiveWaves.push_back(wave15);

    std::vector<std::pair<float, EnemyType>> enemySpawns16 = {};
    enemySpawns16.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns16.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns16.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns16.push_back({5.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns16.push_back({1.0f, EnemyType::Skeleton});
    EnemyWave wave16 = {};
    wave16.p_id = 16;
    wave16.p_moneyReward = 500;
    wave16.p_enemySpawns = enemySpawns16;
    wave16.p_totalWaveTime = getTotalWaveTime(wave16);
    m_unactiveWaves.push_back(wave16);

    std::vector<std::pair<float, EnemyType>> enemySpawns17 = {};
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns17.push_back({1.0f, EnemyType::Skeleton});
    EnemyWave wave17 = {};
    wave17.p_id = 17;
    wave17.p_moneyReward = 525;
    wave17.p_enemySpawns = enemySpawns17;
    wave17.p_totalWaveTime = getTotalWaveTime(wave17);
    m_unactiveWaves.push_back(wave17);

    std::vector<std::pair<float, EnemyType>> enemySpawns18 = {};
    enemySpawns18.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns18.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns18.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns18.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns18.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns18.push_back({1.0f, EnemyType::Skeleton});
    EnemyWave wave18 = {};
    wave18.p_id = 18;
    wave18.p_moneyReward = 550;
    wave18.p_enemySpawns = enemySpawns18;
    wave18.p_totalWaveTime = getTotalWaveTime(wave18);
    m_unactiveWaves.push_back(wave18);

    std::vector<std::pair<float, EnemyType>> enemySpawns19 = {};
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::Skeleton});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({1.0f, EnemyType::SkeletonWarrior});
    enemySpawns19.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns19.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns19.push_back({2.5f, EnemyType::SkeletonGuardian});
    EnemyWave wave19 = {};
    wave19.p_id = 19;
    wave19.p_moneyReward = 575;
    wave19.p_enemySpawns = enemySpawns19;
    wave19.p_totalWaveTime = getTotalWaveTime(wave19);
    m_unactiveWaves.push_back(wave19);

    std::vector<std::pair<float, EnemyType>> enemySpawns20 = {};
    enemySpawns20.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns20.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns20.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns20.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns20.push_back({2.5f, EnemyType::SkeletonGuardian});
    enemySpawns20.push_back({5.0f, EnemyType::SkeletonKing});
    EnemyWave wave20 = {};
    wave20.p_id = 20;
    wave20.p_moneyReward = 600;
    wave20.p_enemySpawns = enemySpawns20;
    wave20.p_totalWaveTime = getTotalWaveTime(wave20);
    m_unactiveWaves.push_back(wave20);

    uint32_t totalEnemies = 0;
    for (size_t i = 0; i < m_unactiveWaves.size(); i++)
    {
        totalEnemies += m_unactiveWaves[i].p_enemySpawns.size();
    }
    mgr_enemy->ReserveEnemies(totalEnemies);
}

EnemyWave *WaveManager::GetNextWave()
{
    if (m_unactiveWaves.empty())
        return nullptr;

    EnemyWave *smallest = &m_unactiveWaves[0];
    for (auto &wave : m_unactiveWaves)
    {
        if (wave.p_id < smallest->p_id)
        {
            smallest = &wave;
        }
    }
    return smallest;
}
EnemyWave *WaveManager::GetCurrentWave()
{
    if (m_activeWaves.empty())
        return nullptr;

    EnemyWave *biggest = &m_activeWaves[0];
    for (auto &wave : m_activeWaves)
    {
        if (wave.p_id > biggest->p_id)
        {
            biggest = &wave;
        }
    }
    return biggest;
}
const bool WaveManager::ShouldWaveStart() const
{
    return mgr_tower->WasAnyTowerPlaced();
}
bool WaveManager::IsSkipAllowed()
{
    if (m_unactiveWaves.empty())
    {
        return false;
    }
    EnemyWave *currentWave = GetCurrentWave();
    if (!currentWave)
    {
        return false;
    }
    if (m_spawnTime >= currentWave->p_totalWaveTime / 2.0f)
    {
        return true;
    }
    return false;
}
void WaveManager::SkipWave()
{
    EnemyWave *currentWave = GetCurrentWave();
    EnemyWave *nextWave = GetNextWave();
    if (!currentWave || !nextWave)
    {
        return;
    }

    mgr_ps->AddMoney(currentWave->p_moneyReward);
    ActivateWave(nextWave);
}
void WaveManager::ClearActiveWaves()
{
    m_activeWaves.clear();
}
void WaveManager::ClearUnactiveWaves()
{
    m_unactiveWaves.clear();
}
void WaveManager::Update(const float deltaTime)
{
    UpdateUnactiveWaves();
    UpdateActiveWaves(deltaTime);
}
void WaveManager::InjectDependencies(EnemyManager *enemyManager, PSManager *psManager, TowerManager *towerManager, MessageManager *messageManager)
{
    mgr_enemy = enemyManager;
    mgr_ps = psManager;
    mgr_tower = towerManager;
    mgr_message = messageManager;
}
void WaveManager::Init()
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");
    assert(mgr_ps != nullptr && "psManager wasn't injected and its dependency");
    assert(mgr_tower != nullptr && "towerManager wasn't injected and its dependency");
    assert(mgr_message != nullptr && "messageManager wasn't injected and its dependency");

    LoadWaves();

    m_spawnTime = 0.0f;
    m_waveTime = 0.0f;
}
