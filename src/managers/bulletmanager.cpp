#include "bulletmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/basics.hpp"
#include "../utility/debugUtil.hpp"
#include <raylib.h>
#include <cmath>
#include <algorithm>

int32_t BulletManager::g_idCounter = 1;

void BulletManager::UpdatePosition(Bullet &bullet, const float deltaTime)
{
    bullet.p_position.x += cos(bullet.p_directionAngle) * bullet.p_speed * deltaTime;
    bullet.p_position.y += sin(bullet.p_directionAngle) * bullet.p_speed * deltaTime;

    if (bullet.p_spinSpeed != 0)
    {
        bullet.p_rotation += bullet.p_spinSpeed * deltaTime;
    }
}
void BulletManager::UpdateAnimation(Bullet &bullet, const float deltaTime)
{
    Basics::Animate(deltaTime,bullet);
}
void BulletManager::ValidatePosition(Bullet &bullet)
{
    const Texture2D bulletTexture = bullet.p_texture;
    const int width = bulletTexture.width;
    const int height = bulletTexture.height;

    if (bullet.p_position.x <= 0 - width || bullet.p_position.x >= 270 + width || bullet.p_position.y <= 0 - height || bullet.p_position.y >= 270 + height)
    {
        bullet.p_alive = false;
    }
}
void BulletManager::RemoveBullets()
{
    std::vector<size_t> indexesToRemove = {};
    for (size_t i = 0; i < m_bullets.size(); i++)
    {
        if (!m_bullets[i].p_alive)
        {
            m_bullets[i].p_onDeathCallback(m_bullets[i]);
            indexesToRemove.push_back(i);
        }
    }
    if (indexesToRemove.empty())
    {
        return;
    }
    for (auto it = indexesToRemove.rbegin(); it != indexesToRemove.rend(); ++it)
    {
        m_bullets.erase(m_bullets.begin() + *it);
    }
}

Vector2 BulletManager::GetCenterPosition(const Bullet &bullet) const
{
    return Vector2{bullet.p_position.x + bullet.p_sourceRect.width / 2.0f, bullet.p_position.y + bullet.p_sourceRect.height / 2.0f};
}
std::vector<Bullet *> BulletManager::GetBulletsFromArea(const Rectangle area,const BulletOwner owner)
{
    std::vector<Bullet *> detectedBullets = {};
    for (auto &bullet : m_bullets)
    {
        if (bullet.p_owner != owner)
        {
            continue;
        }
        
        const Vector2 pos = bullet.p_position;
        const Rectangle rect = bullet.p_sourceRect;
        const float hitboxBonusX = bullet.p_hitboxBonus.x/2.0f;
        const float hitboxBonuxY = bullet.p_hitboxBonus.y/2.0f;
        const Rectangle bulletRect = {pos.x - hitboxBonusX, pos.y - hitboxBonuxY, rect.width + hitboxBonusX, rect.height + hitboxBonuxY};
        if (CheckCollisionRecs(area, bulletRect))
        {
            detectedBullets.push_back(&bullet);
        }
    }
    return detectedBullets;
}
int32_t BulletManager::GetNewValidId()
{
    return BulletManager::g_idCounter++;
}
void BulletManager::AddBullet(const Bullet bullet)
{
    m_bullets.push_back(bullet);
}

void BulletManager::ClearBulletsVector()
{
    m_bullets.clear();
}

void BulletManager::Update(const float deltaTime)
{
    for (auto &bullet : m_bullets)
    {
        UpdatePosition(bullet, deltaTime);
        UpdateAnimation(bullet, deltaTime);
        ValidatePosition(bullet);
        bullet.p_updateFunction(deltaTime,bullet);
    }
    RemoveBullets();
}
void BulletManager::Draw(const uint8_t screenOffset) const
{
    for (const auto &bullet : m_bullets)
    {
        const Texture2D texture = bullet.p_texture;
        const Vector2 position = {bullet.p_position.x + screenOffset, bullet.p_position.y};
        const Rectangle dest = {floorf(position.x), floorf(position.y), static_cast<float>(bullet.p_sourceRect.width), static_cast<float>(bullet.p_sourceRect.height)};
        const Vector2 origin = {floorf(static_cast<float>(bullet.p_sourceRect.width) / 2.0f), floorf(static_cast<float>(bullet.p_sourceRect.height) / 2.0f)};
        DrawTexturePro(texture, bullet.p_sourceRect, dest, origin, bullet.p_rotation, WHITE);
    }
}

void BulletManager::Init()
{
    BulletManager::g_idCounter = 1;
    m_bullets.clear();
}
