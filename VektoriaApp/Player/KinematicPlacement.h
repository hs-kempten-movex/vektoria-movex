#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

namespace PlayerNS
{
    class KinematicPlacement :
        public CPlacement
    {
    public:
        KinematicPlacement(float maxVelocity, float maxHeight);
        KinematicPlacement(float maxVelocity, float maxHeight, CGeos* collisionObjects, CGeoTerrains* collisionTerrains);

        void Tick(float fTime, float fTimeDelta);

        void SetAcceleration(CHVector acceleration);

        void SetCollisionObjects(CGeos* collisionObjects)
        {
            m_collisionObjects = collisionObjects;
        }

        void SetCollisionTerrains(CGeoTerrains* collisionTerrains)
        {
            m_collisionTerrains = collisionTerrains;
        }

        CHVector GetVelocity()
        {
            return m_velocity;
        }

    private:
        CGeos* m_collisionObjects;
        CGeoTerrains* m_collisionTerrains;

        float m_maxVelocity;
        float m_maxHeight;
        float m_dampening = 0.99f;

        CHVector m_velocity;
        CHVector m_acceleration;

        float GetMaxHeightOfCollisionTerrains(CHVector position);
    };
}


