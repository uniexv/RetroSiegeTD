#pragma once

#include <unordered_map>
#include <cstdint>
#include "../structs/tempmessage.hpp"

enum TempMessageKeys : uint16_t
{
    Mes_WaveCounter = 1,
    Mes_PopUp = 2
};

class MessageManager
{
private:
    std::unordered_map<TempMessageKeys, TempMessage> m_tempMessages;

public:
    MessageManager() = default;
    
    void ClearMessages();

    TempMessage *GetMessage(const TempMessageKeys &key);
    const TempMessage *GetMessage(const TempMessageKeys &key) const;
    size_t GetMessageCount() const;

    void InsertMessage(const TempMessageKeys &key, const TempMessage &message);
    bool RemoveMessage(const TempMessageKeys &key);

    void Update(float deltaTime);

    void Init();

};
