#include "bullets.hpp"
#include "sprites.hpp"
#include "basics.hpp"
#include <unordered_map>
#include <raymath.h>
#include <cassert>

namespace Bullets
{
    std::unordered_map<BulletType, Bullet> g_bulletData = {};

    void InitBulletData()
    {
        g_bulletData.clear();

#pragma region Shuliken
        Bullet shulikenBullet = {};

        shulikenBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::ShulikenBullet];
        shulikenBullet.p_sourceRect = {0, 0, 9, 9};
        shulikenBullet.p_hitboxBonus = {0,0};
        shulikenBullet.p_position = {-1.0f, -1.0f};
        shulikenBullet.p_id = -1;
        shulikenBullet.p_damage = 0;
        shulikenBullet.p_timeToNextFrame = 0.0f;
        shulikenBullet.p_timePassed = 0.0f;
        shulikenBullet.p_directionAngle = 0.0f;
        shulikenBullet.p_rotation = 0.0f;
        shulikenBullet.p_spinSpeed = 200.0f;
        shulikenBullet.p_speed = 75.0f;
        shulikenBullet.p_typeId = BulletType::Shuliken;
        shulikenBullet.p_frameAmount = 0;
        shulikenBullet.p_frameOffset = 0;
        shulikenBullet.p_pierce = false;
        shulikenBullet.p_removeAfterAnimation = false;
        shulikenBullet.p_alive = true;
        shulikenBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        shulikenBullet.p_onDeathCallback = [](Bullet& bullet){};
        shulikenBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::Shuliken] = shulikenBullet;
#pragma endregion

#pragma region SharpShuliken
        Bullet sharpShulikenBullet = {};
        sharpShulikenBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::SharpShulikenBullet];
        sharpShulikenBullet.p_sourceRect = {0, 0, 9, 9};
        sharpShulikenBullet.p_hitboxBonus = {0,0};
        sharpShulikenBullet.p_position = {-1.0f, -1.0f};
        sharpShulikenBullet.p_id = -1;
        sharpShulikenBullet.p_damage = 0;
        sharpShulikenBullet.p_timeToNextFrame = 0.0f;
        sharpShulikenBullet.p_timePassed = 0.0f;
        sharpShulikenBullet.p_directionAngle = 0.0f;
        sharpShulikenBullet.p_rotation = 0.0f;
        sharpShulikenBullet.p_spinSpeed = 225.0f;
        sharpShulikenBullet.p_speed = 85.0f;
        sharpShulikenBullet.p_typeId = BulletType::SharpShuliken;
        sharpShulikenBullet.p_frameAmount = 0;
        sharpShulikenBullet.p_frameOffset = 0;
        sharpShulikenBullet.p_pierce = true;
        sharpShulikenBullet.p_removeAfterAnimation = false;
        sharpShulikenBullet.p_alive = true;
        sharpShulikenBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        sharpShulikenBullet.p_onDeathCallback = [](Bullet& bullet){};
        sharpShulikenBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::SharpShuliken] = sharpShulikenBullet;
#pragma endregion

#pragma region Dagger
        Bullet daggerBullet = {};
        daggerBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::DaggerBullet];
        daggerBullet.p_sourceRect = {0, 0, 7, 3};
        daggerBullet.p_hitboxBonus = {0,0};
        daggerBullet.p_position = {-1.0f, -1.0f};
        daggerBullet.p_id = -1;
        daggerBullet.p_damage = 0;
        daggerBullet.p_timeToNextFrame = 0.0f;
        daggerBullet.p_timePassed = 0.0f;
        daggerBullet.p_directionAngle = 0.0f;
        daggerBullet.p_rotation = 0.0f;
        daggerBullet.p_spinSpeed = 0.0f;
        daggerBullet.p_speed = 105.0f;
        daggerBullet.p_typeId = BulletType::Dagger;
        daggerBullet.p_frameAmount = 0;
        daggerBullet.p_frameOffset = 0;
        daggerBullet.p_pierce = true;
        daggerBullet.p_removeAfterAnimation = false;
        daggerBullet.p_alive = true;
        daggerBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        daggerBullet.p_onDeathCallback = [](Bullet& bullet){};
        daggerBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::Dagger] = daggerBullet;
#pragma endregion

