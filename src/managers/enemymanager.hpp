#pragma once
#include <vector>
#include <string>
#include "../enums/targetingtype.hpp"
#include "../structs/enemy.hpp"

class TileManager;
class BulletManager; 
class PSManager;

class EnemyManager
{
private:
    std::vector<Enemy> m_enemies = {};
    Enemy* m_hoveredEnemy = nullptr;

    int32_t m_IdCounter = 1;
    uint32_t m_killedEnemies = 0;
    
    TileManager *mgr_tile = nullptr;
    BulletManager *mgr_bullet = nullptr;
    PSManager *mgr_ps = nullptr;

private:

    const Vector2 CalculateMovePosition(const int16_t moveDirection) const;
    void UpdateVisualPosition(Enemy &enemy, const Vector2 &tilePosition, const int16_t moveDirection);
    void UpdateMovement(Enemy &enemy, const float deltaTime);
    void UpdateHitEffect(Enemy &enemy, const float deltaTime);
    void UpdateCooldown(Enemy &enemy, const float deltaTime);
    void UpdateAnimation(Enemy &enemy, const float deltaTime);
    void UpdateEnemy(Enemy &enemy, const float deltaTime);
    void HandleHits(Enemy &enemy);
    void CheckForHover();
    void CleanEnemy(Enemy &enemy);
    void PreKillEnemy(Enemy &enemy);
    void RemoveEnemies();

public:

    std::string EnemyTypeToString(const EnemyType type);
    bool IsEnemiesEmpty() const;
    uint32_t GetNewValidId();
    Vector2 GetCenterPosition(const Enemy &enemy) const;
    const uint32_t GetKilledAmount() const;
    uint32_t FindEnemyInArea(const Vector2 center, const float radius, const TargetingType targetingType);
    Enemy *GetEnemyById(const uint32_t id);
    const Enemy *GetHoveredEnemy() const;
    void AddEnemy(Enemy enemy);
    void SpawnEnemy(const EnemyType enemy);
    void ReserveEnemies(const uint16_t amount);
    void ClearEnemiesVector();
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr);
    void Init();

};
