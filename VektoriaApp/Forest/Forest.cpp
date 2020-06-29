#include "Forest.h"
#include "../Island.h"
#include "../Utils/ThreadPool.h"

#define CLUSTER_SIZE 200
#define TREES_PER_CLUSTER 20

using namespace Vektoria;
using namespace ForestNS;
using namespace UtilsNS;
ForestNS::Forest::Forest(unsigned int seed)
{
    m_random.SRand(seed);
}
//TODO dejans bäume holen und einfügen
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
        zpCherryBlossomTree->InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 3 }, { 1500.0f, 4 } } }, &threadPool);
        zpCherryBlossomTree->Scale(1.1f);

        zpCherryBlossomTree->InitCollisionGeo(&threadPool);
        m_collisionGeos.push_back(&zpCherryBlossomTree->GetCollisionGeo());
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

    m_zpConifer.InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 3 }, { 1500.0f, 4 } } }, &threadPool);
    m_zpConifer.Scale(3.5f);

    CFileWavefront objLoader;
    m_zgBarrel = objLoader.LoadGeo("models\\Barrel.obj", true);
    m_zpBarrel.AddGeo(m_zgBarrel);
    m_zpBarrel.TranslateYDelta(1.0f);
    m_zpBarrel.RotateX(QUARTERPI);
    m_zgBarrel->SetMaterial(& m_zmBarrel);
    m_zmBarrel.MakeTextureDiffuse("textures\\clutter\\BarrelDiffuseTex.png");
    m_zmBarrel.MakeTextureBump("textures\\clutter\\BarrelNormalTex.jpg");
    m_zmBarrel.MakeTextureSpecular("textures\\clutter\\BarrelSpecularTex.png");

    InitCluster(terrain);
}


void Forest::InitCluster(CGeoTerrain* terrain)
{
    for (int i = -TERRAIN_SIZE / 2; i < TERRAIN_SIZE; i += CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            ForestCluster* newCluster = new ForestCluster(m_random.Rand(), terrain, CHVector(i, 0, j), CLUSTER_SIZE);
            for (auto& zpCherryBlossomTree : m_zpCherryBlossomTrees)
            {
                newCluster->AddPlacementsForSpecies(zpCherryBlossomTree, TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI); //cherrytrees höhe wo sie wachsen dürfen, abhang etc
            }

            newCluster->AddPlacementsForSpecies(&m_zpConifer, TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI);

            newCluster->AddPlacementsForSpecies(&m_zpBarrel, TREES_PER_CLUSTER, 0.0, 40.0f, 0.0f, 0.5236f);
            
            std::vector<CPlacement*> poppyPlacements;
            for (auto& zpPoppy : m_zpPoppies)
            {
                auto newPoppies = newCluster->AddPlacementsForSpecies(zpPoppy, TREES_PER_CLUSTER, 10.0, 130.0f);
                poppyPlacements.insert(poppyPlacements.end(), newPoppies.begin(), newPoppies.end());
            }
            std::vector<CPlacement*> japanischerSchildfarnPlacements;
            for (auto& zpJapanischerSchildfarn : m_zpJapanischeSchildfarne)
            {
                auto newJapanischeSchildfarne = newCluster->AddPlacementsForSpecies(zpJapanischerSchildfarn, TREES_PER_CLUSTER, 10.0, 130.0f);
                japanischerSchildfarnPlacements.insert(japanischerSchildfarnPlacements.end(), newJapanischeSchildfarne.begin(), newJapanischeSchildfarne.end());
            }
            
            AddPlacement(newCluster);
            m_forestClusters.push_back(newCluster);
            
            m_zpFlowers.insert(m_zpFlowers.end(), poppyPlacements.begin(), poppyPlacements.end());
            m_zpFlowers.insert(m_zpFlowers.end(), japanischerSchildfarnPlacements.begin(), japanischerSchildfarnPlacements.end());
        }
    }
}