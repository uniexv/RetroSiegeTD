#pragma once
#include <cstdint>
#include <functional>
#include <raylib.h>

class BulletManager;
enum class BulletType : uint8_t {
  Shuliken = 1,
  SharpShuliken = 2,
  Dagger = 3,
  Slash = 4,
  SpearSlash = 5,
  BigSlash = 6,
  BiggestSlash = 7,
  SniperBullet = 8,
  ShockWave = 9
};

enum class BulletOwner : uint8_t { Tower = 1, Enemy = 2 };

struct Bullet {
  std::function<void(const float deltaTime, Bullet &bullet)> p_updateFunction =
      [](const float deltaTime, Bullet &bullet) {};
  std::function<void(Bullet &bullet)> p_onDeathCallback = [](Bullet &bullet) {};
  Texture2D p_texture = {0, 0, 0, 0, 0};
  Rectangle p_sourceRect = {0, 0, 0, 0};
  Vector2 p_position = {0, 0};
  Vector2 p_hitboxBonus = {0, 0};
  int32_t p_id = -1;
  int32_t p_damage = 1;
  float p_timeToNextFrame = 0.0f;
  float p_timePassed = 0.0f;
  float p_directionAngle = 0;
  float p_rotation = 0.0f;
  float p_spinSpeed = 3.0f;
  float p_speed = 1.0f;
  BulletType p_typeId = BulletType::Shuliken;
  uint16_t p_frameAmount = 0;
  uint16_t p_frameOffset = 0;
  BulletOwner p_owner = BulletOwner::Tower;
  bool p_pierce = false;
  bool p_removeAfterAnimation = false;
  bool p_alive = true;
};
