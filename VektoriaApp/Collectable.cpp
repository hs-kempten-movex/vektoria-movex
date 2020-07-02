#include "Collectable.h"

void Collectable::Init(CPlacement * placement, float cooldown, int points, float range)
{
    m_placement = placement;
    m_cooldown = cooldown;
    m_points = points;
    m_range = range;

    m_particleMaterial.MakeTextureBillboard("textures\\green_image.jpg");
    m_particleGeo.Init(0.05f, &m_particleMaterial);
    m_zpParticle.SetBillboardForEmitters();
    m_zpParticle.AddGeo(&m_particleGeo);

    m_emitter.Init();
    m_emitter.SetPlacementParticle(&m_zpParticle);
    m_emitter.SetVelocity(-0.5f);
    m_emitter.SetRate(0.0f);
    m_emitter.SetTimeToFade(10.0f);

    m_emmiterGeo.Init(1.0, &m_emmiterMaterial);
    m_emmiterGeo.AddEmitter(&m_emitter);

    m_zpEmmitter.SetLoD(0.0f, 100.0f);
    m_zpEmmitter.RotateX(HALFPI);
    m_zpEmmitter.AddGeo(&m_emmiterGeo);

    placement->AddPlacement(&m_zpEmmitter);
}

void Collectable::Tick(float fTime, float fTimeDelta)
{
    if (m_remainingCooldown > 0)
    {
        m_remainingCooldown -= fTimeDelta;
        m_emitter.SetRate(2.5f);
    }
    else
    {
        m_emitter.SetRate(0.0f);
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
                player->UpdateScore();
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
