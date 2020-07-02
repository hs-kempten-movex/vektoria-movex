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
        InitScore();
        
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



void Player::InitScore()
{
	//Font erstellen, Schriftart laden, auf Transparent stellen
    m_WritingFont = new CWritingFont();
    m_WritingFont->LoadPreset("LucidaConsoleWhite");
    m_WritingFont->SetChromaKeyingOn();

	//erstellen von Bereichen für die prints
    m_FloatRect.Init(0.1f, 0.1f, 0.2f, 0.03f); //Rect für die Punkte
    m_PointFloatRect.Init(0.0f, 0.095f, 0.07f, 0.035f); //Rect für "Score:"

	//print info
    m_PointWriting.Init(m_PointFloatRect, 6, m_WritingFont);
    m_PointWriting.PrintString("Score:");
    m_Writing.Init(m_FloatRect, 10, m_WritingFont);
    m_Writing.PrintInt(m_score);

	//overlay mit transparenten hintergrund erstellen, writings hinzufügen, an viewport hängen
    m_Image.Init("textures\\Transparent_square.png");
    m_PointOverlay.Init(&m_Image, m_FloatRect, true);
    m_PointOverlay.AddWriting(&m_Writing);
    m_PointOverlay.AddWriting(&m_PointWriting);
    m_PointOverlay.SwitchOn();
    m_viewport.AddOverlay(&m_PointOverlay);
}