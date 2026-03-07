#include "enemies.hpp"
#include "basics.hpp"
#include "bullets.hpp"
#include "sprites.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../utility/debugutil.hpp"
#include <cassert>

namespace Enemies
{
    std::unordered_map<EnemyType, Enemy> g_enemyData = {};

    void InitEnemyData()
    {
        g_enemyData.clear();

#pragma region BlueSlime
        Enemy blueSlime = {};
        blueSlime.p_hitCooldowns = {};
        blueSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        blueSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        blueSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::BlueSlimeEnemy];
        blueSlime.p_sourceRect = {0, 0, 15, 15};
        blueSlime.p_moneyDrop = 10;
        blueSlime.p_health = 6;
        blueSlime.p_defense = 0;
        blueSlime.p_position = {-1.0f, -1.0f};
        blueSlime.p_id = 0;
        blueSlime.p_speed = 1.5f;
        blueSlime.p_timeToNextFrame = 1.0f;
        blueSlime.p_timePassed = 0.0f;
        blueSlime.p_timeToMove = 0.0f;
        blueSlime.p_hitEffectTime = 0.0f;
        blueSlime.p_typeId = EnemyType::BlueSlime;
        blueSlime.p_walked = 0;
        blueSlime.p_tileId = -1;
        blueSlime.p_frameOffset = 15;
        blueSlime.p_frameAmount = 2;
        blueSlime.p_alive = true;
        blueSlime.p_survived = false;
        blueSlime.p_dirty = true;

        g_enemyData[EnemyType::BlueSlime] = blueSlime;
#pragma endregion

#pragma region RedSlime
        Enemy redSlime = {};
        redSlime.p_hitCooldowns = {};
        redSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        redSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        redSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::RedSlimeEnemy];
        redSlime.p_sourceRect = {0, 0, 15, 15};
        redSlime.p_moneyDrop = 20;
        redSlime.p_health = 25;
        redSlime.p_defense = 1;
        redSlime.p_position = {-1.0f, -1.0f};
        redSlime.p_id = 0;
        redSlime.p_speed = 2.0f;
        redSlime.p_timeToNextFrame = 1.0f;
        redSlime.p_timePassed = 0.0f;
        redSlime.p_timeToMove = 0.0f;
        redSlime.p_hitEffectTime = 0.0f;
        redSlime.p_typeId = EnemyType::RedSlime;
        redSlime.p_walked = 0;
        redSlime.p_tileId = -1;
        redSlime.p_frameOffset = 15;
        redSlime.p_frameAmount = 2;
        redSlime.p_alive = true;
        redSlime.p_survived = false;
        redSlime.p_dirty = true;

        g_enemyData[EnemyType::RedSlime] = redSlime;
#pragma endregion

#pragma region Zombie
        Enemy zombie = {};
        zombie.p_hitCooldowns = {};
        zombie.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        zombie.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        zombie.p_texture = Sprites::g_textures[Sprites::TextureIndex::ZombieEnemy];
        zombie.p_sourceRect = {0, 0, 15, 15};
        zombie.p_moneyDrop = 25;
        zombie.p_health = 80;
        zombie.p_defense = 0;
        zombie.p_position = {-1.0f, -1.0f};
        zombie.p_id = 0;
        zombie.p_speed = 1.5f;
        zombie.p_timeToNextFrame = 0.5f;
        zombie.p_timePassed = 0.0f;
        zombie.p_timeToMove = 0.0f;
        zombie.p_hitEffectTime = 0.0f;
        zombie.p_typeId = EnemyType::Zombie;
        zombie.p_walked = 0;
        zombie.p_tileId = -1;
        zombie.p_frameOffset = 15;
        zombie.p_frameAmount = 2;
        zombie.p_alive = true;
        zombie.p_survived = false;
        zombie.p_dirty = true;

        g_enemyData[EnemyType::Zombie] = zombie;
#pragma endregion

#pragma region ArmoredZombie
        Enemy armoredZombie = {};
        armoredZombie.p_hitCooldowns = {};
        armoredZombie.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        armoredZombie.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        armoredZombie.p_texture = Sprites::g_textures[Sprites::TextureIndex::ArmoredZombieEnemy];
        armoredZombie.p_sourceRect = {0, 0, 15, 15};
        armoredZombie.p_moneyDrop = 35;
        armoredZombie.p_health = 100;
        armoredZombie.p_defense = 7;
        armoredZombie.p_position = {-1.0f, -1.0f};
        armoredZombie.p_id = 0;
        armoredZombie.p_speed = 1.75f;
        armoredZombie.p_timeToNextFrame = 0.5f;
        armoredZombie.p_timePassed = 0.0f;
        armoredZombie.p_timeToMove = 0.0f;
        armoredZombie.p_hitEffectTime = 0.0f;
        armoredZombie.p_typeId = EnemyType::ArmoredZombie;
        armoredZombie.p_walked = 0;
        armoredZombie.p_tileId = -1;
        armoredZombie.p_frameOffset = 15;
        armoredZombie.p_frameAmount = 2;
        armoredZombie.p_alive = true;
        armoredZombie.p_survived = false;
        armoredZombie.p_dirty = true;

        g_enemyData[EnemyType::ArmoredZombie] = armoredZombie;
