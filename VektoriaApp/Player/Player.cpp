#include "Player.h"
#include <assert.h>

using namespace PlayerNS;

Player::Player(uint8_t id, uint8_t playerCount, CHVector spawnPosition) :
    m_id{ id },
    m_playerCount { playerCount }
{
    // only two player are supported
    assert(m_id == 1 || m_id == 2);
    assert(m_playerCount >= 1);

    // move to spawn position
    Translate(spawnPosition);
}

void Player::Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains)
{
    // initialize controller
    Controller::Init(CollisionObjects, CollsisionTerrains);

    // if just one player, init fullscreen
    if (m_playerCount == 1)
    {
        assert(m_id == 1);
        m_viewport.InitFull(&m_camera);
    } 
    else
    {
        // otherwise init left side for player one and right side for player two
        if (m_id == 1)
        {
            m_viewport.InitHalfLeft(&m_camera);
        }
        else if (m_id == 2)
        {
            m_viewport.InitHalfRight(&m_camera);
        }
    }

    m_viewport.SetHazeOn();

    // add butterfly and restrict move range
    pitch.AddPlacement(&m_butterfly);
    pitch.SetMoveRange(CAABB(
        CHVector(-50000.0f, 4.0f, -50000.0f, 1.0f),
        CHVector(+50000.0f, 20000.0f, +50000.0f, 1.0f)));
    
    // init and add camera
    m_camera.Init(HALFPI, 0.3, 170000.0f, true, pzpShadowCastingLight);
    pitch.AddPlacement(&m_zpCamera);
    m_zpCamera.TranslateDelta(0.0f, 6.0f, 30.0f);
    m_zpCamera.AddCamera(&m_camera);
}

void Player::Tick(float fTime, float fTimeDelta)
{
    Controller::Tick(fTime, fTimeDelta);

    m_butterfly.SetGlide(GetVelocity().y < 0.0f && (GetFront() * GetVelocity()) / MAX_VELOCITY > GLIDE_THRESHOLD);
    m_butterfly.RotateZ(-(GetRight() * GetVelocity()) / MAX_VELOCITY);    
    m_butterfly.Tick(fTime, fTimeDelta);
}

    //in progress unbekannte vektoria features zu beseitigen

void Player::InitScore()
{
    COverlay PointCounter = COverlay();
    CMaterial Material = CMaterial();
    Material.LoadPreset("NasaStars");
    CFloatRect Size = CFloatRect(0, 0, 200, 200);
    PointCounter.Init(&Material, Size);
    CWritingFont Font = CWritingFont();
    Font.LoadPreset("LucidaConsoleWhiteF");
    CWriting Points = CWriting();
    
    Points.Init(Size, 20, &Font);
    Points.PrintInt(m_score);
    PointCounter.AddWriting(&Points);

    m_viewport.AddOverlay(&PointCounter);
}
