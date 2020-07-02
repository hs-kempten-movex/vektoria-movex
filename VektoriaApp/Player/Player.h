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

        void UpdateScore()
        {
                m_Writing.PrintInt(m_score);
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

    protected:
		//overlay test
        COverlay m_PointOverlay;
        CFloatRect m_FloatRect;
        CFloatRect m_PointFloatRect;
        CWritingFont* m_WritingFont;
		CWriting m_Writing;
        CWriting m_PointWriting;
        CImage m_Image;
    };
}