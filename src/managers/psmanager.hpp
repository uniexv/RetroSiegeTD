
#pragma once
#include <cstdint>

class PSManager
{
private:
    uint64_t m_money = 0;
    uint64_t m_health = 0;
    uint64_t m_maxHealth = 0;
public:
    PSManager() = default;

    const uint64_t GetMoney() const;
    void AddMoney(const uint64_t amount);
    void SubMoney(const uint64_t amount);
    void SetMoney(const uint64_t amount);
    bool CanAfford(const uint64_t cost) const;

    const uint64_t GetHealth() const;
    const uint64_t GetMaxHealth() const;
    void AddHealth(const uint64_t amount);
    void SubHealth(const uint64_t amount);
    void SetHealth(const uint64_t amount);
    bool IsAlive() const;

    void Init();
};
