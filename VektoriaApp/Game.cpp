
#include "Game.h"
#include "Utils/PlacementUtils.h"

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
	m_scene.AddPlacement(&m_island.m_pIsland1);
	m_scene.AddPlacement(&m_island.m_pIsland2);
	m_scene.AddPlacement(&m_island.m_pIsland3);
	m_scene.AddPlacement(&m_island.m_pIsland4);
  
	// Initialisiere die Kamera mit Outdoor-BVH-
	// Schattenfrustumcasting (OBVHSFC) zur Beschleunigung:
	m_scene.SetFrustumCullingOn();

  //TODO check how sky works with multiple cameras. It shoud be set on the camera placement instead of the island placement
  m_scene.SetSkyOn(&m_island.m_pIsland1);
  m_scene.SetSkyShadowDepth(250.0f);

  // WALD HIER //
  m_forest.Init(&m_island.m_gTerrainOri);
  m_island.m_pIsland1.AddPlacement(&m_forest);


  auto flowers = m_forest.GetFlowers();
  m_collectables = std::vector<Collectable>(flowers.size());
  for (int i = 0; i < flowers.size(); i++)
  {
      m_collectables[i].Init(flowers[i], 3000.0f, 10, 50.0f);
  }

	InitPlayers();
}

void CGame::InitPlayers()
{
    for (auto& collisionTree : m_forest.GetCollisionObjects())
    {
        m_collisionObjects.Add(collisionTree);
    }

    m_collsisionTerrains.Add(&m_island.m_gTerrainOri);
    m_collsisionTerrains.Add(&m_island.m_gWater);

    for (auto& player : m_players)
    {
        player.Init(m_scene.GetSkyLightPlacement(), &m_collisionObjects, &m_collsisionTerrains);
        m_frame.AddViewport(player.GetViewport());
        m_frame.AddDeviceGameController(&player);

        m_scene.AddPlacement(&player);
    }
}

void CGame::Tick(float fTime, float fTimeDelta)
{
    // Hier die Echtzeit-Veränderungen einfügen:
    m_root.Tick(fTimeDelta);

    for (auto& collectable : m_collectables)
    {
        collectable.Tick(fTime, fTimeDelta);
    }

    for (auto& player : m_players)
    {
        player.Tick(fTime, fTimeDelta);

        if (player.IsGatherButtonPressed())
        {
            for (auto& collectable : m_collectables)
            {
                collectable.Gather(&player);
            }
        }
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

