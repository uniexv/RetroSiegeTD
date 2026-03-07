#include "towers.hpp"
#include "bullets.hpp"
#include "basics.hpp"
#include "sprites.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/mathutil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/particlemanager.hpp"
#include <unordered_map>
#include <cassert>
#include <cmath>

namespace Towers
{
    std::unordered_map<TowerType, Tower> g_towerData = {};
    std::unordered_map<TowerType, uint16_t> g_towerAmountLimits = {
        {TowerType::MarketLv1,6},
        {TowerType::SniperLv1,1}
    };

    void InitTowerData()
    {
        g_towerData.clear();

#pragma region NinjaLv1
        Tower ninja1Tower = {};
        ninja1Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja1Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::NinjaTower1];
        ninja1Tower.p_sourceRect = {0, 0, 15, 15};
        ninja1Tower.p_price = 50;
        ninja1Tower.p_damage = 1;
        ninja1Tower.p_position = {-1.0f, -1.0f};
        ninja1Tower.p_range = 70.0f;
        ninja1Tower.p_attackSpeed = 0.70f;
        ninja1Tower.p_timeToAttack = 0.0f;
        ninja1Tower.p_timeToNextFrame = 0.0f;
        ninja1Tower.p_timePassed = 0.0f;
        ninja1Tower.p_upgradesTo = TowerType::NinjaLv2;
        ninja1Tower.p_id = -1;
        ninja1Tower.p_level = 1;
        ninja1Tower.p_frameOffset = 0;
        ninja1Tower.p_frameAmount = 0;
        ninja1Tower.p_typeId = TowerType::NinjaLv1;
        ninja1Tower.p_tileId = 0;
        ninja1Tower.p_isUpgradeHovered = false;
        ninja1Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv1] = ninja1Tower;
#pragma endregion

#pragma region NinjaLv2
        Tower ninja2Tower = {};
        ninja2Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja2Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::NinjaTower2];
        ninja2Tower.p_sourceRect = {0, 0, 15, 15};
        ninja2Tower.p_price = 125;
        ninja2Tower.p_damage = 2;
        ninja2Tower.p_position = {-1.0f, -1.0f};
        ninja2Tower.p_range = 70.0f;
        ninja2Tower.p_attackSpeed = 0.70f;
        ninja2Tower.p_timeToAttack = 0.0f;
        ninja2Tower.p_timeToNextFrame = 0.0f;
        ninja2Tower.p_timePassed = 0.0f;
        ninja2Tower.p_upgradesTo = TowerType::NinjaLv3;
        ninja2Tower.p_id = -1;
        ninja2Tower.p_level = 2;
        ninja2Tower.p_frameOffset = 0;
        ninja2Tower.p_frameAmount = 0;
        ninja2Tower.p_typeId = TowerType::NinjaLv2;
        ninja2Tower.p_tileId = 0;
        ninja2Tower.p_isUpgradeHovered = false;
        ninja2Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv2] = ninja2Tower;
#pragma endregion

#pragma region NinjaLv3
        Tower ninja3Tower = {};
        ninja3Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SharpShuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja3Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::NinjaTower3];
        ninja3Tower.p_sourceRect = {0, 0, 15, 15};
        ninja3Tower.p_price = 500;
        ninja3Tower.p_damage = 2;
        ninja3Tower.p_position = {-1.0f, -1.0f};
        ninja3Tower.p_range = 70.0f;
        ninja3Tower.p_attackSpeed = 0.65f;
        ninja3Tower.p_timeToAttack = 0.0f;
        ninja3Tower.p_timeToNextFrame = 0.0f;
        ninja3Tower.p_timePassed = 0.0f;
        ninja3Tower.p_upgradesTo = TowerType::NinjaLv4;
        ninja3Tower.p_id = -1;
        ninja3Tower.p_level = 3;
        ninja3Tower.p_frameOffset = 0;
        ninja3Tower.p_frameAmount = 0;
        ninja3Tower.p_typeId = TowerType::NinjaLv3;
        ninja3Tower.p_tileId = 0;
        ninja3Tower.p_isUpgradeHovered = false;
        ninja3Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv3] = ninja3Tower;
#pragma endregion

