#include "towerselect.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/basics.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

constexpr uint16_t startingPoint = 262;
constexpr uint8_t offset = 10;
constexpr int8_t gap = -10;
constexpr uint8_t elementHeight = 15;
constexpr uint8_t boundingHeight = 190;

void TowerSelect::InitLabels()
{
    constexpr size_t amountOfLabels = 6;
    mgr_gui->ReserveLabel(amountOfLabels);
#pragma region BoundingLabel
    Label &boundingLabel = mgr_gui->AddLabel(Label{});
    boundingLabel.p_text = "";
    boundingLabel.p_id = mgr_gui->GetAmountOfLabels();
    boundingLabel.p_rect = {5, (startingPoint - offset * 8) + gap * 9 - 5, 95, boundingHeight};
    boundingLabel.p_color = DARKBLUE;
    boundingLabel.p_boundingSize = 5.0f;
    boundingLabel.p_boundingColor = boundingLabel.p_color * 0.8f;
    boundingLabel.p_visible = false;
    boundingLabel.p_roundness = 0.25f;
    boundingLabel.p_segments = 1.0f;
    boundingLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower && placeTower == TowerType::Nothing)
        {
            label.p_visible = false;
            return;
        }
        label.p_visible = true;
    };
#pragma endregion
#pragma region NameLabel
    Label &nameLabel = mgr_gui->AddLabel(Label{});
    nameLabel.p_text = "";
    nameLabel.p_id = mgr_gui->GetAmountOfLabels();
    nameLabel.p_rect = {5, (startingPoint - offset * 8) + gap * 9, 95, elementHeight};
    nameLabel.p_color = BLUE;
    nameLabel.p_boundingSize = 2.0f;
    nameLabel.p_boundingColor = nameLabel.p_color * 0.8f;
    nameLabel.p_visible = false;
    nameLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                label.p_text = "Type: " + this->mgr_tower->TowerTypeToString(placeTower);
                ;
                label.p_visible = true;
            }
        }
        else
        {
            label.p_text = "Type: " + this->mgr_tower->TowerTypeToString(static_cast<TowerType>(tower->p_typeId));
            ;
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region IdLabel
    Label &IdLabel = mgr_gui->AddLabel(Label{});
    IdLabel.p_text = "";
    IdLabel.p_id = mgr_gui->GetAmountOfLabels();
    IdLabel.p_rect = {5, (startingPoint - offset * 7) + gap * 8, 95, elementHeight};
    IdLabel.p_color = BLUE;
    IdLabel.p_boundingSize = 2.0f;
    IdLabel.p_boundingColor = IdLabel.p_color * 0.8f;
    IdLabel.p_visible = false;
    IdLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();

        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                label.p_text = "Id: N/A";
                label.p_visible = true;
            }
        }
        else
        {
            label.p_text = "Id: " + std::to_string(tower->p_id);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region LevelLabel
    Label &levelLabel = mgr_gui->AddLabel(Label{});
    levelLabel.p_text = "";
    levelLabel.p_id = mgr_gui->GetAmountOfLabels();
    levelLabel.p_rect = {5, (startingPoint - offset * 6) + gap * 7, 95, elementHeight};
    levelLabel.p_color = BLUE;
    levelLabel.p_boundingSize = 2.0f;
    levelLabel.p_boundingColor = levelLabel.p_color * 0.8f;
    levelLabel.p_visible = false;
    levelLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();

        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "Lv: " + std::to_string(tower.p_level);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "Lv: " + std::to_string(tower->p_level) + " -> " + std::to_string(postUpgradeData.p_level);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "Lv: " + std::to_string(tower->p_level);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region DamageLabel
    Label &damageLabel = mgr_gui->AddLabel(Label{});
    damageLabel.p_text = "";
    damageLabel.p_id = mgr_gui->GetAmountOfLabels();
    damageLabel.p_rect = {5, (startingPoint - offset * 5) + gap * 6, 95, elementHeight};
    damageLabel.p_color = BLUE;
    damageLabel.p_boundingSize = 2.0f;
    damageLabel.p_boundingColor = damageLabel.p_color * 0.8f;
    damageLabel.p_visible = false;
    damageLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "Dmg: " + std::to_string(tower.p_damage);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "Dmg: " + std::to_string(tower->p_damage) + " -> " + std::to_string(postUpgradeData.p_damage);
            ;
            label.p_visible = true;
        }
        else
        {
            label.p_text = "Dmg: " + std::to_string(tower->p_damage);

            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region AttackSpeedLabel
    Label &attackSpeedLabel = mgr_gui->AddLabel(Label{});
    attackSpeedLabel.p_text = "";
    attackSpeedLabel.p_id = mgr_gui->GetAmountOfLabels();
    attackSpeedLabel.p_rect = {5, (startingPoint - offset * 4) + gap * 5, 95, elementHeight};
    attackSpeedLabel.p_color = BLUE;
    attackSpeedLabel.p_boundingSize = 2.0f;
    attackSpeedLabel.p_boundingColor = attackSpeedLabel.p_color * 0.8f;
    attackSpeedLabel.p_visible = false;
    attackSpeedLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "As: " + std::format("{:.2f}", tower.p_attackSpeed);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "As: " + std::format("{:.2f}", tower->p_attackSpeed) + " -> " + std::format("{:.2f}", postUpgradeData.p_attackSpeed);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "As: " + std::format("{:.2f}", tower->p_attackSpeed);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region RangeLabel
    Label &rangeLabel = mgr_gui->AddLabel(Label{});
    rangeLabel.p_text = "R: 0";
    rangeLabel.p_id = mgr_gui->GetAmountOfLabels();
    rangeLabel.p_rect = {5, (startingPoint - offset * 3) + gap * 4, 95, elementHeight};
    rangeLabel.p_color = BLUE;
    rangeLabel.p_boundingSize = 2.0f;
    rangeLabel.p_boundingColor = rangeLabel.p_color * 0.8f;
    rangeLabel.p_visible = false;
    rangeLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "R: " + std::format("{:.2f}", tower.p_range);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "R: " + std::format("{:.2f}", tower->p_range) + " -> " + std::format("{:.2f}", postUpgradeData.p_range);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "R: " + std::format("{:.2f}", tower->p_range);
            label.p_visible = true;
        }
    };
