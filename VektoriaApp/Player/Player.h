#pragma once
#include "Butterfly.h"
#include "Controller.h"
#include "Vektoria\Root.h"
#include "Vektoria\Overlay.h"

#define GLIDE_THRESHOLD 0.2f

using namespace Vektoria;

namespace PlayerNS
{
    class Player :
        public Controller
    {
    public:
        Player(uint8_t id, uint8_t playerCount);

        void Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains, unsigned int seed);
        void Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains, CHVector spawnPosition);

        virtual void Tick(float time, float fTimeDelta) override;

        CViewport* GetViewport()
        {
            return &m_viewport;
        }

        CPlacement* GetCameraPlacement()
        {
            return &m_zpCamera;
        }

        void AddPoints(int points)
        {
            m_score += points;
        }

    private:
        uint8_t m_id;
        uint8_t m_playerCount;

        CPlacement m_zpCamera;
        CCamera m_camera;

        CViewport m_viewport;
        Butterfly m_butterfly;

        int m_score = 0;
        void InitScore();

		//overlay test
		COverlay PointCounter = COverlay();
		CMaterial Material = CMaterial();
		CFloatRect Size = CFloatRect(1, 1, 200, 200);
		CWritingFont Font = CWritingFont();
		CWriting Points = CWriting();
    };
}