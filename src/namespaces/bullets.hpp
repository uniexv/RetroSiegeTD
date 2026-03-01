#pragma once
#include <unordered_map>
#include "../structs/bullet.hpp"

namespace Bullets
{
    extern std::unordered_map<BulletType,Bullet> g_bulletData;

    void InitBulletData();
    Bullet GetBulletData(BulletType typeId);
}
