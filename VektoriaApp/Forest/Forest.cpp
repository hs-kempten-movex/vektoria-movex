#include "Forest.h"
#include "../Island.h"
#include "../Utils/ThreadPool.h"

#define CLUSTER_SIZE 200
#define TREES_PER_CLUSTER 15

using namespace Vektoria;
using namespace ForestNS;
using namespace UtilsNS;
ForestNS::Forest::Forest(unsigned int seed)
{
    m_random.SRand(seed);
}
//TODO dejans b�ume holen und einf�gen
Forest::Forest(unsigned int seed, CGeoTerrain* terrain) :
    Forest(seed)
{
    Init(terrain);
}

Forest::~Forest()
{
    for (auto& cluster : m_forestClusters)
    {
        delete cluster;
    }
}

void ForestNS::Forest::Init(CGeoTerrain * terrain)
{
    ThreadPool threadPool(4);

    for (auto &zpCherryBlossomTree : m_zpCherryBlossomTrees)
    {
        zpCherryBlossomTree = new PlantPlacement<CherryBlossomTree, 4>(m_random.Rand(), m_random.RandFr() * 150.0f, 0.2f, 0.0f);
        zpCherryBlossomTree->InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 4 }, { 1500.0f, 5 } } }, &threadPool);
        zpCherryBlossomTree->Scale(2.0f);

        zpCherryBlossomTree->InitCollisionGeo(&threadPool);
        m_collisionGeos.push_back(&zpCherryBlossomTree->GetCollisionGeo());
    }

    for (auto& zpConifer : m_zpConifers)
    {
        zpConifer = new PlantPlacement<Nadelbaum, 4>(m_random.Rand(), m_random.RandFr() * 300.0f, 0.2f, 0.0f);
        zpConifer->InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 4 }, { 1500.0f, 5 } } }, &threadPool);
        zpConifer->Scale(3.5f);

        zpConifer->InitCollisionGeo(&threadPool);
        m_collisionGeos.push_back(&zpConifer->GetCollisionGeo());
    }

    for (auto& zpAsiaTree : m_zpAsiaTrees)
    {
        zpAsiaTree = new PlantPlacement<CGeoBioAsianTree, 3>(m_random.Rand(), m_random.RandFr() * 300.0f, 0.2f, 0.0f);
        zpAsiaTree->InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 4 } } }, &threadPool);
        zpAsiaTree->Scale(2.0f);

        zpAsiaTree->InitCollisionGeo(&threadPool);
        m_collisionGeos.push_back(&zpAsiaTree->GetCollisionGeo());
    }

    for (auto& zpPoppy : m_zpPoppies)
    {
        zpPoppy = new PlantPlacement<GeoBioPoppy, 3>(m_random.Rand(), m_random.RandFr(), 0.2f, 0.0f);
        zpPoppy->InitLoDs({ { {100.0f, 0}, { 500.0f, 1 }, { 1000.0f, 2 } } }, &threadPool);
        zpPoppy->Scale(1.5f);
    }

    for (auto& zpJapanischerSchildfarn : m_zpJapanischeSchildfarne)
    {
        zpJapanischerSchildfarn = new PlantPlacement<GeoBioJapanischerSchildfarn, 3>(m_random.Rand(), m_random.RandFr(), 0.2f, 0.0f);
        zpJapanischerSchildfarn->InitLoDs({ { {100.0f, 0}, { 500.0f, 1 }, { 1000.0f, 2 } } }, &threadPool);
        zpJapanischerSchildfarn->Scale(1.5f);
    }

    CFileWavefront objLoader;
    m_zgBarrel = objLoader.LoadGeo("models\\Barrel.obj", true);
    m_zpBarrel.AddGeo(m_zgBarrel);
    m_zpBarrel.SetLoD(0.0f, 500.0f);
    m_zpBarrel.TranslateYDelta(1.0f);
    m_zpBarrel.RotateX(QUARTERPI);
    m_zgBarrel->SetMaterial(& m_zmBarrel);
    m_zmBarrel.MakeTextureDiffuse("textures\\clutter\\BarrelDiffuseTex.png");
    m_zmBarrel.MakeTextureBump("textures\\clutter\\BarrelNormalTex.jpg");
    m_zmBarrel.MakeTextureSpecular("textures\\clutter\\BarrelSpecularTex.png");

    m_zgChest = objLoader.LoadGeo("models\\Chest.obj", true);
    m_zpChest.AddGeo(m_zgChest);
    m_zpChest.SetLoD(0.0f, 500.0f);
    m_zpChest.TranslateYDelta(-0.1f);
    m_zgChest->SetMaterial(&m_zmChest);
    m_zmChest.MakeTextureDiffuse("textures\\clutter\\ChestDiffuseTex.jpg");
    m_zmChest.MakeTextureBump("textures\\clutter\\ChestNormalTex.jpg");
    m_zmChest.MakeTextureSpecular("textures\\clutter\\ChestSpecularTex.jpg");

    m_zgStone = objLoader.LoadGeo("models\\Stone01.obj", true);
    m_zpStone.AddGeo(m_zgStone);
    m_zpStone.SetLoD(0.0f, 500.0f);
    m_zgStone->SetMaterial(&m_zmStone);
    m_zmStone.MakeTextureDiffuse("textures\\clutter\\Stone01DiffuseTex.jpg");
    m_zmStone.MakeTextureBump("textures\\clutter\\Stone01NormalTex.jpg");
    m_zmStone.MakeTextureSpecular("textures\\clutter\\Stone01SpecularTex.jpg");


    m_zgPadogaBase = objLoader.LoadGeo("models\\PadogaBase.obj", true);
    m_zgPadogaSupport = objLoader.LoadGeo("models\\PadogaSupport.obj", true);
    m_zgPadogaRoof = objLoader.LoadGeo("models\\PadogaRoof.obj", true);
    m_zgPadogaBase->SetMaterial(&m_zmPadogaBase);
    m_zgPadogaSupport->SetMaterial(&m_zmPadogaSupport);
    m_zgPadogaRoof->SetMaterial(&m_zmPadogaRoof);

    m_zpPadoga.AddGeo(m_zgPadogaBase);
    m_zpPadoga.AddGeo(m_zgPadogaSupport);
    m_zpPadoga.AddGeo(m_zgPadogaRoof);

    m_zmPadogaBase.MakeTextureDiffuse("textures\\clutter\\PadogaBaseDiffuseTex.png");
    m_zmPadogaBase.MakeTextureBump("textures\\clutter\\PadogaBaseNormalTex.png");
    m_zmPadogaBase.MakeTextureSpecular("textures\\clutter\\PadogaBaseSpecluarTex.png");
    m_zmPadogaSupport.MakeTextureDiffuse("textures\\clutter\\PadogaSupportsDiffuse.jpg");
    m_zmPadogaRoof.MakeTextureDiffuse("textures\\clutter\\PadogaRoofDiffuseTex.png");
    m_zmPadogaRoof.MakeTextureBump("textures\\clutter\\PadogaRoofNormalTex.png");
    m_zmPadogaRoof.MakeTextureSpecular("textures\\clutter\\PadogaRoofSpecularTex.png");




    InitCluster(terrain);
}


