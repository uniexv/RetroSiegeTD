#pragma once
#include <vector>
#include <string>
#include "../structs/tower.hpp"

class Tile;

class TileManager;
class EnemyManager;
class PSManager;
class BulletManager;
class MessageManager;

class TowerManager
{
private:

    int32_t m_idCounter = 1;

    std::vector<Tower> m_towers = {};
    int32_t m_lastSelectedTowerId = -1;
    TowerType m_placeTower = TowerType::Nothing;
    TileManager *mgr_tile = nullptr;
    EnemyManager *mgr_enemy = nullptr;
    PSManager *mgr_ps = nullptr;
    BulletManager *mgr_bullet = nullptr;
    ParticleManager *mgr_particle = nullptr;
    MessageManager *mgr_message = nullptr;
    bool m_wasAnyTowerPlaced = false;

private:

    std::vector<Tower>::iterator TryGetTowerIterator(const int32_t id);
    bool CanPlaceTowerOnTile(const Tile *tile) const;
    bool ValidateTowerPlacement(const Tower& tower) const;
    void DetectInput();
    uint16_t GetTowerTypeAmount(const TowerType type) const;
    void DetectTowerInput(Tower &tower);
    void UpdateFight(Tower &tower, const float deltatime);
    void UpdateAnimation(Tower &tower, const float deltaTime);
    void HandleHits(Tower &tower);
    void DrawSelectedTower(const uint8_t screenOffset) const;
    void DrawHoverRange(const Tower& tower,const uint8_t screenOffset) const;

public:
    TowerManager() = default;

    std::string TowerTypeToString(const TowerType type);
    Vector2 GetCenterPosition(const Tower &tower) const;
    bool WasAnyTowerPlaced() const;
    void AddTower(const Tower tower);
    void RemoveTower(const int32_t id);
    Tower *GetLastSelectedTower();
    Tower *GetTowerById(const int32_t id);
    size_t GetTowerIndexById(const int32_t id);
    const Tower *GetReadTowerById(const int32_t id) const;
    const size_t GetTowerCount() const;
    int32_t GetNextValidId();
    TowerType GetPlaceTower() const;
    void SetPlaceTower(const TowerType type);
    void ChangeLastSelectedTower(const int32_t id);
    void ClearTowersVector();
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr, EnemyManager *mgr_enemyPtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr, ParticleManager *mgr_particlePtr, MessageManager *mgr_messagePtr);
    void Init();
};