#pragma region NinjaLv4
        Tower ninja4Tower = {};
        ninja4Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::NinjaTower4];
        ninja4Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Dagger);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja4Tower.p_sourceRect = {0, 0, 15, 15};
        ninja4Tower.p_price = 1250;
        ninja4Tower.p_damage = 5;
        ninja4Tower.p_position = {-1.0f, -1.0f};
        ninja4Tower.p_range = 80.0f;
        ninja4Tower.p_attackSpeed = 0.50f;
        ninja4Tower.p_timeToAttack = 0.0f;
        ninja4Tower.p_timeToNextFrame = 0.0f;
        ninja4Tower.p_timePassed = 0.0f;
        ninja4Tower.p_upgradesTo = TowerType::Nothing;
        ninja4Tower.p_id = -1;
        ninja4Tower.p_level = 4;
        ninja4Tower.p_frameOffset = 0;
        ninja4Tower.p_frameAmount = 0;
        ninja4Tower.p_typeId = TowerType::NinjaLv4;
        ninja4Tower.p_tileId = 0;
        ninja4Tower.p_isUpgradeHovered = false;
        ninja4Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv4] = ninja4Tower;
#pragma endregion

#pragma region KnightLv1
        Tower knight1Tower = {};
        knight1Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::KnightTower1];
        knight1Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Slash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight1Tower.p_sourceRect = {0, 0, 15, 15};
        knight1Tower.p_price = 120;
        knight1Tower.p_damage = 4;
        knight1Tower.p_position = {-1.0f, -1.0f};
        knight1Tower.p_range = 25.0f;
        knight1Tower.p_attackSpeed = 2.0f;
        knight1Tower.p_timeToAttack = 0.0f;
        knight1Tower.p_timeToNextFrame = 0.0f;
        knight1Tower.p_timePassed = 0.0f;
        knight1Tower.p_upgradesTo = TowerType::KnightLv2;
        knight1Tower.p_id = -1;
        knight1Tower.p_level = 1;
        knight1Tower.p_frameOffset = 0;
        knight1Tower.p_frameAmount = 0;
        knight1Tower.p_typeId = TowerType::KnightLv1;
        knight1Tower.p_tileId = 0;
        knight1Tower.p_isUpgradeHovered = false;
        knight1Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv1] = knight1Tower;
#pragma endregion

#pragma region KnightLv2
        Tower knight2Tower = {};
        knight2Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::KnightTower2];
        knight2Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Slash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight2Tower.p_sourceRect = {0, 0, 15, 15};
        knight2Tower.p_price = 200;
        knight2Tower.p_damage = 6;
        knight2Tower.p_position = {-1.0f, -1.0f};
        knight2Tower.p_range = 30.0f;
        knight2Tower.p_attackSpeed = 1.5f;
        knight2Tower.p_timeToAttack = 0.0f;
        knight2Tower.p_timeToNextFrame = 0.0f;
        knight2Tower.p_timePassed = 0.0f;
        knight2Tower.p_upgradesTo = TowerType::KnightLv3;
        knight2Tower.p_id = -1;
        knight2Tower.p_level = 2;
        knight2Tower.p_frameOffset = 0;
        knight2Tower.p_frameAmount = 0;
        knight2Tower.p_typeId = TowerType::KnightLv2;
        knight2Tower.p_tileId = 0;
        knight2Tower.p_isUpgradeHovered = false;
        knight2Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv2] = knight2Tower;
#pragma endregion

#pragma region KnightLv3
        Tower knight3Tower = {};
        knight3Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::KnightTower3];
        knight3Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BigSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight3Tower.p_sourceRect = {0, 0, 15, 15};
        knight3Tower.p_price = 500;
        knight3Tower.p_damage = 10;
        knight3Tower.p_position = {-1.0f, -1.0f};
        knight3Tower.p_range = 30.0f;
        knight3Tower.p_attackSpeed = 1.5f;
        knight3Tower.p_timeToAttack = 0.0f;
        knight3Tower.p_timeToNextFrame = 0.0f;
        knight3Tower.p_timePassed = 0.0f;
        knight3Tower.p_upgradesTo = TowerType::KnightLv4;
        knight3Tower.p_id = -1;
        knight3Tower.p_level = 3;
        knight3Tower.p_frameOffset = 0;
        knight3Tower.p_frameAmount = 0;
        knight3Tower.p_typeId = TowerType::KnightLv3;
        knight3Tower.p_tileId = 0;
        knight3Tower.p_isUpgradeHovered = false;
        knight3Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv3] = knight3Tower;
