#pragma once

#include "Vektoria\Root.h"
using namespace Vektoria;

#define TERRAIN_SIZE 2500
#define TERRAIN_VERTICES 1001
#define LOD_DIVISOR 8
#define TERRAIN_HEIGHT 500
#define TERRAIN_SAND_MAX 3
#define TERRAIN_SANDLESSMOSSY_MAX 5
#define TERRAIN_SAND_MOSSY_MAX 8
#define TERRAIN_ROCK_MOSSY_MAX 130
#define TERRAIN_ROCK_MAX 500
#define TERRAIN_ROCK_SNOWY_MIN 130
#define TERRAIN_ROCK_SNOWY_MAX 500
#define PERLINE_SEED_MAX 1000000.0f
#define SEED_ARRAY_SIZE 20

class Island
{
public:
    Island();
    ~Island();

    CGeos m_gsCol, m_gsHeight; //Kollisionscontainer

    CPlacement m_pIsland1; //insel- wasserplacement
    CPlacement m_pIsland_Billboards;
    CPlacement m_pIsland2; //background insel 1
    CPlacement m_pIsland3; //background insel 2
    CPlacement m_pIsland3Water;
    CPlacement m_pIsland4; //background insel 3
    CPlacement m_pIsland4Water;

    CGeoTerrain m_gTerrainOri; //Gesamtes Terrain
    CGeoTerrain m_gWater; //wasserausschnitt

    CGeoTerrain m_gTerrainSand; //Sandausschnitt
    CGeoTerrain m_gTerrainRock;
    CGeoTerrain m_gTerrainRockSnowy;
    CGeoTerrain m_gTerrainMirror;
	/*ben�tigt f�r wald*/
    CGeoTerrain m_gTerrainSandMossy;
    CGeoTerrain m_gTerrainRockMossy;
    CGeoTerrain m_gTerrainSandLessMossy;

    //background insel billboards
    CGeoQuad m_gqIslandBillboard1;
    CGeoQuad m_gqIslandWaterBillboard1;
    CMaterial m_mIslandBill1;
    CMaterial m_mIslandWaterBill1;
    CGeoQuad m_gqIslandBillboard2;
    CGeoQuad m_gqIslandWaterBillboard2;
    CMaterial m_mIslandBill2;
    CMaterial m_mIslandWaterBill2;

private:
    CPerlin * m_pperlin = nullptr; //Perlin-Noise
    CPerlin * m_pperlinBack = nullptr; 

    CBlob * m_pblob1 = nullptr; //Erhebung aus dem meer
    CBlob * m_pblobBack = nullptr;
    CBlob * m_pblob_rest = nullptr; //Artefaktl�schung

    CCut m_cutUnderSea; //Schnitt unter N.N.
    CCut m_cutInverseUnderSea;
    CCut m_cutInverseSand; //strandschnitt
    CCut m_cutInverseSeaToBeach;
    CCut m_cutInverseSandLessMossy;
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
    CMaterial m_mSandLessMossy;
    CMaterial m_mSandMossy;
    CMaterial m_mRockMossy; //Erdmaterial
    CMaterial m_mRock;
    CMaterial m_mRockSnow;
    CMaterial m_mMirror;

    CMaterial m_mGround;

    CRandom m_RandomSeed;
    int Random_Seed();
    int m_aiSeed[SEED_ARRAY_SIZE];
    int m_iRandomSlot;
    int m_iSeed;
};

