#pragma once
#include "Vektoria\Root.h"
#include "KinematicPlacement.h"

using namespace Vektoria;

#define CONTROLLER_SENSITIVITY 100.0f
#define CONTROLLER_DRIFT_THRESHOLD 0.25f
#define MAX_VELOCITY 100.0f
#define MAX_HEIGHT 10.0f
#define BACKWARDS_ACCELERATION_MULTIPLIER 0.75f

namespace PlayerNS
{
    class Controller :
        public CDeviceGameController,
        public KinematicPlacement
    {
    public:
        Controller();
        ~Controller();

        void Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains);

        virtual void Tick(float time, float fTimeDelta);

        CHVector GetFront()
        {
            return m_front;
        }

        CHVector GetRight()
        {
            return m_right;
        }

    protected:
        CPlacement m_zpYaw;
        CPlacement m_zpPitch;

    private:
        void rotate(float fTimeDalta);
        void move(float fTimeDelta);

        CHVector m_front;
        CHVector m_right;
    };
}