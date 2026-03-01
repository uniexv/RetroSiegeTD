#pragma once
#include <vector>
#include "../structs/particle.hpp"

class ParticleManager
{
private:
    std::vector<Particle> m_particles = {};

public:
    ParticleManager() = default;

    void AddParticle(const Particle particle);
    void UpdateTextPosition(Particle &particle);
    void UpdateTransparency(Particle &particle);
    void UpdateMovement(Particle &particle, const float deltaTime);
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void Init();
};
