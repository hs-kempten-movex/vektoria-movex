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
	m_root.AddFrame(&m_frame);
	m_frame.AddViewport(&m_viewport);
	m_frame.AddDeviceKeyboard(&m_keyboard);
	m_root.AddScene(&m_scene);
	m_root.AddMaterial(&m_zmBlossom);
	
	//Himmel mit SOnne, Mond und Sterne
	m_scene.SetSkyOn(&m_pCamera);
	m_scene.SetSkyFlowOn(120);

	//Placements
	m_scene.AddPlacement(&island.m_pIsland1);
	island.m_pIsland1.AddPlacement(&m_zpLSystem);
	island.m_pIsland1.AddPlacement(&m_zpBlume);
	m_zpLSystem.AddGeo(&tree);
	m_zpLSystem.TranslateX(500.0f);
	
	//Beschränkte bewegungsfreiheit der Kamera
	m_pCamera.SetMoveRange(CAABB(
		CHVector(-50000.0f, 4.0f, -50000.0f, 1.0f),
		CHVector(+50000.0f, 20000.0f, +50000.0f, 1.0f)));

	// Initialisiere die Kamera mit Outdoor-BVH-
	// Schattenfrustumcasting (OBVHSFC) zur Beschleunigung:
	m_scene.SetFrustumCullingOn();
	m_camera.Init(HALFPI,					// 45° Kameraöffnungswinkel
	0.3, 170000.0f,							// 30cm bis 170 km Sicht
	true,									// BVH-Schattenfrustumcasting an!
	m_scene.GetSkyLightPlacement());		 // Info für das OBVHSFC

	// Initialisiere die Kamera:
	m_scene.AddPlacement(&m_pCamera);
	m_pCamera.AddCamera(&m_camera);
	
	// Die Kamera soll sich 30 m/s bewegen:
	m_pCamera.SetTranslationSensitivity(200);

	// Stelle die Kamera an einen geeigneten Anfangsort:
	m_pCamera.Translate(0.0f,300.0f,200.0f);


	// Blume Test 
	Poppy *BlumeAlla = new Poppy();
	m_zpBlume.AddGeo(BlumeAlla);
	m_zpBlume.TranslateX(490.0f);

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	CHitPoint hitpointGround;
	CHitPoint hitpointCollision;
	m_keyboard.PlaceWASDTerrain(
		m_pCamera,
    island.m_gsCol,
    island.m_gsHeight,
    island.m_gsTerrain,
		4.0f,
		3000.0f,
		hitpointCollision,
		hitpointGround,
		fTimeDelta);
	m_root.Tick(fTimeDelta);


}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
	
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
}