#pragma region Slash
        Bullet slashBullet = {};
        slashBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::SlashBullet];
        slashBullet.p_sourceRect = {0, 0, 8, 8};
        slashBullet.p_hitboxBonus = {10.0f,10.0f};
        slashBullet.p_position = {-1.0f, -1.0f};
        slashBullet.p_id = -1;
        slashBullet.p_damage = 0;
        slashBullet.p_timeToNextFrame = 0.05f;
        slashBullet.p_timePassed = 0.0f;
        slashBullet.p_directionAngle = 0.0f;
        slashBullet.p_rotation = 0.0f;
        slashBullet.p_spinSpeed = 0.0f;
        slashBullet.p_speed = 0.0f;
        slashBullet.p_typeId = BulletType::Slash;
        slashBullet.p_frameAmount = 8;
        slashBullet.p_frameOffset = 8;
        slashBullet.p_pierce = true;
        slashBullet.p_removeAfterAnimation = true;
        slashBullet.p_alive = true;
        slashBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        slashBullet.p_onDeathCallback = [](Bullet& bullet){};
        slashBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::Slash] = slashBullet;
#pragma endregion

#pragma region SpearSlash
        Bullet spearSlashBullet = {};

        spearSlashBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::SpearSlashBullet];
        spearSlashBullet.p_sourceRect = {0, 0, 8, 8};
        spearSlashBullet.p_hitboxBonus = {0,0};
        spearSlashBullet.p_position = {-1.0f, -1.0f};
        spearSlashBullet.p_id = -1;
        spearSlashBullet.p_damage = 0;
        spearSlashBullet.p_timeToNextFrame = 0.05f;
        spearSlashBullet.p_timePassed = 0.0f;
        spearSlashBullet.p_directionAngle = 0.0f;
        spearSlashBullet.p_rotation = 0.0f;
        spearSlashBullet.p_spinSpeed = 0.0f;
        spearSlashBullet.p_speed = 0.0f;
        spearSlashBullet.p_typeId = BulletType::SpearSlash;
        spearSlashBullet.p_frameAmount = 6;
        spearSlashBullet.p_frameOffset = 8;
        spearSlashBullet.p_pierce = true;
        spearSlashBullet.p_removeAfterAnimation = true;
        spearSlashBullet.p_alive = true;
        spearSlashBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        spearSlashBullet.p_onDeathCallback = [](Bullet& bullet){};
        spearSlashBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::SpearSlash] = spearSlashBullet;
#pragma endregion

#pragma region BigSlash
        Bullet bigSlashBullet = {};

        bigSlashBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::BigSlashBullet];
        bigSlashBullet.p_sourceRect = {0, 0, 8, 8};
        bigSlashBullet.p_hitboxBonus = {17.5f,15.0f};
        bigSlashBullet.p_position = {-1.0f, -1.0f};
        bigSlashBullet.p_id = -1;
        bigSlashBullet.p_damage = 0;
        bigSlashBullet.p_timeToNextFrame = 0.05f;
        bigSlashBullet.p_timePassed = 0.0f;
        bigSlashBullet.p_directionAngle = 0.0f;
        bigSlashBullet.p_rotation = 0.0f;
        bigSlashBullet.p_spinSpeed = 0.0f;
        bigSlashBullet.p_speed = 0.0f;
        bigSlashBullet.p_typeId = BulletType::BigSlash;
        bigSlashBullet.p_frameAmount = 8;
        bigSlashBullet.p_frameOffset = 8;
        bigSlashBullet.p_pierce = true;
        bigSlashBullet.p_removeAfterAnimation = true;
        bigSlashBullet.p_alive = true;
        bigSlashBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        bigSlashBullet.p_onDeathCallback = [](Bullet& bullet){};
        bigSlashBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::BigSlash] = bigSlashBullet;
#pragma endregion

#pragma region BiggestSlash
        Bullet biggestSlashBullet = {};

        biggestSlashBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::BiggestSlashBullet];
        biggestSlashBullet.p_sourceRect = {0, 0, 10, 10};
        biggestSlashBullet.p_hitboxBonus = {25.0f,20.0f};
        biggestSlashBullet.p_position = {-1.0f, -1.0f};
        biggestSlashBullet.p_id = -1;
        biggestSlashBullet.p_damage = 0;
        biggestSlashBullet.p_timeToNextFrame = 0.05f;
        biggestSlashBullet.p_timePassed = 0.0f;
        biggestSlashBullet.p_directionAngle = 0.0f;
        biggestSlashBullet.p_rotation = 0.0f;
        biggestSlashBullet.p_spinSpeed = 0.0f;
        biggestSlashBullet.p_speed = 0.0f;
        biggestSlashBullet.p_typeId = BulletType::BiggestSlash;
        biggestSlashBullet.p_frameAmount = 8;
        biggestSlashBullet.p_frameOffset = 10;
        biggestSlashBullet.p_pierce = true;
        biggestSlashBullet.p_removeAfterAnimation = true;
        biggestSlashBullet.p_alive = true;
        biggestSlashBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        biggestSlashBullet.p_onDeathCallback = [](Bullet& bullet){};
        biggestSlashBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::BiggestSlash] = biggestSlashBullet;
