#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "bulletmanager.hpp"
#include "../utility/debugutil.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/basics.hpp"
#include "../managers/psmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/enemies.hpp"
#include <raymath.h>
#include <algorithm>
#include <limits>
#include <cassert>


const Vector2 EnemyManager::CalculateMovePosition(const int16_t moveDirection) const
{
    float dy = 0.0f;
    float dx = 0.0f;
    switch (std::abs(moveDirection))
    {
    case 1:
        dy = -15.0f;
        break;
    case 2:
        dy = +15.0f;
        break;
    case 3:
        dx = +15.0f;
        break;
    case 4:
        dx = -15.0f;
        break;
    default:
        break;
    }
    return Vector2{dx, dy};
}
void EnemyManager::UpdateVisualPosition(Enemy &enemy, const Vector2 &tilePosition, const int16_t moveDirection)
{
    Vector2 movePosition = CalculateMovePosition(moveDirection);

    constexpr float minTime = 0.0f;
    float normalizedTime = (enemy.p_timeToMove - minTime) / (enemy.p_speed - minTime);
    enemy.p_position = Vector2Add(tilePosition, Vector2Scale(movePosition, normalizedTime));
}
void EnemyManager::UpdateMovement(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_tileId == -1)
    {
        return;
    }
    enemy.p_timeToMove += deltaTime;

    Tile positionTile = mgr_tile->GetTile(enemy.p_tileId);
    int16_t moveDirection = (uint16_t)positionTile.p_moveDirection;
    if (moveDirection != -5)
    {
        UpdateVisualPosition(enemy, positionTile.p_position, moveDirection);
        if (enemy.p_timeToMove >= enemy.p_speed)
        {
            enemy.p_tileId = mgr_tile->GetMovedId(enemy.p_tileId, moveDirection);
            enemy.p_timeToMove = 0;
            enemy.p_dirty = true;
            enemy.p_walked += 1;
        }
    }
    else
    {
        enemy.p_survived = true;
        return;
    }
}
void EnemyManager::UpdateHitEffect(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_hitEffectTime <= 0)
    {
        return;
    }

    enemy.p_hitEffectTime -= deltaTime;
}
void EnemyManager::UpdateCooldown(Enemy &enemy, const float deltaTime)
{
    std::vector<int> indexsToDelete = {};
    for (size_t i = 0; i < enemy.p_hitCooldowns.size(); i++)
    {
        enemy.p_hitCooldowns[i].first -= deltaTime;
        if (enemy.p_hitCooldowns[i].first <= 0)
        {
            indexsToDelete.push_back(i);
        }
    }
    for (int i = indexsToDelete.size() - 1; i >= 0; i--)
    {
        enemy.p_hitCooldowns.erase(enemy.p_hitCooldowns.begin() + indexsToDelete[i]);
    }
}
void EnemyManager::UpdateAnimation(Enemy &enemy, const float deltaTime)
{
    Basics::Animate(deltaTime, enemy);
}
void EnemyManager::UpdateEnemy(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_dirty)
    {
        CleanEnemy(enemy);
    }

    HandleHits(enemy);
    UpdateMovement(enemy, deltaTime);
    UpdateCooldown(enemy, deltaTime);
    UpdateHitEffect(enemy, deltaTime);
    UpdateAnimation(enemy, deltaTime);
    if (enemy.p_updateFunction)
    {
        enemy.p_updateFunction(deltaTime, enemy, this, mgr_bullet);
    }
    else
    {
        Debug::PrintError(enemy.p_id, "Invalid Function Enemy ID");
        Debug::PrintError((int)enemy.p_typeId, "Invalid Function Enemy TypeID");
    }
    if (enemy.p_health <= 0)
    {
        enemy.p_alive = false;
    }
    if (!enemy.p_alive || enemy.p_survived)
    {
        PreKillEnemy(enemy);
    }
}
void EnemyManager::HandleHits(Enemy &enemy)
{
    constexpr float hitCooldown = 3.0f;
    constexpr float hitEffectTime = 0.4f;
    const Rectangle enemyRect = {enemy.p_position.x, enemy.p_position.y, (float)enemy.p_sourceRect.width, (float)enemy.p_sourceRect.height};

    std::vector<Bullet *> detectedBullets = mgr_bullet->GetBulletsFromArea(enemyRect,BulletOwner::Tower);
    for (auto bullet : detectedBullets)
    {
        bool bulletOnCooldown = false;
        for (size_t i = 0; i < enemy.p_hitCooldowns.size(); i++)
        {
            if (enemy.p_hitCooldowns[i].second == bullet->p_id)
            {
                bulletOnCooldown = true;
                continue;
            };
        }
        if (bulletOnCooldown)
        {
            continue;
        }

        if (!bullet->p_alive)
        {
            continue;
        }
        else if (!bullet->p_pierce)
        {
            bullet->p_alive = false;
        }
        else
        {
            enemy.p_hitCooldowns.push_back({hitCooldown, bullet->p_id});
        }

        enemy.p_health -= static_cast<int64_t>(Clamp(bullet->p_damage - enemy.p_defense, 0.0f, std::numeric_limits<int64_t>::max()));
        enemy.p_hitEffectTime = hitEffectTime;
    }
}
void EnemyManager::CheckForHover()
{
    const Vector2 mousePosition = GetMousePosition();
    for (auto &enemy : m_enemies)
    {
        Rectangle rect =
            {
                (Settings::g_boundingSize + enemy.p_position.x) * Settings::g_gameScale,
                enemy.p_position.y * Settings::g_gameScale,
                enemy.p_sourceRect.width * Settings::g_gameScale,
                enemy.p_sourceRect.height * Settings::g_gameScale};
        if (CheckCollisionPointRec(mousePosition, rect))
        {
            m_hoveredEnemy = &enemy;
            return;
        }
    }
    m_hoveredEnemy = nullptr;
}
void EnemyManager::PreKillEnemy(Enemy &enemy)
{
    if (!enemy.p_alive)
    {
        if (enemy.p_isSummon)
        {
            return;
        }
        m_killedEnemies += 1;
        mgr_ps->AddMoney(enemy.p_moneyDrop);

        enemy.p_deathCallback(enemy, this);
    }
    else if (enemy.p_survived)
    {
        mgr_ps->SubHealth(enemy.p_health);
    }
}
void EnemyManager::CleanEnemy(Enemy &enemy)
{
    if (enemy.p_tileId == -1)
    {
        enemy.p_tileId = mgr_tile->GetPathStart().p_id;
    }

    const Tile tile = mgr_tile->GetTile(enemy.p_tileId);
    if (tile.p_id == -1)
    {
        return;
    }

    enemy.p_position = tile.p_position;
    enemy.p_dirty = false;
}
void EnemyManager::RemoveEnemies()
{
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](Enemy &enemy)
                                   { return !enemy.p_alive || enemy.p_survived; }),
                    m_enemies.end());
}