#pragma endregion

#pragma region KnightLv4
        Tower knight4Tower = {};
        knight4Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::KnightTower4];
        knight4Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BigSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight4Tower.p_sourceRect = {0, 0, 15, 15};
        knight4Tower.p_price = 750;
        knight4Tower.p_damage = 16;
        knight4Tower.p_position = {-1.0f, -1.0f};
        knight4Tower.p_range = 30.0f;
        knight4Tower.p_attackSpeed = 1.5f;
        knight4Tower.p_timeToAttack = 0.0f;
        knight4Tower.p_timeToNextFrame = 0.0f;
        knight4Tower.p_timePassed = 0.0f;
        knight4Tower.p_upgradesTo = TowerType::KnightLv5;
        knight4Tower.p_id = -1;
        knight4Tower.p_level = 4;
        knight4Tower.p_frameOffset = 0;
        knight4Tower.p_frameAmount = 0;
        knight4Tower.p_typeId = TowerType::KnightLv4;
        knight4Tower.p_tileId = 0;
        knight4Tower.p_isUpgradeHovered = false;
        knight4Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv4] = knight4Tower;
#pragma endregion

#pragma region KnightLv5
        Tower knight5Tower = {};
        knight5Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::KnightTower5];
        knight5Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BiggestSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight5Tower.p_sourceRect = {0, 0, 15, 15};
        knight5Tower.p_price = 1150;
        knight5Tower.p_damage = 24;
        knight5Tower.p_position = {-1.0f, -1.0f};
        knight5Tower.p_range = 30.0f;
        knight5Tower.p_attackSpeed = 1.5f;
        knight5Tower.p_timeToAttack = .0f;
        knight5Tower.p_timeToNextFrame = 0.0f;
        knight5Tower.p_timePassed = 0.0f;
        knight5Tower.p_upgradesTo = TowerType::Nothing;
        knight5Tower.p_id = -1;
        knight5Tower.p_level = 5;
        knight5Tower.p_frameOffset = 0;
        knight5Tower.p_frameAmount = 0;
        knight5Tower.p_typeId = TowerType::KnightLv5;
        knight5Tower.p_tileId = 0;
        knight5Tower.p_isUpgradeHovered = false;
        knight5Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv5] = knight5Tower;
#pragma endregion

#pragma region MarketLv1
        Tower market1Tower = {};
        market1Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::MarketTower1];
        market1Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Basics::UpdateFarmTower(tower, mgr_enemy, mgr_tower, mgr_ps, mgr_particle);
        };
        market1Tower.p_sourceRect = {0, 0, 15, 15};
        market1Tower.p_price = 100;
        market1Tower.p_damage = 3;
        market1Tower.p_position = {-1.0f, -1.0f};
        market1Tower.p_range = 5.0f;
        market1Tower.p_attackSpeed = 3.0f;
        market1Tower.p_timeToAttack = 0.0f;
        market1Tower.p_timeToNextFrame = 0.0f;
        market1Tower.p_timePassed = 0.0f;
        market1Tower.p_upgradesTo = TowerType::MarketLv2;
        market1Tower.p_id = -1;
        market1Tower.p_level = 1;
        market1Tower.p_frameOffset = 0;
        market1Tower.p_frameAmount = 0;
        market1Tower.p_typeId = TowerType::MarketLv1;
        market1Tower.p_tileId = 0;
        market1Tower.p_isUpgradeHovered = false;
        market1Tower.p_rangeless = true;
        market1Tower.p_dirty = true;

        g_towerData[TowerType::MarketLv1] = market1Tower;
#pragma endregion

#pragma region MarketLv2
        Tower market2Tower = {};
        market2Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::MarketTower2];
        market2Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Basics::UpdateFarmTower(tower, mgr_enemy, mgr_tower, mgr_ps, mgr_particle);
        };
        market2Tower.p_sourceRect = {0, 0, 15, 15};
        market2Tower.p_price = 250;
        market2Tower.p_damage = 8;
        market2Tower.p_position = {-1.0f, -1.0f};
        market2Tower.p_range = 5.0f;
        market2Tower.p_attackSpeed = 3.0f;
        market2Tower.p_timeToAttack = 0.0f;
        market2Tower.p_timeToNextFrame = 0.0f;
        market2Tower.p_timePassed = 0.0f;
        market2Tower.p_upgradesTo = TowerType::MarketLv3;
        market2Tower.p_id = -1;
        market2Tower.p_level = 2;
        market2Tower.p_frameOffset = 0;
        market2Tower.p_frameAmount = 0;
        market2Tower.p_typeId = TowerType::MarketLv2;
        market2Tower.p_tileId = 0;
        market2Tower.p_isUpgradeHovered = false;
        market2Tower.p_rangeless = true;
        market2Tower.p_dirty = true;

        g_towerData[TowerType::MarketLv2] = market2Tower;
