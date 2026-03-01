#include "playerstats.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/wavemanager.hpp"
#include "../managers/guimanager.hpp"
#include "../managers/psmanager.hpp"
#include <cassert>

void PlayerStats::InitLabels()
{
    constexpr size_t amountOfLabels = 2;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region HealthLabel
    Label &healthLabel = mgr_gui->AddLabel(Label{});
    healthLabel.p_text = "Health:";
    healthLabel.p_id = mgr_gui->GetAmountOfLabels();
    healthLabel.p_rect = {5, 28, 95, 20};
    healthLabel.p_color = RED;
    healthLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const std::string text = "Hp: " + std::to_string(mgr_ps->GetHealth()) + "/" + std::to_string(mgr_ps->GetMaxHealth());
        label.p_text = text;
    };
    healthLabel.p_boundingColor = healthLabel.p_color * 0.8f;
    healthLabel.p_boundingSize = 2.0f;
    
#pragma endregion

#pragma region MoneyLabel
    Label &moneyLabel = mgr_gui->AddLabel(Label{});
    moneyLabel.p_text = "Wave:";
    moneyLabel.p_id = mgr_gui->GetAmountOfLabels();
    moneyLabel.p_rect = {5, 53, 95, 20};
    moneyLabel.p_color = YELLOW;
    moneyLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const std::string text = "$: " + std::to_string(mgr_ps->GetMoney());
        label.p_text = text;
    };
    moneyLabel.p_boundingColor = moneyLabel.p_color * 0.8f;
    moneyLabel.p_boundingSize = 2.0f;
#pragma endregion
}
void PlayerStats::InjectDependencies(GuiManager *guiManager, PSManager *psManager)
{
    mgr_gui = guiManager;
    mgr_ps = psManager;
}
void PlayerStats::Init()
{
    // assert(mgr_wave != nullptr && "WaveManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
}
