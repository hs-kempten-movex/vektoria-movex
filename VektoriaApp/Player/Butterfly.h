#pragma once
#include "Vektoria\Root.h"

#define MAX_WING_ROTATION 1.22173F
#define WING_ROTATION_SPEED 600.0F * 0.0174533F

using namespace Vektoria;

namespace PlayerNS
{
    class Butterfly :
        public CPlacement
    {
    public:
        Butterfly();
        ~Butterfly();

        void Tick(float fTime, float fTimeDelta);

        void SetGlide(bool glide)
        {
            m_glide = glide;
        }

    private:
        CGeo* m_torso;
        CGeo* m_wingsL; 
        CGeo* m_wingsR;

        CPlacement m_zpTorso;
        CPlacement m_zpWingsL;
        CPlacement m_zpWingsR;

        CMaterial m_zmWings;
        CMaterial m_zmTorso;

        float m_wingRotation;
        float m_wingRotationDirection = -1.0f;

        bool m_glide;
    };
}