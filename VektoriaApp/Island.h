#pragma once

#include "Vektoria\Root.h"
using namespace Vektoria;

#define TERRAIN_SIZE 1000
#define TERRAIN_VERTICES 2000
#define TERRAIN_HEIGHT 350
#define TERRAIN_SAND_MAX 12
#define TERRAIN_GRASS_MAX 150
#define TERRAIN_SNOW_MAX 300

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
    CGeoTerrain m_gTerrainSand; //Sandausschnitt
    CGeoTerrain m_gTerrainSandMossy;
    CGeoTerrain m_gWater; //wasserausschnitt
    CGeoTerrain m_gTerrainGrass; //Grasausschnitt

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
};

