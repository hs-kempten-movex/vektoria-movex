#include "KinematicPlacement.h"

using namespace PlayerNS;

KinematicPlacement::KinematicPlacement(float maxVelocity, float maxHeight) :
    m_maxVelocity{ maxVelocity },
    m_maxHeight{ maxHeight },
    m_collisionObjects{ nullptr },
    m_collisionTerrains{ nullptr }

{
}

KinematicPlacement::KinematicPlacement(float maxVelocity, float maxHeight, CGeos* collisionObjects, CGeoTerrains* collisionTerrains) :
    m_maxVelocity { maxVelocity },
    m_maxHeight{ maxHeight },
    m_collisionObjects{ collisionObjects },
    m_collisionTerrains{ collisionTerrains }
{
}

void KinematicPlacement::SetAcceleration(CHVector acceleration)
{
    if (m_collisionTerrains != nullptr)
    {
        CHVector pos = GetPos();
        CHitPoint terrainHitPoint;
        m_collisionTerrains->GetHitpoint(pos.x, pos.z, terrainHitPoint);

        if (terrainHitPoint.m_bExistent && terrainHitPoint.m_vPos.y + m_maxHeight < pos.y)
        {
            acceleration.y = 0.0f;
        }
    }

    m_acceleration = acceleration + CHVector(0, -0.0981f, 0);
}

void KinematicPlacement::Tick(float fTime, float fTimeDelta)
{
    CHVector translationVector = m_velocity * fTimeDelta;
    m_velocity += m_acceleration;
    if (m_velocity.Length() > m_maxVelocity)
    {
        m_velocity = m_velocity.Normal() * m_maxVelocity;
    }

    m_velocity *= m_dampening;

    if (m_collisionTerrains != nullptr)
    {
        CHVector nextPos = GetPos() + translationVector;
        CHitPoint terrainHitPoint;
        m_collisionTerrains->GetHitpoint(nextPos.x, nextPos.z, terrainHitPoint);

        if (terrainHitPoint.m_bExistent && terrainHitPoint.m_vPos.y > nextPos.y)
        {
            // on floor
            m_velocity = CHVector();
            return;
        }
    }

    if (m_collisionObjects != nullptr)
    {
        CRay intersectionRay = CRay(GetPos(), translationVector, QUASI_ZERO, translationVector.Length());
        CHitPoint objectHitPoint;
        m_collisionObjects->Intersects(intersectionRay, objectHitPoint);

        if (objectHitPoint.m_bExistent) 
        {
            m_velocity = CHVector();
            return;
        }
    }

    TranslateDelta(translationVector);
}