#pragma endregion

#pragma region Skeleton
        Enemy skeleton = {};
        skeleton.p_hitCooldowns = {};
        skeleton.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        skeleton.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        skeleton.p_texture = Sprites::g_textures[Sprites::TextureIndex::SkeletonEnemy];
        skeleton.p_sourceRect = {0, 0, 15, 15};
        skeleton.p_moneyDrop = 25;
        skeleton.p_health = 65;
        skeleton.p_defense = 0;
        skeleton.p_position = {-1.0f, -1.0f};
        skeleton.p_id = 0;
        skeleton.p_speed = 0.5f;
        skeleton.p_timeToNextFrame = 0.25f;
        skeleton.p_timePassed = 0.0f;
        skeleton.p_timeToMove = 0.0f;
        skeleton.p_hitEffectTime = 0.0f;
        skeleton.p_typeId = EnemyType::Skeleton;
        skeleton.p_walked = 0;
        skeleton.p_tileId = -1;
        skeleton.p_frameOffset = 15;
        skeleton.p_frameAmount = 2;
        skeleton.p_alive = true;
        skeleton.p_survived = false;
        skeleton.p_dirty = true;

        g_enemyData[EnemyType::Skeleton] = skeleton;
#pragma endregion

#pragma region Summoner
        Enemy summoner = {};
        summoner.p_hitCooldowns = {};
        summoner.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet)
        {
            constexpr float spawnCooldown = 2.5f;
            static float time = 0.0f;
            time += deltaTime;
            if (time >= spawnCooldown)
            {
                Basics::PlayAnimation(deltaTime, enemy, 3, 8);
                if (enemy.p_inSpecialAnim)
                {
                    return;
                }

                time = 0.0f;

                Enemy summon = GetEnemyData(EnemyType::Skeleton);
                summon.p_isSummon = true;
                summon.p_id = mgr_enemy->GetNewValidId();
                summon.p_tileId = enemy.p_tileId;
                summon.p_walked = enemy.p_walked;
                mgr_enemy->AddEnemy(summon);
            }
        };
        summoner.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        summoner.p_texture = Sprites::g_textures[Sprites::TextureIndex::SummonerEnemy];
        summoner.p_sourceRect = {0, 0, 15, 15};
        summoner.p_moneyDrop = 200;
        summoner.p_health = 250;
        summoner.p_defense = 3;
        summoner.p_position = {-1.0f, -1.0f};
        summoner.p_id = 0;
        summoner.p_speed = 2.0f;
        summoner.p_timeToNextFrame = 0.25f;
        summoner.p_timePassed = 0.0f;
        summoner.p_timeToMove = 0.0f;
        summoner.p_hitEffectTime = 0.0f;
        summoner.p_typeId = EnemyType::Summoner;
        summoner.p_walked = 0;
        summoner.p_tileId = -1;
        summoner.p_frameOffset = 15;
        summoner.p_frameAmount = 2;
        summoner.p_alive = true;
        summoner.p_survived = false;
        summoner.p_dirty = true;

        g_enemyData[EnemyType::Summoner] = summoner;
#pragma endregion

#pragma region QuickSlime
        Enemy quickSlime = {};
        quickSlime.p_hitCooldowns = {};
        quickSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        quickSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        quickSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::QuickSlimeEnemy];
        quickSlime.p_sourceRect = {0, 0, 15, 15};
        quickSlime.p_moneyDrop = 15;
        quickSlime.p_health = 5;
        quickSlime.p_defense = 0;
        quickSlime.p_position = {-1.0f, -1.0f};
        quickSlime.p_id = 0;
        quickSlime.p_speed = 0.7f;
        quickSlime.p_timeToNextFrame = 0.35f;
        quickSlime.p_timePassed = 0.0f;
        quickSlime.p_timeToMove = 0.0f;
        quickSlime.p_hitEffectTime = 0.0f;
        quickSlime.p_typeId = EnemyType::QuickSlime;
        quickSlime.p_walked = 0;
        quickSlime.p_tileId = -1;
        quickSlime.p_frameOffset = 15;
        quickSlime.p_frameAmount = 2;
        quickSlime.p_alive = true;
        quickSlime.p_survived = false;
        quickSlime.p_dirty = true;

        g_enemyData[EnemyType::QuickSlime] = quickSlime;
#pragma endregion

