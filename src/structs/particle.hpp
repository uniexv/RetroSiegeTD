#pragma once
#include <string>
#include <raylib.h>
#include <cstdint>

enum class ParticleMoveType : uint8_t
{
    MoveUp = 1,
    MoveUpWiggle = 2,
    MoveDown = 3,
    MoveWiggleDown = 4
};

struct Particle
{
    std::string p_text = "";
    Rectangle p_drawRect = {0, 0, 0, 0};
    Vector2 p_position = {0,0};
    Vector2 p_textPosition = {0, 0};
    ParticleMoveType p_particleMoveType = ParticleMoveType::MoveUp;
    Color p_color = WHITE;
    float p_speed = 1.0f;
    float p_rotation = 0.0f;
    float p_amplitude = 1.0f;
    float p_transparency = 1.0f;
    float p_aliveTime = 0.0f;
    float p_startingTime = 0.0f;
};
