#include "messagemanager.hpp"
#include <limits>
#include "../utility/debugutil.hpp"
#include <vector>

void MessageManager::ClearMessages()
{
    m_tempMessages.clear();
}
TempMessage* MessageManager::GetMessage(const TempMessageKeys& key)
{
    auto it = m_tempMessages.find(key);
    if (it != m_tempMessages.end())
    {
        return &it->second;
    }
    return nullptr;
}
const TempMessage* MessageManager::GetMessage(const TempMessageKeys& key) const
{
    auto it = m_tempMessages.find(key);
    if (it != m_tempMessages.end())
    {
        return &it->second;
    }
    return nullptr;
}
size_t MessageManager::GetMessageCount() const
{
    return m_tempMessages.size();
}
void MessageManager::InsertMessage(const TempMessageKeys &key, const TempMessage& message)
{
    m_tempMessages[key] = message;
}
bool MessageManager::RemoveMessage(const TempMessageKeys &key)
{
    return m_tempMessages.erase(key) > 0;
}
void MessageManager::Update(float deltaTime)
{
    std::vector<TempMessageKeys> keysToRemove;

    for (auto& pair : m_tempMessages)
    {
        pair.second.p_time -= deltaTime;
        if (pair.second.p_time <= std::numeric_limits<float>::epsilon())
        {
            keysToRemove.push_back(pair.first);
        }
    }

    for (const auto& key : keysToRemove)
    {
        m_tempMessages.erase(key);
    }
}
void MessageManager::Init()
{
    ClearMessages();
}
