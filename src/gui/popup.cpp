#include "popup.hpp"
#include "../namespaces/settings.hpp"
#include "../structs/button.hpp"
#include "../structs/label.hpp"
#include "../managers/messagemanager.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>

void Popup::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region PopupLabel
    Label &popupLabel = mgr_gui->AddLabel(Label{});
    popupLabel.p_text = "";
    popupLabel.p_id = mgr_gui->GetAmountOfLabels();
    popupLabel.p_rect = {(float)Settings::g_boundingSize, 0, 270, 20};
    popupLabel.p_color = BLANK;
    popupLabel.p_boundingColor = BLANK;
    popupLabel.p_textColor = BLANK;
    popupLabel.p_boundingSize = 0.0f;
    popupLabel.p_segments = 0.0f;
    popupLabel.p_roundness = 0.0f;
    popupLabel.p_visible = true;
    popupLabel.p_elementType = GuiType::GameGui;
    popupLabel.p_textPosition = {0, 0};
    popupLabel.p_imagePosition = {0, 0};
    popupLabel.p_updateFunction = [this](float deltaTime, Label &label) 
    {
        TempMessage* message = mgr_message->GetMessage(TempMessageKeys::Mes_PopUp);
        
        if (message)
        {
            label.p_text = message->p_message;
            label.p_textColor = {230, 41, 55,static_cast<unsigned char>((message->p_time / message->p_baseTime) * 255.0f)};
        }
        else
        {
            label.p_text = "";
            label.p_textColor = BLANK;
        }
    };
#pragma endregion
}

void Popup::InitButtons()
{
}

void Popup::InjectDependencies(MessageManager *messageManager, GuiManager *guiManager)
{
    mgr_message = messageManager;
    mgr_gui = guiManager;
}

void Popup::Init()
{
    assert(mgr_message != nullptr && "MessageManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
