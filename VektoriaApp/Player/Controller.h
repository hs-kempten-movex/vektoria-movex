#pragma once
#include "Vektoria\Root.h"
#include "KinematicPlacement.h"

using namespace Vektoria;

#define CONTROLLER_SENSITIVITY 100.0f
#define CONTROLLER_DRIFT_THRESHOLD 0.25f
#define MAX_VELOCITY 100.0f
#define BACKWARDS_ACCELERATION_MULTIPLIER 0.75f

namespace PlayerNS
{
    class Controller :
        public CDeviceGameController
    {
    public:
        Controller();
        ~Controller();

        void Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains);

        virtual void Tick(float time, float fTimeDelta);

        CPlacement* GetPitch()
        {
            return &pitch;
        }

        CPlacement* GetTranslation()
        {
            return &translation;
        }


    protected:

        KinematicPlacement translation = KinematicPlacement(MAX_VELOCITY);
        CPlacement yaw;
        CPlacement pitch;

    private:
        void rotate(float fTimeDalta);
        void move(float fTimeDelta);
    };
}