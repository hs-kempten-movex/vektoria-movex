#include "Player.h"
#include <assert.h>

using namespace PlayerNS;

Player::Player(uint8_t id, uint8_t playerCount) :
    m_id{ id },
    m_playerCount { playerCount }
{
    // only two player are supported
    assert(m_id == 1 || m_id == 2);
    assert(m_playerCount >= 1);
}

void Player::Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains, unsigned int seed)
{
    // seed terrain. This is necessary for GetRandomPos()
    CollsisionTerrains->m_apgeoterrain[0]->m_random.SRand(seed);
    CHVector spawnPosition;
    CHitPoint objectHitPoint;
    do {
        // get random position
        spawnPosition = CollsisionTerrains->m_apgeoterrain[0]->GetRandomPos();

        // check if randowm position intersects with collision object
        if (CollisionObjects != nullptr)
        {
            CRay intersectionRay = CRay(spawnPosition, GetDirection(), QUASI_ZERO, 1.0f);
            CollisionObjects->Intersects(intersectionRay, objectHitPoint);
        }
    // repeat by intersection or if spawnPosition is in water (below 0)
    } while (spawnPosition.y < 0 || objectHitPoint.m_bExistent);

    // add max flight height and init player with spawn position
    spawnPosition.y += MAX_HEIGHT;
    Player::Init(pzpShadowCastingLight, CollisionObjects, CollsisionTerrains, spawnPosition);
}

void Player::Init(CPlacement* pzpShadowCastingLight, CGeos* CollisionObjects, CGeoTerrains* CollsisionTerrains, CHVector spawnPosition)
{
    // initialize controller
    Controller::Init(CollisionObjects, CollsisionTerrains);

    // move to spawn position
    Translate(spawnPosition);

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
    m_zpPitch.AddPlacement(&m_butterfly);
    m_zpPitch.SetMoveRange(CAABB(
        CHVector(-50000.0f, 4.0f, -50000.0f, 1.0f),
        CHVector(+50000.0f, 20000.0f, +50000.0f, 1.0f)));
    
    // init and add camera
    m_camera.Init(HALFPI, 0.3f, 170000.0f, true, pzpShadowCastingLight);
    m_zpPitch.AddPlacement(&m_zpCamera);
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
    Material.LoadPreset("NasaStars");
    PointCounter.Init(&Material, Size);
    Font.LoadPreset("LucidaConsoleWhiteF");
    
    Points.Init(Size, 20, &Font);
    Points.PrintInt(m_score);
    PointCounter.AddWriting(&Points);

    m_viewport.AddOverlay(&PointCounter);
}
