#pragma once
#include <vector>
#include "../structs/bullet.hpp"

class BulletManager
{
private:
    static int32_t g_idCounter;

private:
    std::vector<Bullet> m_bullets = {};
private:
    void UpdatePosition(Bullet& bullet,const float deltaTime);
    void UpdateAnimation(Bullet& bullet, const float deltaTime);
    void ValidatePosition(Bullet& bullet);
    void RemoveBullets();
public:
    static int32_t GetNewValidId();
public:
    BulletManager() = default;

    Vector2 GetCenterPosition(const Bullet &bullet) const;
    std::vector<Bullet*> GetBulletsFromArea(const Rectangle area,const BulletOwner owner);
    void AddBullet(const Bullet bullet);
    void ClearBulletsVector();
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void Init();
};
