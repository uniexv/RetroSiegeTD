#pragma once
#include "../enums/targetingtype.hpp"
#include <cstdint>
#include <functional>
#include <raylib.h>
enum class TowerType : uint8_t
{
    Nothing = 0,
    NinjaLv1 = 1,
    NinjaLv2 = 2,
    NinjaLv3 = 3,
    NinjaLv4 = 4,
    KnightLv1 = 5,
    KnightLv2 = 6,
    KnightLv3 = 7,
    KnightLv4 = 8,
    KnightLv5 = 9,
    MarketLv1 = 10,
    MarketLv2 = 11,
    MarketLv3 = 12,
    MarketLv4 = 13,
    SniperLv1 = 14,
    SniperLv2 = 15,
    SniperLv3 = 16,
    SniperLv4 = 17,
};
class ParticleManager;
class TowerManager;
class EnemyManager;
class ParticleManager;
class PsManager;
class Enemy;
class BulletManager;
class PSManager;
struct Tower
{
    std::function<void(
                       const float deltaTime,Tower* tower,
                       Enemy* enemy,EnemyManager* mgr_enemy,
                       BulletManager* mgr_bullet,TowerManager* mgr_tower,
                       PSManager* mgr_ps, ParticleManager* mgr_particle
                      )>
    p_fightFunction = [](const float deltaTime,Tower* tower,Enemy* enemy,EnemyManager* mgr_enemy,BulletManager* mgr_bullet,TowerManager* mgr_tower,PSManager* mgr_ps, ParticleManager* mgr_particle){};
    Texture2D p_texture = {0, 0, 0, 0, 0};
    Rectangle p_sourceRect = {0, 0, 0, 0};
    uint64_t p_price = 0; 
    int64_t p_damage = 1;  
    Vector2 p_position = {0,0};
    float p_range = 30;
    float p_attackSpeed = 1;
    float p_timeToAttack = 0;
    float p_timeToNextFrame = 0.0f;
    float p_timePassed = 0.0f;
    float p_stun = 0.0f;
    TowerType p_upgradesTo = TowerType::Nothing;
    int32_t p_id = -1;   
    uint16_t p_level = 0;
    uint16_t p_frameOffset = 0;
    uint16_t p_frameAmount = 0;
    TowerType p_typeId = TowerType(0);
    int16_t p_tileId = 0;
    TargetingType p_targetting = TargetingType::First;
    bool p_isUpgradeHovered = false;
    bool p_rangeless = false;
    bool p_dirty = true;
};