#pragma endregion

#pragma region MarketLv3
        Tower market3Tower = {};
        market3Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::MarketTower3];
        market3Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Basics::UpdateFarmTower(tower, mgr_enemy, mgr_tower, mgr_ps, mgr_particle);
        };
        market3Tower.p_sourceRect = {0, 0, 15, 15};
        market3Tower.p_price = 1250;
        market3Tower.p_damage = 20;
        market3Tower.p_position = {-1.0f, -1.0f};
        market3Tower.p_range = 5.0f;
        market3Tower.p_attackSpeed = 3.0f;
        market3Tower.p_timeToAttack = 0.0f;
        market3Tower.p_timeToNextFrame = 0.0f;
        market3Tower.p_timePassed = 0.0f;
        market3Tower.p_upgradesTo = TowerType::MarketLv4;
        market3Tower.p_id = -1;
        market3Tower.p_level = 3;
        market3Tower.p_frameOffset = 0;
        market3Tower.p_frameAmount = 0;
        market3Tower.p_typeId = TowerType::MarketLv3;
        market3Tower.p_tileId = 0;
        market3Tower.p_isUpgradeHovered = false;
        market3Tower.p_rangeless = true;
        market3Tower.p_dirty = true;

        g_towerData[TowerType::MarketLv3] = market3Tower;
#pragma endregion

#pragma region MarketLv4
        Tower market4Tower = {};
        market4Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::MarketTower4];
        market4Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Basics::UpdateFarmTower(tower, mgr_enemy, mgr_tower, mgr_ps, mgr_particle);
        };
        market4Tower.p_sourceRect = {0, 0, 15, 15};
        market4Tower.p_price = 5000;
        market4Tower.p_damage = 50;
        market4Tower.p_position = {-1.0f, -1.0f};
        market4Tower.p_range = 5.0f;
        market4Tower.p_attackSpeed = 3.0f;
        market4Tower.p_timeToAttack = 0.0f;
        market4Tower.p_timeToNextFrame = 0.0f;
        market4Tower.p_timePassed = 0.0f;
        market4Tower.p_upgradesTo = TowerType::Nothing;
        market4Tower.p_id = -1;
        market4Tower.p_level = 4;
        market4Tower.p_frameOffset = 0;
        market4Tower.p_frameAmount = 0;
        market4Tower.p_typeId = TowerType::MarketLv4;
        market4Tower.p_tileId = 0;
        market4Tower.p_isUpgradeHovered = false;
        market4Tower.p_rangeless = true;
        market4Tower.p_dirty = true;

        g_towerData[TowerType::MarketLv4] = market4Tower;
#pragma endregion

#pragma region SniperLv1
        Tower sniper1Tower = {};
        sniper1Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::SniperTower1];
        sniper1Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SniperBullet);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        sniper1Tower.p_sourceRect = {0, 0, 15, 15};
        sniper1Tower.p_price = 900;
        sniper1Tower.p_damage = 14;
        sniper1Tower.p_position = {-1.0f, -1.0f};
        sniper1Tower.p_range = 110.0f;
        sniper1Tower.p_attackSpeed = 3.0f;
        sniper1Tower.p_timeToAttack = 0.0f;
        sniper1Tower.p_timeToNextFrame = 0.0f;
        sniper1Tower.p_timePassed = 0.0f;
        sniper1Tower.p_upgradesTo = TowerType::SniperLv2;
        sniper1Tower.p_id = -1;
        sniper1Tower.p_level = 1;
        sniper1Tower.p_frameOffset = 0;
        sniper1Tower.p_frameAmount = 0;
        sniper1Tower.p_typeId = TowerType::SniperLv1;
        sniper1Tower.p_tileId = 0;
        sniper1Tower.p_isUpgradeHovered = false;
        sniper1Tower.p_dirty = true;

        g_towerData[TowerType::SniperLv1] = sniper1Tower;
