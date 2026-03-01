#include "basics.hpp"
#include "towers.hpp"
#include "settings.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/particlemanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../structs/particle.hpp"
#include <unordered_map>
#include <cassert>
namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps)
    {
        assert(tower->p_upgradesTo != TowerType::Nothing);
        if (tower->p_upgradesTo == TowerType::Nothing)
        {
            return;
        }

        Tower upgradedTower = Towers::GetTowerData(tower->p_upgradesTo);
        if (!tower)
        {
            return;
        }

        if (mgr_ps->CanAfford(upgradedTower.p_price))
        {
            mgr_ps->SubMoney(upgradedTower.p_price);
            upgradedTower.p_id = tower->p_id;
            upgradedTower.p_tileId = tower->p_tileId;
            upgradedTower.p_dirty = true;
            upgradedTower.p_targetting = tower->p_targetting;
            *tower = upgradedTower;
        }
    }
    void UpdateFarmTower(Tower *tower, EnemyManager *mgr_enemy, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle)
    {
        static std::unordered_map<int32_t, uint32_t> startingKillAmounts = {};
        if (!startingKillAmounts.contains(tower->p_id))
        {
            startingKillAmounts[tower->p_id] = mgr_enemy->GetKilledAmount();
        }

        uint32_t difference = mgr_enemy->GetKilledAmount() - startingKillAmounts[tower->p_id];
        if (difference != 0)
        {
            Vector2 pos = mgr_tower->GetCenterPosition(*tower);

            Particle particle = {};
            particle.p_text = std::to_string(difference * tower->p_damage) + "$";
            particle.p_drawRect = {0,0,0,0};
            particle.p_position = {pos.x + Settings::g_boundingSize, pos.y};
            particle.p_textPosition = {0, 0};
            particle.p_particleMoveType = ParticleMoveType::MoveUp;
            particle.p_color = DARKGREEN;
            particle.p_speed = 10.0f;
            particle.p_rotation = 0.0f;
            particle.p_transparency = 1.0f;
            particle.p_aliveTime = 3.0f;
            particle.p_startingTime = particle.p_aliveTime;
            mgr_particle->AddParticle(particle);
            

            mgr_ps->AddMoney(difference * tower->p_damage);
            startingKillAmounts[tower->p_id] = mgr_enemy->GetKilledAmount();
        }
    }
    void Animate(const float deltaTime, Enemy &enemy)
    {
        if (enemy.p_frameAmount == 0 || enemy.p_frameOffset == 0 || enemy.p_inSpecialAnim)
        {
            return;
        }

        enemy.p_timePassed += deltaTime;
        if (enemy.p_timePassed >= enemy.p_timeToNextFrame)
        {
            enemy.p_timePassed -= enemy.p_timeToNextFrame;
            if (enemy.p_sourceRect.x + enemy.p_frameOffset >= enemy.p_frameOffset * enemy.p_frameAmount)
            {
                enemy.p_sourceRect = {0, 0, static_cast<float>(enemy.p_frameOffset), enemy.p_sourceRect.height};
            }
            else
            {
                enemy.p_sourceRect.x += enemy.p_frameOffset;
            }
        }
    };

    void Animate(const float deltaTime, Bullet &bullet)
    {
        if (bullet.p_frameAmount == 0 || bullet.p_frameOffset == 0)
        {
            return;
        }

        bullet.p_timePassed += deltaTime;
        if (bullet.p_timePassed >= bullet.p_timeToNextFrame)
        {
            bullet.p_timePassed -= bullet.p_timeToNextFrame;
            if (bullet.p_sourceRect.x + bullet.p_frameOffset >= bullet.p_frameOffset * bullet.p_frameAmount)
            {
                if (bullet.p_removeAfterAnimation)
                {
                    bullet.p_alive = false;
                    return;
                }

                bullet.p_sourceRect = {0, 0, static_cast<float>(bullet.p_frameOffset), bullet.p_sourceRect.height};
            }
            else
            {
                bullet.p_sourceRect.x += bullet.p_frameOffset;
            }
        }
    }

    void Animate(const float deltaTime, Tower &tower)
    {
        if (tower.p_frameAmount == 0 || tower.p_frameOffset == 0)
        {
            return;
        }

        tower.p_timePassed += deltaTime;
        if (tower.p_timePassed >= tower.p_timeToNextFrame)
        {
            tower.p_timePassed -= tower.p_timeToNextFrame;
            if (tower.p_sourceRect.x + tower.p_frameOffset >= tower.p_frameOffset * tower.p_frameAmount)
            {
                tower.p_sourceRect = {0, 0, static_cast<float>(tower.p_frameOffset), tower.p_sourceRect.height};
            }
            else
            {
                tower.p_sourceRect.x += tower.p_frameOffset;
            }
        }
    }

    void PlayAnimation(const float deltaTime, Enemy &enemy, uint16_t startingFrame, uint16_t amountOfFrames)
    {
        enemy.p_inSpecialAnim = true;

        enemy.p_timePassed += deltaTime;

        if (enemy.p_timePassed >= enemy.p_timeToNextFrame)
        {
            enemy.p_timePassed -= enemy.p_timeToNextFrame;
            if (enemy.p_sourceRect.x + enemy.p_frameOffset >= enemy.p_frameOffset * (amountOfFrames + startingFrame))
            {
                enemy.p_sourceRect = {0, 0, static_cast<float>(enemy.p_frameOffset), enemy.p_sourceRect.height};
                enemy.p_inSpecialAnim = false;
            }
            else if(enemy.p_sourceRect.x < enemy.p_frameOffset*startingFrame)
            {
                enemy.p_sourceRect.x = enemy.p_frameOffset*startingFrame;
            }
            else
            {
                enemy.p_sourceRect.x += enemy.p_frameOffset;
            }
        }
    }
};