std::string EnemyManager::EnemyTypeToString(const EnemyType type)
{
    switch (type)
    {
    case EnemyType::BlueSlime:
        return "Blue Slime";
        break;
    case EnemyType::RedSlime:
        return "Red Slime";
        break;
    case EnemyType::Zombie:
        return "Zombie";
        break;
    case EnemyType::ArmoredZombie:
        return "Armored Zombie";
        break;
    case EnemyType::Skeleton:
        return "Skeleton";
        break;
    case EnemyType::Summoner:
        return "Summoner";
        break;
    case EnemyType::QuickSlime:
        return "Quick Slime";
        break;
    case EnemyType::ElectricSlime:
        return "Electric Slime";
        break;
    case EnemyType::SmallSlime:
        return "Small Slime";
        break;
    case EnemyType::BigSlime:
        return "Big Slime";
        break;
    case EnemyType::SkeletonWarrior:
        return "Skeleton Warrior";
        break;
    case EnemyType::SkeletonGuardian:
        return "Skeleton Guardian";
        break;
    case EnemyType::SkeletonKing:
        return "Skeleton King";
        break;
    default:
        return "Unknown";
        break;
    }
}
bool EnemyManager::IsEnemiesEmpty() const
{
    return m_enemies.empty();
}
uint32_t EnemyManager::GetNewValidId()
{
    return m_IdCounter++;
}
Vector2 EnemyManager::GetCenterPosition(const Enemy &enemy) const
{
    return Vector2{enemy.p_position.x + enemy.p_sourceRect.width / 2.0f, enemy.p_position.y + enemy.p_sourceRect.height / 2.0f};
}
const uint32_t EnemyManager::GetKilledAmount() const
{
    return m_killedEnemies;
}
uint32_t EnemyManager::FindEnemyInArea(const Vector2 center, const float radius, const TargetingType targetingType)
{
    int64_t enemyHealth = -1;
    int32_t enemyWalked = -1;
    uint32_t enemyId = 0;
    for (auto &enemy : m_enemies)
    {
        Vector2 enemyCenter = GetCenterPosition(enemy);
        if (CheckCollisionPointCircle(enemyCenter, center, radius))
        {
            if (enemyHealth == -1 && enemyWalked == -1)
            {
                enemyHealth = enemy.p_health;
                enemyWalked = enemy.p_walked;
                enemyId = enemy.p_id;
            }

            if (targetingType == TargetingType::First)
            {
                if (enemyWalked < enemy.p_walked)
                {
                    enemyWalked = enemy.p_walked;
                    enemyId = enemy.p_id;
                }
            }
            else if (targetingType == TargetingType::Last)
            {
                if (enemyWalked > enemy.p_walked)
                {
                    enemyWalked = enemy.p_walked;
                    enemyId = enemy.p_id;
                }
            }
            else if (targetingType == TargetingType::Strongest)
            {
                if (enemyHealth < enemy.p_health)
                {
                    enemyHealth = enemy.p_health;
                    enemyId = enemy.p_id;
                }
            }
            else if (targetingType == TargetingType::Weakest)
            {
                if (enemyHealth > enemy.p_health)
                {
                    enemyHealth = enemy.p_health;
                    enemyId = enemy.p_id;
                }
            }
        }
    }
    return enemyId;
}
Enemy *EnemyManager::GetEnemyById(const uint32_t id)
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_id == id)
            return &enemy;
    }
    return nullptr;
}
const Enemy *EnemyManager::GetHoveredEnemy() const
{
    return m_hoveredEnemy;
}
void EnemyManager::AddEnemy(Enemy enemy)
{
    CleanEnemy(enemy);
    m_enemies.push_back(enemy);
}
void EnemyManager::SpawnEnemy(const EnemyType enemyType)
{
    Enemy enemy = Enemies::GetEnemyData(enemyType);
    enemy.p_tileId = -1;
    enemy.p_id = GetNewValidId();
    CleanEnemy(enemy);
    AddEnemy(enemy);
}
void EnemyManager::ReserveEnemies(const uint16_t amount)
{
    m_enemies.reserve(amount);
}
void EnemyManager::ClearEnemiesVector()
{
    m_enemies.clear();
}
void EnemyManager::Update(const float deltaTime)
{
    for (auto &enemy : m_enemies)
    {
        UpdateEnemy(enemy, deltaTime);
    }
    CheckForHover();
    RemoveEnemies();
}
void EnemyManager::Draw(const uint8_t screenOffset) const
{
    for (auto &enemy : m_enemies)
    {
        Color color = WHITE;
        if (enemy.p_hitEffectTime > 0.0f)
        {
            color = {230, 41, 55, 255};
        }

        constexpr Vector2 origin = {0.0f, 0.0f};
        const Texture2D texture = enemy.p_texture;
        const Vector2 position = {floorf(enemy.p_position.x + screenOffset), floorf(enemy.p_position.y)};
        const Rectangle dest = {position.x, position.y, static_cast<float>(enemy.p_sourceRect.width), static_cast<float>(enemy.p_sourceRect.height)};
        DrawTexturePro(texture, enemy.p_sourceRect, dest, origin, 0.0f, color);
    }
}
void EnemyManager::InjectDependencies(TileManager *mgr_tilePtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr)
{
    mgr_tile = mgr_tilePtr;
    mgr_bullet = mgr_bulletPtr;
    mgr_ps = mgr_psPtr;
}
void EnemyManager::Init()
{
    m_IdCounter = 1;
    m_hoveredEnemy = nullptr;
}
