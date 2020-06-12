#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"
#include "Island.h"
#include "Player/KeyboardControl.h"
#include "Player/Butterfly.h"
#include "Forest/Forest.h"

using namespace Vektoria;

class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);	// Wird nach Ende einmal aufgerufen (Destruktor)

	CRoot m_root;
	CScene m_scene;

	CLightParallel m_light;
	CGeoSphere m_Kugel;
	CPlacement m_pkugel;

	CFrame m_frame;
	CViewport m_viewport;
	CCamera m_camera;
	CPlacement m_zpCamera;
	PlayerNS::KeyboardControl m_keyboard;

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat
	void InitPlayer();
private:
	Island island;
  PlayerNS::Butterfly m_zpButterfly;

  ForestNS::Forest* m_forest;

	CGeos CollisionObjects;
	CGeoTerrains CollsisionTerrains;
};


