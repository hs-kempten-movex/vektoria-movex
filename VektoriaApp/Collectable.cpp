#include "Collectable.h"

Collectable::Collectable(CPlacement* placement, float cooldown, int points) :
    m_placement{ placement },
    m_cooldown{ cooldown },
    m_points{ points }
{
}

void Collectable::Tick(float fTime, float fTimeDelta)
{
    if (m_remainingCooldown > 0)
    {
        m_remainingCooldown -= fTimeDelta;
        m_placement->SetDrawingOff();
    }
    else
    {
        m_placement->SetDrawingOn();
    }
}

void Collectable::Gather(PlayerNS::Player* player)
{
    if (m_remainingCooldown <= 0)
    {
        player->AddPoints(m_points);
    }
}