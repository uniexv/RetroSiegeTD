#pragma once
#include "enemy.hpp"
#include <cstdint>
#include <utility>

struct EnemyWave {
    std::vector<std::pair<float, EnemyType>> p_enemySpawns = {};
    uint64_t p_moneyReward = 0;
    float p_totalWaveTime = 0.0f;
    uint32_t p_id = 0;
};
