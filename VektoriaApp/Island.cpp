#include "Island.h"

Island::Island()
{
    //Cuts:
    m_cutUnderSea.Init(
        eCutKind_Height,						//wegschneiden
        -F_MAX, 0,								// von -? bis N.N.
        false,									//invertieren?
        true, true);							//"glattziehen"
    m_cutInverseBeach.Init(eCutKind_Height, 0, TERRAIN_SAND_MAX, true, true, false);
    m_cutInverseBeachToSnow.Init(eCutKind_Height, 0, TERRAIN_HEIGHT, true, true, false);
    m_cutInverseGrass.Init(eCutKind_Height, TERRAIN_SAND_MAX, TERRAIN_HEIGHT, true, false, false);
    //m_cutInverseSnow.Init(eCutKind_Height, TERRAIN_GRASS_MAX, TERRAIN_SNOW_MAX, true, false, false);

    m_cutInverseUnder15Degrees.Init(eCutKind_Steepness, 0.0f, PI / 12.0f, true, false, false);
    m_cutUnder15Degrees.Init(eCutKind_Steepness, 0.0f, PI / 12.0f, false, false, false);

    //Cut dem Terrain hinzufügen:
    m_gTerrain.AddCut(&m_cutUnderSea);
    m_gTerrain.AddCut(&m_cutInverseBeachToSnow);
    m_gTerrainSand.AddCut(&m_cutInverseBeach);
    m_gTerrainSand.AddCut(&m_cutInverseUnder15Degrees);
    m_gTerrainSandMossy.AddCut(&m_cutInverseBeach);
    m_gTerrainSandMossy.AddCut(&m_cutUnder15Degrees);
    m_gTerrainGrass.AddCut(&m_cutInverseGrass);

    //perlin-Noise
    m_pperlin = new CPerlin(
        420,							//zufallsseed
        1.0f,						//Amplitude
        16,							//Oktaven
        0.5f,						//Persistenz
        12.0f,						//Frequenz
        0.0f,						//X-Verschiebung
        0.0f,						//Y-Verschiebung
        ePerlinInterpol_Linear,	//Interpolationsart
        false);						//Repetivität

      //Texturen laden für wasser und land
    m_mWater.LoadPreset("Water");
    m_mWater.SetAni(8, 8, 7);
    m_mWater.Translate(CColor(0.0f, 0.2f, 0.3f));
    m_mWater.SetTransparency(0.9f);
    m_mWater.MakeTextureHaze("textures\\waterHaze.jpg");
    m_mWater.SetPostprocessingOn();
    m_mWater.SetHazeOn();
    m_mWater.SetHazeStrength(1.8);

    m_mSand.LoadPreset("Sand");
    m_mSandMossy.LoadPreset("SandMossy");
    m_mEarthMossy.LoadPreset("RockMossy");

    //blob und perlinnoise mischen
    m_pblob_rest = new CBlob(
        0.5f, 0.5f,					//Mittelpunkt des Blobs (u&v)
        0.51f, 0.51f,					//Radius des Blobs (u&v)
        -1,							//Höhe des Blobs
        eBlobShapeGround_Rect,		//Grundflächentopologie
        eBlobShapeSide_All,			//Höhenverlauftopologie
        nullptr);

    m_pblob1 = new CBlob(
        0.5f, 0.5f,					//Mittelpunkt des Blobs (u&v)
        0.51f, 0.51f,					//Radius des Blobs (u&v)
        TERRAIN_HEIGHT,							//Höhe des Blobs
        eBlobShapeGround_Radial,		//Grundflächentopologie
        eBlobShapeSide_Parabol,			//Höhenverlauftopologie
        m_pperlin);						//Perlin-noise-instanz

      //Blob einem Blaupausen-terrain hinzufügen
    m_gTerrainOri.AddBlob(m_pblob_rest);
    m_gTerrainOri.AddBlob(m_pblob1);

    //Vertex-Daten aus blaupausen-terrain erzeugen
    m_gTerrainOri.CreateField(
        TERRAIN_SIZE, TERRAIN_SIZE,							//ein Quadratkilomenter Terrain
        TERRAIN_VERTICES, TERRAIN_VERTICES,					//2000 x 2000 vertices
        0.0f, 0.0f,											//UV-textur beginnt bei (0,0)
        1.0f, 1.0f);										//geht bis (1,1)

      //Abschnitte erstellen
    m_gTerrain.InitFromOther(m_gTerrainOri, &m_mEarthMossy);
    m_gTerrainSand.InitFromOther(m_gTerrainOri, &m_mSand);
    m_gTerrainSandMossy.InitFromOther(m_gTerrainOri, &m_mSandMossy);
    m_gTerrainGrass.InitFromOther(m_gTerrainOri, &m_mEarthMossy);

    //wasseroberfläche erzeugen:
    m_gWater.Init(
        70000, 70000,	//Großes Meer (70*70qm)
        &m_mWater,		//bewegtes wassermaterial
        10, 10,			//nur wenig polygone 
        0.0f, 0.0f,		//keine UV-verschiebung
        500.0f,			//500 mal wiederholen
        500.0f);		//in jeder Richtung

      //Geos an placement hängen:
    m_pIsland1.AddGeo(&m_gTerrain);
    m_pIsland1.AddGeo(&m_gWater);
    m_pIsland1.AddGeo(&m_gTerrainSand);
    m_pIsland1.AddGeo(&m_gTerrainSandMossy);
    m_pIsland1.AddGeo(&m_gTerrainGrass);

    //Terrain zu kollisionscontainer:
    m_gsTerrain.Add(&m_gTerrain);
}

Island::~Island() {
    delete m_pperlin;
    delete m_pblob1;
    delete m_pblob_rest;
}
