#include "Forest.h"
#include "../Island.h"
#include "../Utils/ThreadPool.h"

#define CLUSTER_SIZE 250
#define TREES_PER_CLUSTER 20

using namespace Vektoria;
using namespace ForestNS;
using namespace UtilsNS;
//TODO dejans bäume holen und einfügen
Forest::Forest(CGeoTerrain* terrain)
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

    m_zpCherryBlossomTree.InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 3 }, { 1500.0f, 4 } } }, &threadPool);
    m_zpCherryBlossomTree.InitCollisionGeo(&threadPool);
    m_zpCherryBlossomTree.Scale(1.1f);

    m_zpPoppy.InitLoDs({ { {100.0f, 0}, { 500.0f, 1 }, { 1000.0f, 2 } } }, &threadPool);
    m_zpPoppy.Scale(1.5f);

    m_zpConifer.InitLoDs({ { {100.0f, 1}, { 500.0f, 2 }, { 1000.0f, 3 }, { 1500.0f, 4 } } }, &threadPool);
    m_zpConifer.Scale(3.5f);

    InitCluster(terrain);
}


void Forest::InitCluster(CGeoTerrain* terrain)
{
    for (int i = -TERRAIN_SIZE / 2; i < TERRAIN_SIZE; i += CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            ForestCluster* newCluster = new ForestCluster(terrain, CHVector(i, 0, j), CLUSTER_SIZE);
            newCluster->AddPlacementsForSpecies(&m_zpCherryBlossomTree, TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI); //cherrytrees höhe wo sie wachsen dürfen, abhang etc
            newCluster->AddPlacementsForSpecies(&m_zpConifer, TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI);
            
            std::vector<CPlacement*> poppyPlacements = newCluster->AddPlacementsForSpecies(&m_zpPoppy, TREES_PER_CLUSTER, 10.0, 130.0f);
            
            AddPlacement(newCluster);
            m_forestClusters.push_back(newCluster);
            
            m_flowers.insert(m_flowers.end(), poppyPlacements.begin(), poppyPlacements.end());
        }
    }
}