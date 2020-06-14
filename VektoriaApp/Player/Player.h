#pragma once
#include "Butterfly.h"
#include "Controller.h"
#include "Vektoria\Root.h"

using namespace Vektoria;

namespace PlayerNS
{
    class Player :
        public Controller
    {
    public:
        Player(uint8_t id, uint8_t playerCount, CHVector spawnPosition);

        void Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains);

        virtual void Tick(float time, float fTimeDelta) override;

        CViewport* GetViewport()
        {
            return &m_viewport;
        }

        CPlacement* GetCameraPlacement()
        {
            return &m_zpCamera;
        }

    private:
        uint8_t m_id;
        uint8_t m_playerCount;

        CPlacement m_zpCamera;
        CCamera m_camera;

        CViewport m_viewport;
        Butterfly m_butterfly;
    };
}