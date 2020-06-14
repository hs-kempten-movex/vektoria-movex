#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

#define CONTROLLER_SENSITIVITY 100
#define CONTROLLER_DRIFT_THRESHOLD 0.25

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

        CPlacement translation;
        CPlacement yaw;
        CPlacement pitch;

    private:
        void rotate(float fTimeDalta);
        void move(float fTimeDelta);

        CGeos* collisionObjects;
        CGeoTerrains* collisionTerrains;
    };
}