#pragma endregion
}
void TowerSelect::InitButtons()
{
    constexpr size_t amountOfButtons = 3;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region TargettingButton
    Button &targetingButton = mgr_gui->AddButton(Button{});
    targetingButton.p_text = "Targetting";
    targetingButton.p_id = mgr_gui->GetAmountOfButtons();
    targetingButton.p_rect = {5, (startingPoint - offset * 2) + gap * 3, 95, elementHeight};
    targetingButton.p_color = GREEN;
    targetingButton.p_boundingSize = 2.0f;
    targetingButton.p_boundingColor = targetingButton.p_color * 0.8f;
    targetingButton.p_visible = false;
    targetingButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        TowerType placeTower = this->mgr_tower->GetPlaceTower();
        button.p_color = GREEN;

        if (tower)
        {
            button.p_text = "T: " + TargetingTypeUtility::ToString(tower->p_targetting);
            button.p_visible = true;
        }
        else if (placeTower != TowerType::Nothing)
        {
            Tower placeTowerData = Towers::GetTowerData(placeTower);

            button.p_text = "T: " + TargetingTypeUtility::ToString(placeTowerData.p_targetting);
            button.p_visible = true;
        }
        else
        {
            button.p_visible = false;
        }

        button.p_boundingColor = button.p_color * 0.8f;
    };
    targetingButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            return;
        }

        if (tower->p_targetting != TargetingType::Weakest)
        {
            tower->p_targetting = static_cast<TargetingType>(static_cast<uint8_t>(tower->p_targetting) + 1);
        }
        else
        {
            tower->p_targetting = TargetingType::First;
        }
    };
#pragma endregion
#pragma region UpgradeButton
    Button &upgradeButton = mgr_gui->AddButton(Button{});
    upgradeButton.p_text = "Upgrade";
    upgradeButton.p_id = mgr_gui->GetAmountOfButtons();
    upgradeButton.p_rect = {5, (startingPoint - offset * 1) + gap * 2, 95, elementHeight};
    upgradeButton.p_color = GREEN;
    upgradeButton.p_boundingSize = 2.0f;
    upgradeButton.p_boundingColor = upgradeButton.p_color * 0.8f;
    upgradeButton.p_visible = false;
    upgradeButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        button.p_color = GREEN;

        if (!tower)
        {
            button.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                Tower tower = Towers::GetTowerData(placeTower);
                button.p_color = YELLOW;
                button.p_text = "Cost: " + std::to_string(tower.p_price) + " $";
                button.p_visible = true;
            }
        }
        else if (tower->p_upgradesTo == TowerType::Nothing)
        {
            button.p_visible = true;
            button.p_color = RED;
            button.p_boundingColor = button.p_color * 0.8f;
            button.p_text = "Max Upgrade";
        }
        else
        {
            Tower upgradedTower = Towers::GetTowerData(tower->p_upgradesTo);
            button.p_text = "Upgrade: " + std::to_string(upgradedTower.p_price) + " $";
            tower->p_isUpgradeHovered = button.p_isHovered;
            button.p_visible = true;
        }

        button.p_boundingColor = button.p_color * 0.8f;
    };
    upgradeButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();

        if (tower)
        {
            if (tower->p_upgradesTo == TowerType::Nothing)
            {
                return;
            }

            Basics::UpgradeTower(deltaTime, tower, mgr_ps);
        }
    };

#pragma endregion
#pragma region SellButton
    Button &sellButton = mgr_gui->AddButton(Button{});
    sellButton.p_text = "Sell";
    sellButton.p_id = mgr_gui->GetAmountOfButtons();
    sellButton.p_rect = {5, (startingPoint - offset * 0) + gap * 1, 95, elementHeight};
    sellButton.p_color = GREEN;
    sellButton.p_boundingSize = 2.0f;
    sellButton.p_boundingColor = sellButton.p_color * 0.8f;
    sellButton.p_visible = false;
    sellButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        button.p_color = RED;

        if (!tower)
        {
            button.p_visible = false;
        }
        else
        {
            button.p_text = "Sell for " + std::format("{:.2f}", tower->p_price / 2.0f) + " $";
            button.p_visible = true;
        }

        button.p_boundingColor = button.p_color * 0.8f;
    };
    sellButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            return;
        }
        mgr_ps->AddMoney(tower->p_price / 2.0f);
        mgr_tower->RemoveTower(tower->p_id);
    };
#pragma endregion
}
void TowerSelect::InjectDependencies(TowerManager *towerManager, GuiManager *guiManager, PSManager *psManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
    mgr_ps = psManager;
}
void TowerSelect::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