#pragma region ElectricSlime
        Enemy electricSlime = {};
        electricSlime.p_hitCooldowns = {};
        electricSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        electricSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        electricSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::ElectricSlimeEnemy];
        electricSlime.p_sourceRect = {0, 0, 15, 15};
        electricSlime.p_moneyDrop = 35;
        electricSlime.p_health = 34;
        electricSlime.p_defense = 1;
        electricSlime.p_position = {-1.0f, -1.0f};
        electricSlime.p_id = 0;
        electricSlime.p_speed = 0.35f;
        electricSlime.p_timeToNextFrame = 0.15f;
        electricSlime.p_timePassed = 0.0f;
        electricSlime.p_timeToMove = 0.0f;
        electricSlime.p_hitEffectTime = 0.0f;
        electricSlime.p_typeId = EnemyType::ElectricSlime;
        electricSlime.p_walked = 0;
        electricSlime.p_tileId = -1;
        electricSlime.p_frameOffset = 15;
        electricSlime.p_frameAmount = 2;
        electricSlime.p_alive = true;
        electricSlime.p_survived = false;
        electricSlime.p_dirty = true;

        g_enemyData[EnemyType::ElectricSlime] = electricSlime;
#pragma endregion

#pragma region SmallSlime
        Enemy smallSlime = {};
        smallSlime.p_hitCooldowns = {};
        smallSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        smallSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        smallSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::SmallSlimeEnemy];
        smallSlime.p_sourceRect = {0, 0, 15, 15};
        smallSlime.p_moneyDrop = 5;
        smallSlime.p_health = 20;
        smallSlime.p_defense = 1;
        smallSlime.p_position = {-1.0f, -1.0f};
        smallSlime.p_id = 0;
        smallSlime.p_speed = 1.0f;
        smallSlime.p_timeToNextFrame = 0.5f;
        smallSlime.p_timePassed = 0.0f;
        smallSlime.p_timeToMove = 0.0f;
        smallSlime.p_hitEffectTime = 0.0f;
        smallSlime.p_typeId = EnemyType::SmallSlime;
        smallSlime.p_walked = 0;
        smallSlime.p_tileId = -1;
        smallSlime.p_frameOffset = 15;
        smallSlime.p_frameAmount = 2;
        smallSlime.p_alive = true;
        smallSlime.p_survived = false;
        smallSlime.p_dirty = true;

        g_enemyData[EnemyType::SmallSlime] = smallSlime;
#pragma endregion

#pragma region BigSlime
        Enemy bigSlime = {};
        bigSlime.p_hitCooldowns = {};
        bigSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        bigSlime.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy)
        {
            for (int i = 0; i < 5; i++)
            {
                Enemy smallSlime = Enemies::GetEnemyData(EnemyType::SmallSlime);
                smallSlime.p_speed *= 1.0f + i / 4.0f;
                smallSlime.p_id = mgr_enemy->GetNewValidId();
                smallSlime.p_walked = enemy.p_walked;
                smallSlime.p_tileId = enemy.p_tileId;
                mgr_enemy->AddEnemy(smallSlime);
            }
        };
        bigSlime.p_texture = Sprites::g_textures[Sprites::TextureIndex::BigSlimeEnemy];
        bigSlime.p_sourceRect = {0, 0, 15, 15};
        bigSlime.p_moneyDrop = 35;
        bigSlime.p_health = 125;
        bigSlime.p_defense = 3;
        bigSlime.p_position = {-1.0f, -1.0f};
        bigSlime.p_id = 0;
        bigSlime.p_speed = 3.0f;
        bigSlime.p_timeToNextFrame = 1.5f;
        bigSlime.p_timePassed = 0.0f;
        bigSlime.p_timeToMove = 0.0f;
        bigSlime.p_hitEffectTime = 0.0f;
        bigSlime.p_typeId = EnemyType::BigSlime;
        bigSlime.p_walked = 0;
        bigSlime.p_tileId = -1;
        bigSlime.p_frameOffset = 15;
        bigSlime.p_frameAmount = 2;
        bigSlime.p_alive = true;
        bigSlime.p_survived = false;
        bigSlime.p_dirty = true;

        g_enemyData[EnemyType::BigSlime] = bigSlime;
#pragma endregion

