#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    enum TextureIndex : size_t
    {
        GrassTile = 0,
        GrassPathSprite1 = 1,
        GrassPathSprite2 = 2,
        GrassPathSprite3 = 3,
        GrassPathSprite4 = 4,
        BlueSlimeEnemy = 5,
        RedSlimeEnemy = 6,
        ZombieEnemy = 7,
        ArmoredZombieEnemy = 8,
        SkeletonEnemy = 9,
        SummonerEnemy = 10,
        QuickSlimeEnemy = 11,
        ElectricSlimeEnemy = 12,
        SmallSlimeEnemy = 13,
        BigSlimeEnemy = 14,
        SkeletonWarriorEnemy = 15,
        SkeletonGuardianEnemy = 16,
        SkeletonKingEnemy = 17,
        NinjaTower1 = 18,
        NinjaTower2 = 19,
        NinjaTower3 = 20,
        NinjaTower4 = 21,
        KnightTower1 = 22,
        KnightTower2 = 23,
        KnightTower3 = 24,
        KnightTower4 = 25,
        KnightTower5 = 26,
        MarketTower1 = 27,
        MarketTower2 = 28,
        MarketTower3 = 29,
        MarketTower4 = 30,
        SniperTower1 = 31,
        SniperTower2 = 32,
        SniperTower3 = 33,
        SniperTower4 = 34,
        ShulikenBullet = 35,
        SharpShulikenBullet = 36,
        DaggerBullet = 37,
        SlashBullet = 38,
        SpearSlashBullet = 39,
        BigSlashBullet = 40,
        BiggestSlashBullet = 41,
        SniperBullet = 42,
        MusicOn = 43,
        MusicOff = 44,
        RetroSiegeTD = 45,
        SpeedButton1 = 46,
        SpeedButton2 = 47,
        SpeedButton3 = 48
    };

    inline constexpr size_t g_textureAmount = 49;
    extern std::array<Texture2D, g_textureAmount> g_textures;

    void LoadTextures();
    void UnloadTextures();
}
