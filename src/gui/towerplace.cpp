#include "towerplace.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

void TowerPlace::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region HeaderLabel
    Label &headerLabel = mgr_gui->AddLabel(Label{});
    headerLabel.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f), 3.0f, static_cast<float>(Settings::g_boundingSize - 10), 20.0f};
    headerLabel.p_id = mgr_gui->GetAmountOfLabels();
    headerLabel.p_text = "Towers: ";
    headerLabel.p_color = YELLOW;
    headerLabel.p_boundingSize = 2.0f;
    headerLabel.p_boundingColor = YELLOW * 0.8f;
#pragma endregion
}

void TowerPlace::ControlPlaceTower(const TowerType controlType)
{
    if (mgr_tower->GetPlaceTower() == controlType)
    {
        mgr_tower->SetPlaceTower(TowerType::Nothing);
    }
    else
    {
        mgr_tower->SetPlaceTower(controlType);
    }
    mgr_tower->ChangeLastSelectedTower(-1);
}

void TowerPlace::InitButtons()
{
    constexpr size_t amountOfButtons = 4;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region NinjaButton
    Button &ninjaButton = mgr_gui->AddButton(Button{});
    ninjaButton.p_text = "";
    ninjaButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f), 30.0f, 25.0f, 25.0f};
    ninjaButton.p_color = YELLOW;
    ninjaButton.p_id = mgr_gui->GetAmountOfButtons();
    ninjaButton.p_isHovered = false;
    ninjaButton.p_visible = true;
    ninjaButton.p_boundingColor = ninjaButton.p_color * 0.8f;
    ninjaButton.p_boundingSize = 2.0f;
    ninjaButton.p_image = Sprites::g_textures[Sprites::TextureIndex::NinjaTower1];
    ninjaButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::NinjaLv1);
    };
    ninjaButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::NinjaLv1)
        {
            button.p_color = YELLOW * 0.8f;
            button.p_boundingColor = button.p_color * 0.8f;
        }
        else
        {
            button.p_color = YELLOW;
            button.p_boundingColor = button.p_color * 0.8f;
        }
    };
#pragma endregion

#pragma region KnightButton
    Button &knightButton = mgr_gui->AddButton(Button{});
    knightButton.p_text = "";
    knightButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f + 30.0f), 30.0f, 25.0f, 25.0f};
    knightButton.p_color = YELLOW;
    knightButton.p_id = mgr_gui->GetAmountOfButtons();
    knightButton.p_isHovered = false;
    knightButton.p_visible = true;
    knightButton.p_boundingColor = knightButton.p_color * 0.8f;
    knightButton.p_boundingSize = 2.0f;
    knightButton.p_image = Sprites::g_textures[Sprites::TextureIndex::KnightTower1];
    knightButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::KnightLv1);
    };
    knightButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::KnightLv1)
        {
            button.p_color = YELLOW * 0.8f;
            button.p_boundingColor = button.p_color * 0.8f;
        }
        else
        {
            button.p_color = YELLOW;
            button.p_boundingColor = button.p_color * 0.8f;
        }
    };
#pragma endregion

#pragma region MarketButton
    Button &marketButton = mgr_gui->AddButton(Button{});
    marketButton.p_text = "";
    marketButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f + 30.0f + 30.0f), 30.0f, 25.0f, 25.0f};
    marketButton.p_color = YELLOW;
    marketButton.p_id = mgr_gui->GetAmountOfButtons();
    marketButton.p_isHovered = false;
    marketButton.p_visible = true;
    marketButton.p_boundingColor = marketButton.p_color * 0.8f;
    marketButton.p_boundingSize = 2.0f;
    marketButton.p_image = Sprites::g_textures[Sprites::TextureIndex::MarketTower1];
    marketButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::MarketLv1);
    };
    marketButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::MarketLv1)
        {
            button.p_color = YELLOW * 0.8f;
            button.p_boundingColor = button.p_color * 0.8f;
        }
        else
        {
            button.p_color = YELLOW;
            button.p_boundingColor = button.p_color * 0.8f;
        }
    };
#pragma endregion

#pragma region SniperButton
    Button &sniperButton = mgr_gui->AddButton(Button{});
    sniperButton.p_text = "";
    sniperButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f), 60.0f, 25.0f, 25.0f};
    sniperButton.p_color = YELLOW;
    sniperButton.p_id = mgr_gui->GetAmountOfButtons();
    sniperButton.p_isHovered = false;
    sniperButton.p_visible = true;
    sniperButton.p_boundingColor = sniperButton.p_color * 0.8f;
    sniperButton.p_boundingSize = 2.0f;
    sniperButton.p_image = Sprites::g_textures[Sprites::TextureIndex::SniperTower1];
    sniperButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::SniperLv1);
    };
    sniperButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::SniperLv1)
        {
            button.p_color = YELLOW * 0.8f;
            button.p_boundingColor = button.p_color * 0.8f;
        }
        else
        {
            button.p_color = YELLOW;
            button.p_boundingColor = button.p_color * 0.8f;
        }
    };
#pragma endregion

}
void TowerPlace::InjectDependencies(TowerManager *towerManager, GuiManager *guiManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
}
void TowerPlace::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
