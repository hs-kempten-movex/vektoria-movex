#include "Game.h"
#include <iostream>

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
	m_frame.AddDeviceMouse(&m_keyboard);
	m_root.AddScene(&m_scene);
	m_root.AddMaterial(&m_zmBlossom);
	
	//Himmel mit SOnne, Mond und Sterne
	m_scene.SetSkyOn(&m_keyboard.pitch);
	m_scene.SetSkyFlowOn(120);

	//Placements
	m_scene.AddPlacement(&island.m_pIsland1);
	island.m_pIsland1.AddPlacement(&m_zpLSystem);
	island.m_pIsland1.AddPlacement(&m_zpBlume);
	m_zpLSystem.AddGeo(&tree);
	m_zpLSystem.TranslateX(500.0f);
	m_keyboard.pitch.AddPlacement(&m_zpButterfly);		//Butterfly wird an Pitch Placement gehängt.
	
	//Beschränkte bewegungsfreiheit der Kamera
	m_keyboard.pitch.SetMoveRange(CAABB(
		CHVector(-50000.0f, 4.0f, -50000.0f, 1.0f),
		CHVector(+50000.0f, 20000.0f, +50000.0f, 1.0f)));

	// Initialisiere die Kamera mit Outdoor-BVH-
	// Schattenfrustumcasting (OBVHSFC) zur Beschleunigung:
  m_scene.SetFrustumCullingOff();
	m_camera.Init(HALFPI,					// 45° Kameraöffnungswinkel
	0.3, 170000.0f,							// 30cm bis 170 km Sicht
	true,									// BVH-Schattenfrustumcasting an!
	m_scene.GetSkyLightPlacement());		 // Info für das OBVHSFC

	// Initialisiere die Kamera:
	m_scene.AddPlacement(&m_keyboard.translation);
	m_keyboard.pitch.AddPlacement(&m_zpCamera);

  m_zpCamera.TranslateDelta(0.0f, 20.0f, 100.0f);
  m_zpCamera.AddCamera(&m_camera);

	// Stelle die Kamera an einen geeigneten Anfangsort:
	m_keyboard.translation.Translate(0.0f,300.0f,200.0f);

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

