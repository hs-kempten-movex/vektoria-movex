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

using namespace Vektoria;

#define TERRAIN_SIZE 1000
#define TERRAIN_VERTICES 2000
#define TERRAIN_HEIGHT 350
#define TERRAIN_SAND_MAX 12
#define TERRAIN_GRASS_MAX 150
#define TERRAIN_SNOW_MAX 300


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
	CDeviceKeyboard m_keyboard;
	CPlacement m_pCamera;

	CGeoTerrain m_gTerrainOri; //Gesamtes Terrain
	CGeoTerrain m_gTerrain; //inselausschnitt
	CGeoTerrain m_gTerrainSand; //Sandausschnitt
	CGeoTerrain m_gTerrainSandMossy;
	CGeoTerrain m_gWater; //wasserausschnitt
	CGeoTerrain m_gTerrainGrass; //Grasausschnitt

	CPlacement m_pIsland1; //insel- wasserplacement

	CPerlin * m_pperlin = nullptr; //Perlin-Noise

	CBlob * m_pblob1 = nullptr; //Erhebung aus dem meer
	CBlob* m_pblob_rest = nullptr; //Artefaktlöschung

	CCut m_cutUnderSea; //Schnitt unter N.N.
	CCut m_cutInverseBeachToSnow;
	CCut m_cutInverseBeach; //strandschnitt
	CCut m_cutInverseGrass;
	CCut m_cutInverseSnow;

	CCut m_cutInverseUnder15Degrees;
	CCut m_cutUnder15Degrees;

	CMaterial m_mWater;	//Wellenmaterial
	CMaterial m_mSand; //Strandmaterial
	CMaterial m_mSandMossy;
	CMaterial m_mEarthMossy; //Erdmaterial

	CGeos m_gsCol, m_gsHeight; //Kollisionscontainer
	CGeoTerrains m_gsTerrain; //Terrainkollisionscontainer

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
    // Hier ist Platz für Deine Vektoriaobjekte:
};


