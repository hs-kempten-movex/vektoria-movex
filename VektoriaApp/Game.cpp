
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
	m_root.AddFrame(&m_frame);
	m_root.AddScene(&m_scene);
	
	//Himmel mit SOnne, Mond und Sterne
	m_scene.SetSkyFlowOn(120);

	//Placements
	m_scene.AddPlacement(&island.m_pIsland1);
	m_scene.AddPlacement(&island.m_pIsland2);
	m_scene.AddPlacement(&island.m_pIsland3);
	m_scene.AddPlacement(&island.m_pIsland4);
  
	// Initialisiere die Kamera mit Outdoor-BVH-
	// Schattenfrustumcasting (OBVHSFC) zur Beschleunigung:
	m_scene.SetFrustumCullingOn();

  //TODO check how sky works with multiple cameras. It shoud be set on the camera placement instead of the island placement
  m_scene.SetSkyOn(&island.m_pIsland1);

	InitPlayers();

	// WALD HIER //
  m_forest = new ForestNS::Forest(&island.m_gTerrainOri);
	island.m_pIsland1.AddPlacement(m_forest);
}

void CGame::InitPlayers()
{
    CollsisionTerrains.Add(&island.m_gTerrainOri);
    CollsisionTerrains.Add(&island.m_gWater);

    for (auto& player : m_players)
    {
        player.Init(m_scene.GetSkyLightPlacement(), &CollisionObjects, &CollsisionTerrains);
        m_frame.AddViewport(player.GetViewport());
        m_frame.AddDeviceGameController(&player);

        m_scene.AddPlacement(player.GetTranslation());
    }
}

void CGame::Tick(float fTime, float fTimeDelta)
{
    // Hier die Echtzeit-Veränderungen einfügen:
    m_root.Tick(fTimeDelta);

    for (auto& player : m_players)
    {
        player.Tick(fTime, fTimeDelta);
    }
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
	
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
  m_frame.ReSize(iNewWidth, iNewHeight);
}

