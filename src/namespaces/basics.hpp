#include "../structs/tower.hpp"
#include "../structs/enemy.hpp"
#include "../structs/bullet.hpp"
class PSManager;


namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps);
    void UpdateFarmTower(Tower *tower, EnemyManager *mgr_enemy, TowerManager *mgr_tower, PSManager *mgr_ps, ParticleManager *mgr_particle);
    void Animate(const float deltaTime, Enemy &enemy);
    void Animate(const float deltaTime, Bullet &bullet);
    void Animate(const float deltaTime, Tower &tower);
    void PlayAnimation(const float deltaTime, Enemy& enemy, uint16_t startingFrame, uint16_t amountOfFrames);
};