#pragma endregion

#pragma region SniperLv2
        Tower sniper2Tower = {};
        sniper2Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::SniperTower2];
        sniper2Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SniperBullet);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        sniper2Tower.p_sourceRect = {0, 0, 15, 15};
        sniper2Tower.p_price = 2200;
        sniper2Tower.p_damage = 34;
        sniper2Tower.p_position = {-1.0f, -1.0f};
        sniper2Tower.p_range = 110.0f;
        sniper2Tower.p_attackSpeed = 2.9f;
        sniper2Tower.p_timeToAttack = 0.0f;
        sniper2Tower.p_timeToNextFrame = 0.0f;
        sniper2Tower.p_timePassed = 0.0f;
        sniper2Tower.p_upgradesTo = TowerType::SniperLv3;
        sniper2Tower.p_id = -1;
        sniper2Tower.p_level = 2;
        sniper2Tower.p_frameOffset = 0;
        sniper2Tower.p_frameAmount = 0;
        sniper2Tower.p_typeId = TowerType::SniperLv2;
        sniper2Tower.p_tileId = 0;
        sniper2Tower.p_isUpgradeHovered = false;
        sniper2Tower.p_dirty = true;

        g_towerData[TowerType::SniperLv2] = sniper2Tower;
#pragma endregion

#pragma region SniperLv3
        Tower sniper3Tower = {};
        sniper3Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::SniperTower3];
        sniper3Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SniperBullet);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        sniper3Tower.p_sourceRect = {0, 0, 15, 15};
        sniper3Tower.p_price = 3650;
        sniper3Tower.p_damage = 60;
        sniper3Tower.p_position = {-1.0f, -1.0f};
        sniper3Tower.p_range = 110.0f;
        sniper3Tower.p_attackSpeed = 2.8f;
        sniper3Tower.p_timeToAttack = 0.0f;
        sniper3Tower.p_timeToNextFrame = 0.0f;
        sniper3Tower.p_timePassed = 0.0f;
        sniper3Tower.p_upgradesTo = TowerType::SniperLv4;
        sniper3Tower.p_id = -1;
        sniper3Tower.p_level = 3;
        sniper3Tower.p_frameOffset = 0;
        sniper3Tower.p_frameAmount = 0;
        sniper3Tower.p_typeId = TowerType::SniperLv3;
        sniper3Tower.p_tileId = 0;
        sniper3Tower.p_isUpgradeHovered = false;
        sniper3Tower.p_dirty = true;

        g_towerData[TowerType::SniperLv3] = sniper3Tower;
#pragma endregion

#pragma region SniperLv4
        Tower sniper4Tower = {};
        sniper4Tower.p_texture = Sprites::g_textures[Sprites::TextureIndex::SniperTower4];
        sniper4Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SniperBullet);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = Math::RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        sniper4Tower.p_sourceRect = {0, 0, 15, 15};
        sniper4Tower.p_price = 5850;
        sniper4Tower.p_damage = 80;
        sniper4Tower.p_position = {-1.0f, -1.0f};
        sniper4Tower.p_range = 110.0f;
        sniper4Tower.p_attackSpeed = 2.7f;
        sniper4Tower.p_timeToAttack = 0.0f;
        sniper4Tower.p_timeToNextFrame = 0.0f;
        sniper4Tower.p_timePassed = 0.0f;
        sniper4Tower.p_upgradesTo = TowerType::Nothing;
        sniper4Tower.p_id = -1;
        sniper4Tower.p_level = 4;
        sniper4Tower.p_frameOffset = 0;
        sniper4Tower.p_frameAmount = 0;
        sniper4Tower.p_typeId = TowerType::SniperLv4;
        sniper4Tower.p_tileId = 0;
        sniper4Tower.p_isUpgradeHovered = false;
        sniper4Tower.p_dirty = true;

        g_towerData[TowerType::SniperLv4] = sniper4Tower;
#pragma endregion

    }

    Tower GetTowerData(TowerType typeId)
    {
        auto it = g_towerData.find(typeId);
        if (it != g_towerData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in towerData");
        return Tower{};
    }

    uint16_t GetTowerLimit(TowerType typeId)
    {
        auto it = g_towerAmountLimits.find(typeId);
        if (it != g_towerAmountLimits.end())
        {
            return it->second;
        }
        return 0;
    }
}