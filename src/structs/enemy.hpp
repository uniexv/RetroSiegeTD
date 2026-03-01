#pragma once
#include <raylib.h>
#include <cstdint>
#include <iostream>
#include <vector>
#include <functional>
class EnemyManager;
class BulletManager;
enum class EnemyType : uint8_t
{
    BlueSlime = 1,
    RedSlime = 2,
    Zombie = 3,
    ArmoredZombie = 4,
    Skeleton = 5,
    Summoner = 6,
    QuickSlime = 7,
    ElectricSlime = 8,
    SmallSlime = 9,
    BigSlime = 10,
    SkeletonWarrior = 11,
    SkeletonGuardian = 12,
    SkeletonKing = 13
};
struct Enemy
{
    std::vector<std::pair<float, int32_t>> p_hitCooldowns = {};
    std::function<void(const float deltaTime,Enemy& enemy, EnemyManager* mgr_enemy, BulletManager* mgr_bullet)> p_updateFunction = [](const float deltaTime,Enemy& enemy, EnemyManager* mgr_enemy, BulletManager* mgr_bullet){};
    std::function<void(Enemy& enemy, EnemyManager* mgr_enemy)> p_deathCallback = [](Enemy& enemy, EnemyManager* mgr_enemy){};
    Texture2D p_texture = {0, 0, 0, 0, 0};
    Rectangle p_sourceRect = {0, 0, 0, 0};
    uint64_t p_moneyDrop = 0;
    int64_t p_health = 10;
    int64_t p_defense = 0;
    Vector2 p_position = {0, 0};
    uint32_t p_id = -1;
    float p_speed = 1;
    float p_timeToNextFrame = 0.0f;
    float p_timePassed = 0.0f;
    float p_timeToMove = 0.0f;
    float p_hitEffectTime = 0.0f;
    EnemyType p_typeId = EnemyType(0);
    uint16_t p_walked = 0;
    uint16_t p_frameOffset = 0;
    uint16_t p_frameAmount = 0;
    int16_t p_tileId = 0;
    bool p_isSummon = false;
    bool p_alive = true;
    bool p_survived = false;
    bool p_dirty = true;
    bool p_inSpecialAnim = false;
};
