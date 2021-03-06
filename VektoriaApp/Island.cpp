#include "Island.h"

Island::Island()
{
    //Cuts:
    m_cutUnderSea.Init(
        eCutKind_Height,						//wegschneiden
        -F_MAX, 0,								// von -? bis N.N.
        false,									//invertieren?
        true, true);							//"glattziehen"
    m_cutInverseSand.Init(eCutKind_Height, 0, TERRAIN_SAND_MAX, true, true, false);
    m_cutInverseSandLessMossy.Init(eCutKind_Height, 0, TERRAIN_SANDLESSMOSSY_MAX, true, true, false);
    m_cutInverseSandMossy.Init(eCutKind_Height, 0, TERRAIN_SAND_MOSSY_MAX, true, true, false); //Terrainsandmossy
    m_cutInverseSeaToBeach.Init(eCutKind_Height, 0, TERRAIN_SAND_MOSSY_MAX, true, true, false); //terrainlow
    m_cutInverseRockMossy.Init(eCutKind_Height, TERRAIN_SAND_MOSSY_MAX, TERRAIN_ROCK_MOSSY_MAX, true, false, false);
    m_cutInverseRock.Init(eCutKind_Height, 0, TERRAIN_ROCK_MAX, true, true, false);
    m_cutInverseRockSnowy.Init(eCutKind_Height, TERRAIN_ROCK_SNOWY_MIN, TERRAIN_ROCK_SNOWY_MAX, true, false, false);
    m_cutInverseUnderSea.Init(eCutKind_Height, -F_MAX, 0.0f, true, false, true);

    m_cutInverseUnder15Degrees.Init(eCutKind_Steepness, 0.0f, PI / 12.0f, true, true, false);
    m_cutUnder15Degrees.Init(eCutKind_Steepness, 0.0f, PI / 12.0f, false, false, false);
    m_cutInverseUnder45Degrees.Init(eCutKind_Steepness, 0, QUARTERPI, true, true, false);
    m_cutUnder45Degrees.Init(eCutKind_Steepness, 0, QUARTERPI, false, true, false);
    m_cutInverse15To45Degrees.Init(eCutKind_Steepness, PI / 12.0f, QUARTERPI, true, true, false);
    m_cutInverseOver45Degrees.Init(eCutKind_Steepness, QUARTERPI, PI, true, false, false);
    m_cutOver45Degrees.Init(eCutKind_Steepness, QUARTERPI, PI, false, false, false);

    //Cut dem Terrain hinzufügen:

    m_gTerrainSand.AddCut(&m_cutInverseSand);
    m_gTerrainSand.AddCut(&m_cutInverseUnder15Degrees);

    m_gTerrainSandLessMossy.AddCut(&m_cutInverseSandLessMossy);
    m_gTerrainSandLessMossy.AddCut(&m_cutInverseUnder15Degrees);

    m_gTerrainSandMossy.AddCut(&m_cutInverseSeaToBeach);
    m_gTerrainSandMossy.AddCut(&m_cutInverseUnder45Degrees);

    m_gTerrainRockMossy.AddCut(&m_cutInverseRockMossy);
    m_gTerrainRockMossy.AddCut(&m_cutOver45Degrees);

    m_gTerrainRock.AddCut(&m_cutInverseRock);
    m_gTerrainRock.AddCut(&m_cutInverseOver45Degrees);

    m_gTerrainRockSnowy.AddCut(&m_cutInverseRockSnowy);
    m_gTerrainRockSnowy.AddCut(&m_cutInverseUnder45Degrees);

    m_gTerrainMirror.AddCut(&m_cutInverseUnderSea);

    //Zufalls Seeds: { 84066, 90083, 1006, 16402, 12345, 54321, 6542, 24268, 36232, 25287, 7563, 6435, 7431, 87643, 64413, 81345, 84345, 43254, 45378, 7531 }

    //perlin-Noise
    m_pperlin = new CPerlin(
        Random_Seed(),							//zufallsseed
        1.75f,						//Amplitude
        16,							//Oktaven
        0.5f,						//Persistenz
        12.0f,						//Frequenz
        0.0f,						//X-Verschiebung
        0.0f,						//Y-Verschiebung
        ePerlinInterpol_Linear,	//Interpolationsart
        false);						//Repetivität

    m_pperlinBack = new CPerlin(422, 1.75f, 16, 0.5f, 12.0f, 0.0f, 0.0f, ePerlinInterpol_Linear, false);

      //Texturen laden für wasser und land
    //m_mWater.LoadPreset("Water");
    //m_mWater.MakeTextureEnvironment("textures\\ENF_Water.png");
    m_mWater.MakeTextureDiffuse("textures\\Water_albedo.jpg");
    m_mWater.MakeTextureBump("textures\\Water_Normal.png");
    m_mWater.SetBumpStrength(2.0);
    m_mWater.MakeTextureHaze("textures\\waterHaze.jpg");
    m_mWater.SetAni(8, 8, 7);
    //m_mWater.Translate(CColor(0.0f, 0.2f, 0.8f));
    m_mWater.SetTransparency(0.7f);
    m_mWater.SetPostprocessingOn();
    m_mWater.SetHazeOn();
    m_mWater.SetHazeStrength(3.0);

    //m_mSand.LoadPreset("Sand");
    m_mSand.MakeTextureDiffuse("textures\\Sand2_basecolor.png");
    m_mSand.MakeTextureBump("textures\\Sand2_normal.png");
    m_mSand.SetBumpStrength(2.0);
    m_mSand.MakeTextureHeight("textures\\Sand2_height.png");
    m_mSand.SetHeightStrength(1.0);
    m_mSand.MakeTextureSpecular("textures\\Ground_specular.png");

    m_mSandLessMossy.MakeTextureDiffuse("textures\\SandLessMossy2_basecolor.png");
    m_mSandLessMossy.MakeTextureBump("textures\\SandLessMossy2_normal.png");
    m_mSandLessMossy.SetBumpStrength(2.0);
    m_mSandLessMossy.MakeTextureHeight("textures\\SandLessMossy2_height.png");
    m_mSandLessMossy.SetHeightStrength(1.0);
    m_mSandLessMossy.MakeTextureSpecular("textures\\Ground_specular.png");

    //m_mSandMossy.LoadPreset("SandMossy");
    m_mSandMossy.MakeTextureDiffuse("textures\\SandVeryMossy2_basecolor.png");
    m_mSandMossy.MakeTextureBump("textures\\SandVeryMossy2_normal.png");
    m_mSandMossy.SetBumpStrength(2.0);
    m_mSandMossy.MakeTextureHeight("textures\\SandVeryMossy2_height.png");
    m_mSandMossy.SetHeightStrength(1.0);
    m_mSandMossy.MakeTextureSpecular("textures\\Ground_specular.png");

    m_mRockMossy.LoadPreset("RockMossy");

    //m_mRock.LoadPreset("Rock");
    m_mRock.MakeTextureDiffuse("textures\\Felsen_basecolor.png");
    m_mRock.MakeTextureBump("textures\\Felsen_normal.png");
    m_mRock.SetBumpStrength(2.0);
    m_mRock.MakeTextureHeight("textures\\Felsen_height.png");
    m_mRock.SetHeightStrength(1.0);
    m_mRock.MakeTextureSpecular("textures\\Felsen_specular.png");

    //m_mRockSnow.LoadPreset("RockSnowy");
    m_mRockSnow.MakeTextureDiffuse("textures\\Snow_basecolor.png");
    m_mRockSnow.MakeTextureBump("textures\\Snow_normal.png");
    m_mRockSnow.SetBumpStrength(2.0);
    m_mRockSnow.MakeTextureHeight("textures\\Snow_height.png");
    m_mRockSnow.SetHeightStrength(2.0);
    m_mRockSnow.MakeTextureSpecular("textures\\Felsen_specular.png");
    m_mRockSnow.SetSpecularStrength(2.0);

    m_mGround.MakeTextureDiffuse("textures\\Ground_basecolor.png");
    m_mGround.MakeTextureBump("textures\\Ground_normal.png");
    m_mGround.SetBumpStrength(2.0);
    m_mGround.MakeTextureHeight("textures\\Ground_height.png");
    m_mGround.SetHeightStrength(1.0);
    m_mGround.MakeTextureSpecular("textures\\Ground_specular.png");

    m_mMirror.LoadPreset("RockMossy");

    //blob und perlinnoise mischen
    m_pblob_rest = new CBlob(
        0.5f, 0.5f,					//Mittelpunkt des Blobs (u&v)
        0.51f, 0.51f,					//Radius des Blobs (u&v)
        -7,							//Höhe des Blobs
        eBlobShapeGround_Rect,		//Grundflächentopologie
        eBlobShapeSide_All,			//Höhenverlauftopologie
        nullptr);

    m_pblob1 = new CBlob(0.5f, 0.5f, 0.5f, 0.5f, TERRAIN_HEIGHT, eBlobShapeGround_Radial, eBlobShapeSide_Hill, m_pperlin);
    m_pblobBack = new CBlob(0.5f, 0.5f, 0.5f, 0.5f, TERRAIN_HEIGHT, eBlobShapeGround_Radial, eBlobShapeSide_Hill, m_pperlinBack);

      //Blob einem Blaupausen-terrain hinzufügen
    m_gTerrainOri.AddBlob(m_pblob_rest);
    m_gTerrainOri.AddBlob(m_pblob1);

    //Vertex-Daten aus blaupausen-terrain erzeugen
    m_gTerrainOri.CreateField(
        TERRAIN_SIZE, TERRAIN_SIZE,							//ein Quadratkilomenter Terrain
        TERRAIN_VERTICES, TERRAIN_VERTICES,					//2000 x 2000 vertices
        0.0f, 0.0f,											//UV-textur beginnt bei (0,0)
        100.0f, 100.0f);										//geht bis (1,1)

      //Abschnitte erstellen
    m_gTerrainSand.InitFromOther(m_gTerrainOri, &m_mSand);
    m_gTerrainSandLessMossy.InitFromOther(m_gTerrainOri, &m_mSandLessMossy);
    m_gTerrainSandMossy.InitFromOther(m_gTerrainOri, &m_mSandMossy);
    m_gTerrainRockMossy.InitFromOther(m_gTerrainOri, &m_mGround);           //eigenes materia, fehlerhaft
    m_gTerrainRock.InitFromOther(m_gTerrainOri, &m_mRock);
    m_gTerrainRockSnowy.InitFromOther(m_gTerrainOri, &m_mRockSnow);
    m_gTerrainMirror.InitFromOther(m_gTerrainOri, &m_mMirror, true);

    //wasseroberfläche erzeugen:
    m_gWater.Init(
        70000, 70000,	//Großes Meer (70*70qm)
        &m_mWater,		//bewegtes wassermaterial
        10, 10,			//nur wenig polygone 
        0.0f, 0.0f,		//keine UV-verschiebung
        500.0f,			//500 mal wiederholen
        500.0f);		//in jeder Richtung

    //Geos an placement hängen:
    m_pIsland1.AddGeo(&m_gWater);
    m_pIsland1.AddGeo(&m_gTerrainSand);
    m_pIsland1.AddGeo(&m_gTerrainSandLessMossy);
    m_pIsland1.AddGeo(&m_gTerrainSandMossy);
    m_pIsland1.AddGeo(&m_gTerrainRockMossy);
    m_pIsland1.AddGeo(&m_gTerrainRock);
    m_pIsland1.AddGeo(&m_gTerrainRockSnowy);
    m_pIsland1.AddGeo(&m_gTerrainMirror);

    //InselBillboards für den Hintergrund

    m_mIslandBill1.MakeTextureSprite("textures\\Insel_4_Bill_Land.png");
    m_mIslandBill1.SetChromaKeyingOn();
    m_gqIslandBillboard1.Init(1000.0, &m_mIslandBill1, 0.0, 0.0, 1.0, 1.0);
    m_mIslandWaterBill1.MakeTextureSprite("textures\\Insel_4_Bill_Water.png");
    m_mIslandWaterBill1.SetTransparencyOn();
    m_gqIslandWaterBillboard1.Init(1000.0, &m_mIslandWaterBill1, 0.0, 0.0, 1.0, 1.0);

    m_mIslandBill2.MakeTextureSprite("textures\\Insel_3_Bill_Land.png");
    m_mIslandBill2.SetChromaKeyingOn();
    m_gqIslandBillboard2.Init(1000.0, &m_mIslandBill2, 0.0, 0.0, 1.0, 1.0);
    m_mIslandWaterBill2.MakeTextureSprite("textures\\Insel_3_Bill_Water.png");
    m_mIslandWaterBill2.SetTransparencyOn();
    m_gqIslandWaterBillboard2.Init(1000.0, &m_mIslandWaterBill2, 0.0, 0.0, 1.0, 1.0);

    m_pIsland3.AddGeo(&m_gqIslandBillboard1);
    m_pIsland3.TranslateDelta(-3000, 120, 2500);
    m_pIsland3.SetBillboardY();
    m_pIsland3.SetBillboardScaling(1.0f, 0.125f);
    m_pIsland3.FixDistance(3.0f);
    m_pIsland3Water.AddGeo(&m_gqIslandWaterBillboard1);
    m_pIsland3Water.TranslateDelta(-3000, -100, 2500);
    m_pIsland3Water.SetBillboardY();
    m_pIsland3Water.SetBillboardScaling(1.0f, 0.1f);
    m_pIsland3Water.FixDistance(1000.0);

    m_pIsland4.AddGeo(&m_gqIslandBillboard2);
    m_pIsland4.TranslateDelta(-3000, 120, -2000);
    m_pIsland4.SetBillboardY();
    m_pIsland4.SetBillboardScaling(1.0f, 0.125f);
    m_pIsland4.FixDistance(3.0f);
    m_pIsland4Water.AddGeo(&m_gqIslandWaterBillboard2);
    m_pIsland4Water.TranslateDelta(-3000, -100, -2000);
    m_pIsland4Water.SetBillboardY();
    m_pIsland4Water.SetBillboardScaling(1.0f, 0.1f);
    m_pIsland4Water.FixDistance(1000.0);

    //Billboards an Placements anhängen
    m_pIsland_Billboards.AddPlacement(&m_pIsland3);
    m_pIsland_Billboards.AddPlacement(&m_pIsland3Water);
    m_pIsland_Billboards.AddPlacement(&m_pIsland4);
    m_pIsland_Billboards.AddPlacement(&m_pIsland4Water);

    //collision detection
    m_gTerrainOri.InitFromOther(m_gTerrainOri, NULL);
    m_pIsland1.AddGeo(&m_gTerrainOri);
    m_gTerrainOri.SetDrawingOff();
}

int Island::Random_Seed() {
    int m_aiSeed[SEED_ARRAY_SIZE] = { 84066, 90083, 1006, 16402, 12345, 54321, 6542, 24268, 36232, 25287, 7563, 6435, 7431, 87643, 64413, 81345, 84345, 43254, 45378, 7531 };
    m_RandomSeed.SRand(time(NULL));
    m_iRandomSlot = m_RandomSeed.Rand() % SEED_ARRAY_SIZE;
    return m_iSeed = m_aiSeed[m_iRandomSlot];
}

Island::~Island() {
    delete m_pperlin;
    delete m_pperlinBack;
    delete m_pblob1;
    delete m_pblobBack;
    delete m_pblob_rest;
}
