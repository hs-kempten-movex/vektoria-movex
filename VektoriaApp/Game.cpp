
#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash* psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_root.Init(psplash);
	m_frame.Init(hwnd, procOS);
	m_viewport.InitFull(&m_camera);
	m_viewport.SetHazeOn();
	m_root.AddFrame(&m_frame);
	m_frame.AddViewport(&m_viewport);
	m_frame.AddDeviceKeyboard(&m_keyboard);
	m_frame.AddDeviceMouse(&m_keyboard);
	m_root.AddScene(&m_scene);
	
	//Himmel mit SOnne, Mond und Sterne
	m_scene.SetSkyOn(&m_keyboard.pitch);
	m_scene.SetSkyFlowOn(120);

	//Placements
	m_scene.AddPlacement(&island.m_pIsland1);
	m_scene.AddPlacement(&island.m_pIsland2);
	m_scene.AddPlacement(&island.m_pIsland3);
	m_scene.AddPlacement(&island.m_pIsland4);
  
	// Initialisiere die Kamera mit Outdoor-BVH-
	// Schattenfrustumcasting (OBVHSFC) zur Beschleunigung:
	m_scene.SetFrustumCullingOn();
	m_camera.Init(HALFPI,					// 45° Kameraöffnungswinkel
	0.3, 170000.0f,							// 30cm bis 170 km Sicht
	true,									// BVH-Schattenfrustumcasting an!
	m_scene.GetSkyLightPlacement());		 // Info für das OBVHSFC


	InitPlayer();

	// WALD HIER //
  m_forest = new ForestNS::Forest(&island.m_gTerrainOri);
	island.m_pIsland1.AddPlacement(m_forest);
}

void CGame::InitPlayer()
{
    CollsisionTerrains.Add(&island.m_gTerrainOri);
    CollsisionTerrains.Add(&island.m_gWater);

    m_keyboard.Init(&CollisionObjects, &CollsisionTerrains);

    m_keyboard.pitch.SetMoveRange(CAABB(
        CHVector(-50000.0f, 4.0f, -50000.0f, 1.0f),
        CHVector(+50000.0f, 20000.0f, +50000.0f, 1.0f)));

    island.m_pIsland1.AddPlacement(&m_keyboard.translation);
    m_keyboard.translation.Translate(0.0f, 300.0f, 200.0f);

    m_keyboard.pitch.AddPlacement(&m_zpButterfly);
    m_keyboard.pitch.AddPlacement(&m_zpCamera);

    m_zpCamera.TranslateDelta(0.0f, 6.0f, 30.0f);
    m_zpCamera.AddCamera(&m_camera);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	CHitPoint hitpointGround;
	CHitPoint hitpointCollision;
	m_keyboard.Tick(fTimeDelta);
	m_root.Tick(fTimeDelta);

  m_zpButterfly.Tick(fTime, fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
	
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
  m_frame.ReSize(iNewWidth, iNewHeight);
}

