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
#include "Player/Player.h"
#include "Forest/Forest.h"
#include "Collectable.h"
#include <array>
#include <time.h>

using namespace Vektoria;
using namespace ForestNS;

class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);	// Wird nach Ende einmal aufgerufen (Destruktor)

	CRoot m_root;
	CScene m_scene;
	CFrame m_frame;

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat
	void InitPlayers();
private:

	Island m_island;

  Forest m_forest = Forest(time(NULL));

  std::array<PlayerNS::Player, 1> m_players
  {
      PlayerNS::Player(1, m_players.size())
      //PlayerNS::Player(2, m_players.size())
  };

	CGeos m_collisionObjects;
	CGeoTerrains m_collsisionTerrains;

  std::vector<Collectable> m_collectables;
};


