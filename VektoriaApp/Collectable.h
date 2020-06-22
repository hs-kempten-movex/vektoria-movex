#pragma once
#include "Vektoria\Root.h"
#include "Player/Player.h"
#include "Utils/PlacementUtils.h"
#include <vector>

using namespace Vektoria;

class Collectable
{
public:
    void Init(CPlacement* placement, float cooldown, int points, float range);

    virtual void Tick(float fTime, float fTimeDelta);

    virtual void Gather(PlayerNS::Player* player);

    std::vector<CHVector> GetGlobalPositions()
    {
        return UtilsNS::PlacementUtils::GetGlobalPositions(m_placement);
    }

    bool IsAvailableAtPosition(CHVector position);

private:
    CPlacement* m_placement;

    CPlacement m_zpEmmitter;
    CEmitter m_emitter;
    CMaterial m_emmiterMaterial;
    CGeoQuad m_emmiterGeo;

    CMaterial m_particleMaterial;
    CPlacement m_zpParticle;
    CGeoQuad m_particleGeo;

    int m_points;
    float m_range;

    float m_cooldown;
    float m_remainingCooldown = 0.0f;
};