#pragma region SkeletonWarrior
        Enemy skeletonWarrior = {};
        skeletonWarrior.p_hitCooldowns = {};
        skeletonWarrior.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        skeletonWarrior.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        skeletonWarrior.p_texture = Sprites::g_textures[Sprites::TextureIndex::SkeletonWarriorEnemy];
        skeletonWarrior.p_sourceRect = {0, 0, 15, 15};
        skeletonWarrior.p_moneyDrop = 45;
        skeletonWarrior.p_health = 125;
        skeletonWarrior.p_defense = 6;
        skeletonWarrior.p_position = {-1.0f, -1.0f};
        skeletonWarrior.p_id = 0;
        skeletonWarrior.p_speed = 1.5f;
        skeletonWarrior.p_timeToNextFrame = 0.5f;
        skeletonWarrior.p_timePassed = 0.0f;
        skeletonWarrior.p_timeToMove = 0.0f;
        skeletonWarrior.p_hitEffectTime = 0.0f;
        skeletonWarrior.p_typeId = EnemyType::SkeletonWarrior;
        skeletonWarrior.p_walked = 0;
        skeletonWarrior.p_tileId = -1;
        skeletonWarrior.p_frameOffset = 15;
        skeletonWarrior.p_frameAmount = 2;
        skeletonWarrior.p_alive = true;
        skeletonWarrior.p_survived = false;
        skeletonWarrior.p_dirty = true;

        g_enemyData[EnemyType::SkeletonWarrior] = skeletonWarrior;
#pragma endregion

#pragma region SkeletonGuardian
        Enemy skeletonGuardian = {};
        skeletonGuardian.p_hitCooldowns = {};
        skeletonGuardian.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet) {};
        skeletonGuardian.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        skeletonGuardian.p_texture = Sprites::g_textures[Sprites::TextureIndex::SkeletonGuardianEnemy];
        skeletonGuardian.p_sourceRect = {0, 0, 15, 15};
        skeletonGuardian.p_moneyDrop = 305;
        skeletonGuardian.p_health = 500;
        skeletonGuardian.p_defense = 10;
        skeletonGuardian.p_position = {-1.0f, -1.0f};
        skeletonGuardian.p_id = 0;
        skeletonGuardian.p_speed = 2.5f;
        skeletonGuardian.p_timeToNextFrame = 0.5f;
        skeletonGuardian.p_timePassed = 0.0f;
        skeletonGuardian.p_timeToMove = 0.0f;
        skeletonGuardian.p_hitEffectTime = 0.0f;
        skeletonGuardian.p_typeId = EnemyType::SkeletonGuardian;
        skeletonGuardian.p_walked = 0;
        skeletonGuardian.p_tileId = -1;
        skeletonGuardian.p_frameOffset = 15;
        skeletonGuardian.p_frameAmount = 2;
        skeletonGuardian.p_alive = true;
        skeletonGuardian.p_survived = false;
        skeletonGuardian.p_dirty = true;

        g_enemyData[EnemyType::SkeletonGuardian] = skeletonGuardian;
#pragma endregion

#pragma region SkeletonKing
        Enemy skeletonKing = {};
        skeletonKing.p_hitCooldowns = {};
        skeletonKing.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet)
        {
            constexpr float timeToStun = 10.0f;
            constexpr int32_t stunTime = 10;
            static float time = 0.0f;

            if (time >= timeToStun)
            {
                Debug::Print("Stun fired");

                const Vector2 centerPos = mgr_enemy->GetCenterPosition(enemy);

                Bullet bullet = Bullets::GetBulletData(BulletType::ShockWave);
                bullet.p_damage = stunTime;
                bullet.p_position = centerPos;
                mgr_bullet->AddBullet(bullet);
                
                time = 0.0f;
            }
            time += deltaTime;
        };
        skeletonKing.p_deathCallback = [](Enemy &enemy, EnemyManager *mgr_enemy) {};
        skeletonKing.p_texture = Sprites::g_textures[Sprites::TextureIndex::SkeletonKingEnemy];
        skeletonKing.p_sourceRect = {0, 0, 15, 15};
        skeletonKing.p_moneyDrop = 2500;
        skeletonKing.p_health = 3500;
        skeletonKing.p_defense = 5;
        skeletonKing.p_position = {-1.0f, -1.0f};
        skeletonKing.p_id = 0;
        skeletonKing.p_speed = 7.0f;
        skeletonKing.p_timeToNextFrame = 0.5f;
        skeletonKing.p_timePassed = 0.0f;
        skeletonKing.p_timeToMove = 0.0f;
        skeletonKing.p_hitEffectTime = 0.0f;
        skeletonKing.p_typeId = EnemyType::SkeletonKing;
        skeletonKing.p_walked = 0;
        skeletonKing.p_tileId = -1;
        skeletonKing.p_frameOffset = 15;
        skeletonKing.p_frameAmount = 2;
        skeletonKing.p_alive = true;
        skeletonKing.p_survived = false;
        skeletonKing.p_dirty = true;

        g_enemyData[EnemyType::SkeletonKing] = skeletonKing;
#pragma endregion
    }

    Enemy GetEnemyData(const EnemyType typeId)
    {
        auto it = g_enemyData.find(typeId);
        if (it != g_enemyData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in enemyData");
        return Enemy{};
    }
}
