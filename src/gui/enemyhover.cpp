#include "enemyhover.hpp"
#include "../utility/colorutil.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>

constexpr uint8_t g_hoverLabelGap = 2;
constexpr uint8_t g_hoverGuiWidth = 75;

void EnemyHover::InitLabels()
{
    constexpr size_t amountOfLabels = 3;
    mgr_gui->ReserveLabel(amountOfLabels);

    #pragma region NameLabel
    Label &nameLabel = mgr_gui->AddLabel(Label{});
    nameLabel.p_text = "";
    nameLabel.p_id = mgr_gui->GetAmountOfLabels();
    nameLabel.p_rect = {0, 0, g_hoverGuiWidth, 15};
    nameLabel.p_color = BLUE * 0.9f;
    nameLabel.p_boundingSize = 2.0f;
    nameLabel.p_boundingColor = nameLabel.p_color * 0.8f;
    nameLabel.p_visible = false;
    nameLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Enemy *enemy = this->mgr_enemy->GetHoveredEnemy();
        if (!enemy)
        {
            label.p_visible = false;
            return;
        }

        label.p_rect.x = enemy->p_position.x + enemy->p_sourceRect.width + Settings::g_boundingSize;
        label.p_rect.y = enemy->p_position.y - 15 - g_hoverLabelGap;
        label.p_text = mgr_enemy->EnemyTypeToString(static_cast<EnemyType>(enemy->p_typeId));
        label.p_visible = true;
    };
    #pragma endregion

    #pragma region HealthLabel
    Label &healthLabel = mgr_gui->AddLabel(Label{});
    healthLabel.p_text = "";
    healthLabel.p_id = mgr_gui->GetAmountOfLabels();
    healthLabel.p_rect = {0, 0, g_hoverGuiWidth, 15};
    healthLabel.p_color = RED * 0.9f;
    healthLabel.p_boundingSize = 2.0f;
    healthLabel.p_boundingColor = healthLabel.p_color * 0.8f;
    healthLabel.p_visible = false;
    healthLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Enemy *enemy = this->mgr_enemy->GetHoveredEnemy();
        if (!enemy)
        {
            label.p_visible = false;
            return;
        }

        label.p_rect.x = enemy->p_position.x + enemy->p_sourceRect.width + Settings::g_boundingSize;
        label.p_rect.y = enemy->p_position.y;
        label.p_text = "Health: " + std::to_string(enemy->p_health);
        label.p_visible = true;
    };
    #pragma endregion

    #pragma region DefenseLabel
    Label &defenseLabel = mgr_gui->AddLabel(Label{});
    defenseLabel.p_text = "";
    defenseLabel.p_id = mgr_gui->GetAmountOfLabels();
    defenseLabel.p_rect = {0, 0, g_hoverGuiWidth, 15};
    defenseLabel.p_color = GRAY * 0.9f;
    defenseLabel.p_boundingSize = 2.0f;
    defenseLabel.p_boundingColor = defenseLabel.p_color * 0.8f;
    defenseLabel.p_visible = false;
    defenseLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Enemy *enemy = this->mgr_enemy->GetHoveredEnemy();
        if (!enemy)
        {
            label.p_visible = false;
            return;
        }

        label.p_rect.x = enemy->p_position.x + enemy->p_sourceRect.width + Settings::g_boundingSize;
        label.p_rect.y = enemy->p_position.y + 15 + g_hoverLabelGap;
        label.p_text = "Defense: " + std::to_string(enemy->p_defense);
        label.p_visible = true;
    };
    #pragma endregion
}

void EnemyHover::InitButtons()
{
    
}

void EnemyHover::InjectDependencies(EnemyManager *enemyManager, GuiManager *guiManager)
{
    mgr_enemy = enemyManager;
    mgr_gui = guiManager;
}

void EnemyHover::Init()
{
    assert(mgr_enemy != nullptr && "EnemyManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
