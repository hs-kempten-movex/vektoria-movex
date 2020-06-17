#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

namespace PlayerNS
{
    class KinematicPlacement :
        public CPlacement
    {
    public:
        KinematicPlacement(float maxVelocity);
        KinematicPlacement(float maxVelocity, CGeos* collisionObjects, CGeoTerrains* collisionTerrains);

        void Tick(float fTime, float fTimeDelta);

        void SetAcceleration(CHVector acceleration)
        {
            m_acceleration = acceleration;
        }

        void SetCollisionObjects(CGeos* collisionObjects)
        {
            m_collsioinObjects = m_collsioinObjects;
        }

        void SetCollisionTerrains(CGeoTerrains* collisionTerrains)
        {
            m_collisionTerrains = collisionTerrains;
        }

    private:
        CGeos* m_collsioinObjects;
        CGeoTerrains* m_collisionTerrains;

        float m_maxVelocity;
        float m_dampening = 0.99;

        CHVector m_velocity;
        CHVector m_acceleration;
    };
}


