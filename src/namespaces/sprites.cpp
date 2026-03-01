#include "sprites.hpp"

namespace Sprites
{
    std::array<Texture2D, g_textureAmount> g_textures = {};

    void LoadTextures()
    {
        g_textures[TextureIndex::GrassTile] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[TextureIndex::GrassPathSprite1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[TextureIndex::GrassPathSprite2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[TextureIndex::GrassPathSprite3] = LoadTexture("src/resources/sprites/GrassPathSprite3.png");
        g_textures[TextureIndex::GrassPathSprite4] = LoadTexture("src/resources/sprites/GrassPathSprite4.png");
        g_textures[TextureIndex::BlueSlimeEnemy] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[TextureIndex::RedSlimeEnemy] = LoadTexture("src/resources/sprites/RedSlimeEnemy.png");
        g_textures[TextureIndex::ZombieEnemy] = LoadTexture("src/resources/sprites/ZombieEnemy.png");
        g_textures[TextureIndex::ArmoredZombieEnemy] = LoadTexture("src/resources/sprites/ArmoredZombieEnemy.png");
        g_textures[TextureIndex::SkeletonEnemy] = LoadTexture("src/resources/sprites/SkeletonEnemy.png");
        g_textures[TextureIndex::SummonerEnemy] = LoadTexture("src/resources/sprites/SummonerEnemy.png");
        g_textures[TextureIndex::QuickSlimeEnemy] = LoadTexture("src/resources/sprites/QuickSlimeEnemy.png");
        g_textures[TextureIndex::ElectricSlimeEnemy] = LoadTexture("src/resources/sprites/ElectricSlimeEnemy.png");
        g_textures[TextureIndex::SmallSlimeEnemy] = LoadTexture("src/resources/sprites/SmallSlimeEnemy.png");
        g_textures[TextureIndex::BigSlimeEnemy] = LoadTexture("src/resources/sprites/BigSlimeEnemy.png");
        g_textures[TextureIndex::SkeletonWarriorEnemy] = LoadTexture("src/resources/sprites/SkeletonWarriorEnemy.png");
        g_textures[TextureIndex::SkeletonGuardianEnemy] = LoadTexture("src/resources/sprites/SkeletonGuardianEnemy.png");
        g_textures[TextureIndex::SkeletonKingEnemy] = LoadTexture("src/resources/sprites/SkeletonKingEnemy.png");
        g_textures[TextureIndex::NinjaTower1] = LoadTexture("src/resources/sprites/NinjaTower1.png");
        g_textures[TextureIndex::NinjaTower2] = LoadTexture("src/resources/sprites/NinjaTower2.png");
        g_textures[TextureIndex::NinjaTower3] = LoadTexture("src/resources/sprites/NinjaTower3.png");
        g_textures[TextureIndex::NinjaTower4] = LoadTexture("src/resources/sprites/NinjaTower4.png");
        g_textures[TextureIndex::KnightTower1] = LoadTexture("src/resources/sprites/KnightTower1.png");
        g_textures[TextureIndex::KnightTower2] = LoadTexture("src/resources/sprites/KnightTower2.png");
        g_textures[TextureIndex::KnightTower3] = LoadTexture("src/resources/sprites/KnightTower3.png");
        g_textures[TextureIndex::KnightTower4] = LoadTexture("src/resources/sprites/KnightTower4.png");
        g_textures[TextureIndex::KnightTower5] = LoadTexture("src/resources/sprites/KnightTower5.png");
        g_textures[TextureIndex::MarketTower1] = LoadTexture("src/resources/sprites/MarketTower1.png");
        g_textures[TextureIndex::MarketTower2] = LoadTexture("src/resources/sprites/MarketTower2.png");
        g_textures[TextureIndex::MarketTower3] = LoadTexture("src/resources/sprites/MarketTower3.png");
        g_textures[TextureIndex::MarketTower4] = LoadTexture("src/resources/sprites/MarketTower4.png");
        g_textures[TextureIndex::SniperTower1] = LoadTexture("src/resources/sprites/SniperTower1.png");
        g_textures[TextureIndex::SniperTower2] = LoadTexture("src/resources/sprites/SniperTower2.png");
        g_textures[TextureIndex::SniperTower3] = LoadTexture("src/resources/sprites/SniperTower3.png");
        g_textures[TextureIndex::SniperTower4] = LoadTexture("src/resources/sprites/SniperTower4.png");
        g_textures[TextureIndex::ShulikenBullet] = LoadTexture("src/resources/sprites/ShulikenBullet.png");
        g_textures[TextureIndex::SharpShulikenBullet] = LoadTexture("src/resources/sprites/SharpShulikenBullet.png");
        g_textures[TextureIndex::DaggerBullet] = LoadTexture("src/resources/sprites/DaggerBullet.png");
        g_textures[TextureIndex::SlashBullet] = LoadTexture("src/resources/sprites/SlashBullet.png");
        g_textures[TextureIndex::SpearSlashBullet] = LoadTexture("src/resources/sprites/SpearSlashBullet.png");
        g_textures[TextureIndex::BigSlashBullet] = LoadTexture("src/resources/sprites/BigSlashBullet.png");
        g_textures[TextureIndex::BiggestSlashBullet] = LoadTexture("src/resources/sprites/BiggestSlashBullet.png");
        g_textures[TextureIndex::SniperBullet] = LoadTexture("src/resources/sprites/SniperBullet.png");
        g_textures[TextureIndex::MusicOn] = LoadTexture("src/resources/sprites/MusicOn.png");
        g_textures[TextureIndex::MusicOff] = LoadTexture("src/resources/sprites/MusicOff.png");
        g_textures[TextureIndex::RetroSiegeTD] = LoadTexture("src/resources/sprites/RetroSiegeTD.png");
        g_textures[TextureIndex::SpeedButton1] = LoadTexture("src/resources/sprites/SpeedButton1.png");
        g_textures[TextureIndex::SpeedButton2] = LoadTexture("src/resources/sprites/SpeedButton2.png");
        g_textures[TextureIndex::SpeedButton3] = LoadTexture("src/resources/sprites/SpeedButton3.png");

        for (size_t i = 0; i < g_textures.size(); i++)
        {
            SetTextureFilter(g_textures[i], TEXTURE_FILTER_POINT);
        }
    }

    void UnloadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}
