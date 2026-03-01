#include "particlemanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/basics.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

void ParticleManager::AddParticle(const Particle particle)
{
    m_particles.push_back(particle);
}


void ParticleManager::UpdateTextPosition(Particle &particle)
{
    const Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                                  particle.p_text.c_str(),
                                                  Settings::g_gameFont.baseSize, 0.0f);
    particle.p_textPosition =
        {
            particle.p_drawRect.x + particle.p_drawRect.width / 2.0f - textMeasurement.x / 2.0f,
            particle.p_drawRect.y + particle.p_drawRect.height / 2.0f - textMeasurement.y / 2.0f
        };
}

void ParticleManager::UpdateTransparency(Particle &particle)
{
    if (particle.p_startingTime > 0.0f)
    {
        particle.p_transparency = particle.p_aliveTime / particle.p_startingTime;
        particle.p_transparency = Clamp(particle.p_transparency,0.0f,1.0f);
    }
    else
    {
        particle.p_transparency = 1.0f;
    }
}

void ParticleManager::UpdateMovement(Particle &particle, const float deltaTime)
{

    particle.p_drawRect.x = particle.p_position.x;
    particle.p_drawRect.y = particle.p_position.y;

    switch (particle.p_particleMoveType)
    {
    case ParticleMoveType::MoveUp:
        particle.p_position.y -= particle.p_speed * deltaTime;
        break;
    case ParticleMoveType::MoveUpWiggle:
        particle.p_position.y -= particle.p_speed * deltaTime;
        particle.p_drawRect.x = particle.p_position.x + (sin(particle.p_aliveTime * particle.p_speed ) * particle.p_amplitude);
        break;
    case ParticleMoveType::MoveDown:
        particle.p_position.y += particle.p_speed * deltaTime;
        break;
    case ParticleMoveType::MoveWiggleDown:
        particle.p_position.y += particle.p_speed * deltaTime;
        particle.p_drawRect.x = particle.p_position.x + (sin(particle.p_aliveTime * particle.p_speed ) * particle.p_amplitude);
        break;
    default:
        break;
    }
}

void ParticleManager::Update(const float deltaTime)
{
    for (auto &particle : m_particles)
    {
        particle.p_aliveTime -= deltaTime;
        UpdateTextPosition(particle);
        UpdateTransparency(particle);
        UpdateMovement(particle, deltaTime);
    }

    auto removeCondition = [](const Particle &p)
    { return p.p_aliveTime <= 0.0f; };
    m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), removeCondition), m_particles.end());
}

void ParticleManager::Draw(const uint8_t screenOffset) const
{
    for (const auto &particle : m_particles)
    {
        Rectangle drawRect = particle.p_drawRect;
        drawRect.x += Settings::g_boundingSize;
        drawRect.x = floorf(drawRect.x);
        drawRect.y = floorf(drawRect.y);
        drawRect.width = floorf(drawRect.width);
        drawRect.height = floorf(drawRect.height);
        Color drawColor = particle.p_color;
        drawColor.a *= particle.p_transparency;
        Vector2 drawOrigin = {drawRect.width/2.0f,drawRect.height/2.0f};
        if (!particle.p_text.empty())
        {
            Vector2 textDrawPosition = particle.p_textPosition;
            textDrawPosition.x = floorf(textDrawPosition.x);
            textDrawPosition.y = floorf(textDrawPosition.y);
            DrawTextEx(Settings::g_gameFont,particle.p_text.c_str(),textDrawPosition,Settings::g_gameFont.baseSize,0.0f,drawColor);
        }
        DrawRectanglePro(drawRect,drawOrigin,particle.p_rotation,drawColor);
    }
}

void ParticleManager::Init()
{
}
