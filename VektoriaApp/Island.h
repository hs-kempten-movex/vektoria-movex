#pragma once

#include "Vektoria\Root.h"
using namespace Vektoria;

#define TERRAIN_SIZE 2500
#define TERRAIN_VERTICES 1001
#define TERRAIN_HEIGHT 500
#define TERRAIN_SAND_MAX 3
#define TERRAIN_SAND_MOSSY_MAX 7
#define TERRAIN_ROCK_MOSSY_MAX 130
#define TERRAIN_ROCK_MAX 170
#define TERRAIN_ROCK_SNOWY_MIN 130
#define TERRAIN_ROCK_SNOWY_MAX 170

class Island
{
public:
    Island();
    ~Island();

    CGeos m_gsCol, m_gsHeight; //Kollisionscontainer
    CGeoTerrains m_gsTerrain; //Terrainkollisionscontainer

    CPlacement m_pIsland1; //insel- wasserplacement
private:
    CGeoTerrain m_gTerrainOri; //Gesamtes Terrain
	CGeoTerrain m_gTerrain; //inselausschnitt
	CGeoTerrain m_gTerrainLow;
	CGeoTerrain m_gTerrainSand; //Sandausschnitt
	CGeoTerrain m_gTerrainSandMossy;
	CGeoTerrain m_gTerrainRockMossy;
	CGeoTerrain m_gTerrainRock;
	CGeoTerrain m_gTerrainRockSnowy;
	CGeoTerrain m_gWater; //wasserausschnitt
	CGeoTerrain m_gTerrainMirror;

    CPerlin * m_pperlin = nullptr; //Perlin-Noise

    CBlob * m_pblob1 = nullptr; //Erhebung aus dem meer
    CBlob* m_pblob_rest = nullptr; //Artefaktlöschung

    CCut m_cutUnderSea; //Schnitt unter N.N.
    CCut m_cutInverseUnderSea;
    CCut m_cutInverseSand; //strandschnitt
    CCut m_cutInverseSeaToBeach;
    CCut m_cutInverseSandMossy;
    CCut m_cutInverseRockMossy;
    CCut m_cutInverseRock;
    CCut m_cutInverseRockSnowy;

    CCut m_cutInverseUnder15Degrees;
    CCut m_cutUnder15Degrees;
    CCut m_cutInverseUnder45Degrees;
    CCut m_cutUnder45Degrees;
    CCut m_cutInverse15To45Degrees;
    CCut m_cutInverseOver45Degrees;
    CCut m_cutOver45Degrees;

    CMaterial m_mWater;	//Wellenmaterial
    CMaterial m_mSand; //Strandmaterial
    CMaterial m_mSandMossy;
    CMaterial m_mRockMossy; //Erdmaterial
    CMaterial m_mRock;
    CMaterial m_mRockSnow;
    CMaterial m_mMirror;
};