#pragma endregion

#pragma region SniperBullet
        Bullet sniperBullet = {};

        sniperBullet.p_texture = Sprites::g_textures[Sprites::TextureIndex::SniperBullet];
        sniperBullet.p_sourceRect = {0, 0, 10, 1};
        sniperBullet.p_hitboxBonus = {0,0};
        sniperBullet.p_position = {-1.0f, -1.0f};
        sniperBullet.p_id = -1;
        sniperBullet.p_damage = 0;
        sniperBullet.p_timeToNextFrame = 0.0f;
        sniperBullet.p_timePassed = 0.0f;
        sniperBullet.p_directionAngle = 0.0f;
        sniperBullet.p_rotation = 0.0f;
        sniperBullet.p_spinSpeed = 0.0f;
        sniperBullet.p_speed = 500.0f;
        sniperBullet.p_typeId = BulletType::SniperBullet;
        sniperBullet.p_frameAmount = 0;
        sniperBullet.p_frameOffset = 0;
        sniperBullet.p_pierce = false;
        sniperBullet.p_removeAfterAnimation = false;
        sniperBullet.p_alive = true;
        sniperBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet){};
        sniperBullet.p_onDeathCallback = [](Bullet& bullet){};
        sniperBullet.p_owner = BulletOwner::Tower;

        g_bulletData[BulletType::SniperBullet] = sniperBullet;
#pragma endregion

#pragma region ShockWave
        Bullet shockWaveBullet = {};
        shockWaveBullet.p_texture = {0,0,0,0,0};
        shockWaveBullet.p_sourceRect = {0, 0, 0, 0};
        shockWaveBullet.p_hitboxBonus = {0.0f,0.0f};
        shockWaveBullet.p_position = {-1.0f, -1.0f};
        shockWaveBullet.p_id = -1;
        shockWaveBullet.p_damage = 0;
        shockWaveBullet.p_timeToNextFrame = 0.05f;
        shockWaveBullet.p_timePassed = 0.0f;
        shockWaveBullet.p_directionAngle = 0.0f;
        shockWaveBullet.p_rotation = 0.0f;
        shockWaveBullet.p_spinSpeed = 0.0f;
        shockWaveBullet.p_speed = 0.0f;
        shockWaveBullet.p_typeId = BulletType::ShockWave;
        shockWaveBullet.p_frameAmount = 8;
        shockWaveBullet.p_frameOffset = 8;
        shockWaveBullet.p_pierce = true;
        shockWaveBullet.p_removeAfterAnimation = true;
        shockWaveBullet.p_alive = true;
        shockWaveBullet.p_updateFunction = [](const float deltaTime,Bullet& bullet)
        {

        constexpr Color stunColor = { 0, 121, 241, 128 };
        constexpr Vector2 startingSize = {10.0f,10.0f};
        constexpr Vector2 endSize = {50.0f,50.0f};
        constexpr float finishTime = 5.0f;

        static std::unordered_map<int32_t,std::pair<float,RenderTexture2D>> shockwaveVars = {};        

        if (!shockwaveVars.contains(bullet.p_id))
        {
            shockwaveVars[bullet.p_id] = {0.0f,LoadRenderTexture(endSize.x,endSize.y)};
        }
        
        float& time = shockwaveVars[bullet.p_id].first;
        RenderTexture2D& bulletTex = shockwaveVars[bullet.p_id].second;
        const Vector2 size = Vector2Lerp(startingSize,endSize,time/finishTime);
        const Vector2 center = {endSize.x/2.0f,endSize.y/2.0f};
        
        time += deltaTime;

        if (time >= finishTime)
        {
            bullet.p_alive = false;
            UnloadRenderTexture(bulletTex);
            shockwaveVars.erase(bullet.p_id);
            return;
        }
        

        BeginTextureMode(bulletTex);

                ClearBackground(BLANK);
                
                DrawCircleV(center,size.y/2.0f,stunColor);

        EndTextureMode();

        bullet.p_sourceRect = {center.x - size.x/2.0f,center.y - size.y/2.0f,(float)size.x,(float)size.y};
        bullet.p_texture = bulletTex.texture;

        };
        shockWaveBullet.p_onDeathCallback = [](Bullet& bullet)
        {

        };
        shockWaveBullet.p_owner = BulletOwner::Enemy;

        g_bulletData[BulletType::ShockWave] = shockWaveBullet;
#pragma endregion
    }

    Bullet GetBulletData(BulletType typeId)
    {
        auto it = g_bulletData.find(typeId);
        if (it != g_bulletData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in bulletData");
        return Bullet{};
    }
}
