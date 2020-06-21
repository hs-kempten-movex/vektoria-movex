#include "Collectable.h"

void Collectable::Init(CPlacement * placement, float cooldown, int points, float range)
{
    m_placement = placement;
    m_cooldown = cooldown;
    m_points = points;
    m_range = range;
}

void Collectable::Tick(float fTime, float fTimeDelta)
{
    if (m_remainingCooldown > 0)
    {
        m_remainingCooldown -= fTimeDelta;
    }
}

void Collectable::Gather(PlayerNS::Player* player)
{
    if (m_remainingCooldown <= 0)
    {
        for (auto& playerPosition : UtilsNS::PlacementUtils::GetGlobalPositions(player))
        {
            if (IsAvailableAtPosition(playerPosition))
            {
                player->AddPoints(m_points);
                m_remainingCooldown = m_cooldown;
                return;
            }
        }
    }
}

bool Collectable::IsAvailableAtPosition(CHVector position)
{
    for (auto& myPosition : GetGlobalPositions())
    {
        if ((myPosition - position).Length() <= m_range)
        {
            return true;
        }
    }

    return false;
}