void Forest::InitCluster(CGeoTerrain* terrain)
{
    for (int i = -TERRAIN_SIZE / 2; i < TERRAIN_SIZE; i += CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            ForestCluster* newCluster = new ForestCluster(m_random.Rand(), terrain, CHVector(i, 0, j), CLUSTER_SIZE);
            AddPlacement(newCluster);
            m_forestClusters.push_back(newCluster);

            for (auto& zpCherryBlossomTree : m_zpCherryBlossomTrees)
            {
                newCluster->AddPlacementsForSpecies(zpCherryBlossomTree, TREES_PER_CLUSTER, 10.0f, 75.0f, 0.0f, QUARTERPI); //cherrytrees h�he wo sie wachsen d�rfen, abhang etc
            }

            for (auto& zpConifer : m_zpConifers)
            {
                newCluster->AddPlacementsForSpecies(zpConifer, TREES_PER_CLUSTER, 55.0f, F_MAX, 0.0f, QUARTERPI);
            }

            for (auto& zpAsiaTree : m_zpAsiaTrees)
            {
                newCluster->AddPlacementsForSpecies(zpAsiaTree, TREES_PER_CLUSTER, 10.0f, 75.0f, 0.0f, QUARTERPI);
            }           
            
            for (auto& zpPoppy : m_zpPoppies)
            {
                auto newPoppies = newCluster->AddPlacementsForSpecies(zpPoppy, TREES_PER_CLUSTER, 10.0, 130.0f);
                m_zpFlowers.insert(m_zpFlowers.end(), newPoppies.begin(), newPoppies.end());
            }

            for (auto& zpJapanischerSchildfarn : m_zpJapanischeSchildfarne)
            {
                auto newJapanischeSchildfarne = newCluster->AddPlacementsForSpecies(zpJapanischerSchildfarn, TREES_PER_CLUSTER, 10.0, 130.0f);
                m_zpFlowers.insert(m_zpFlowers.end(), newJapanischeSchildfarne.begin(), newJapanischeSchildfarne.end());
            }            

            newCluster->AddPlacementsForSpecies(&m_zpBarrel, TREES_PER_CLUSTER, 0.0, 40.0f, 0.0f, 0.5236f); //Adds Random Barrels to Island
            newCluster->AddPlacementsForSpecies(&m_zpChest, TREES_PER_CLUSTER, 0.0, 40.0f, 0.0f, 0.5236f); //Adds Random Chests to Island
            newCluster->AddPlacementsForSpecies(&m_zpStone, TREES_PER_CLUSTER * 2, 0.0f, 1000.0f, 0.0f, QUARTERPI, TWOPI, 0.5f, 4.0f);
            newCluster->AddPlacementsForSpecies(&m_zpPadoga, TREES_PER_CLUSTER, 0.0, 100.0f, 0.0f, 0.5236f); //Adds Padogas
        }
    }
}