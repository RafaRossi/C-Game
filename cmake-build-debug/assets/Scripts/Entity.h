//
// Created by rossi on 15/07/2026.
//

#ifndef SDLPROJECT_ENTITY_H
#define SDLPROJECT_ENTITY_H

#include <vector>
#include <unordered_map>
#include "Engine/Game/Core/Component/Component.h"

enum class Stats
{
    MaxHealth,

    AttackPower,
    AttackSpeed,
    AttackRange,

    CritChance,
    CritDamage,

    Defense,
    Duration,

    Iterations,

    Luck,

    Speed,
};

struct StatsModifier
{
public:
    int id;
    Stats type;
    float value;
    bool isMultiplier;
};

class Entity : public Component{
    REGISTER_BODY(Entity, Component)

private:
    int m_CurrentHealth = 100.f;

protected:
    std::unordered_map<Stats, float> m_BaseStats;
    std::unordered_map<Stats, std::vector<StatsModifier>> m_StatModifiers;

    int m_NextModifierId = 1;

public:
    ~Entity() override = default;

    void SetBaseStat(Stats type, float value) {
        m_BaseStats[type] = value;
    }

    int AddModifier(Stats stat, float value, bool isMultiplier = false){
        StatsModifier mod{};

        mod.id = m_NextModifierId++;
        mod.type = stat;
        mod.value = value;
        mod.isMultiplier = isMultiplier;

        m_StatModifiers[stat].push_back(mod);
        return mod.id;
    }

    void RemoveModifier(int id){
        for (auto& [type, modifiersList] : m_StatModifiers) {
            std::erase_if(modifiersList, [id](const StatsModifier& m) { return m.id == id; });
        }
    }

    float GetStat(Stats type) const {
        float finalValue = 0.0f;
        auto baseIt = m_BaseStats.find(type);
        if (baseIt != m_BaseStats.end()) {
            finalValue = baseIt->second;
        }

        float multiplier = 1.0f;

        auto modIt = m_StatModifiers.find(type);
        if (modIt != m_StatModifiers.end()) {
            for (const auto& mod : modIt->second) {
                if (mod.isMultiplier) {
                    multiplier += mod.value;
                } else {
                    finalValue += mod.value;
                }
            }
        }

        return finalValue * multiplier;
    }


    int GetCurrentHealth() const {
        return m_CurrentHealth;
    }


    virtual void TakeDamage(int amount){
        m_CurrentHealth -= amount;

        if(m_CurrentHealth <= 0){
            m_CurrentHealth = 0;

            Die();
        }
    }

    virtual void Heal(int amount){
        m_CurrentHealth += amount;

        if(m_CurrentHealth > (int)GetStat(Stats::MaxHealth)){
            m_CurrentHealth = (int)GetStat(Stats::MaxHealth);
        }
    }

    virtual void Die()
    {

    }
};
#endif //SDLPROJECT_ENTITY_H
