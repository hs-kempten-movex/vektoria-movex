#include "Forest.h"
#include "Island.h"
#include "ThreadPool.h"

#define CBTREE_SEED 30285

#define CLUSTER_SIZE 250
#define TREES_PER_CLUSTER 20

using namespace Vektoria;


Forest::Forest(CGeoTerrain* terrain)
{
    InitGeos(terrain);

    //TODO find better values
    m_CBTreePlacementLoD1.AddGeo(&m_CBTreeLoD1);
    m_CBTreePlacementLoD1.SetLoD(0.0f, 250.0f);
    m_CBTreePlacementLoD2.AddGeo(&m_CBTreeLoD2);
    m_CBTreePlacementLoD2.SetLoD(250.0f, 750.0f);
    m_CBTreePlacementLoD3.AddGeo(&m_CBTreeLoD3);
    m_CBTreePlacementLoD3.SetLoD(750.0f, 1500.0f);

    m_CBTreePlacement.AddPlacement(&m_CBTreePlacementLoD1);
    m_CBTreePlacement.AddPlacement(&m_CBTreePlacementLoD2);
    m_CBTreePlacement.AddPlacement(&m_CBTreePlacementLoD3);
    m_CBTreePlacement.Scale(3.0f);

    m_poopy.SetRandomSeed(44444);
    m_poopy.Iterate(1.0f, 0.2f, 0.0f);
    m_poopy.Init(&m_poopy, 0);
    m_poopy.DeIterate();

    for (auto& cluster : m_forestClusters)
    {
        AddPlacement(cluster);
        for (auto& plantPlacement : cluster->GetPlantPlacements())
        {
            plantPlacement->AddPlacement(&m_CBTreePlacement);
        }
    }
}

Forest::~Forest()
{
    for (auto& cluster : m_forestClusters)
    {
        delete cluster;
    }
}

void Forest::InitGeos(CGeoTerrain* terrain)
{
    ThreadPool threadPool;
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD1, 1);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD2, 2);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD3, 3);

    std::mutex mutex;
    for (int i = -TERRAIN_SIZE / 2; i < TERRAIN_SIZE; i += CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            threadPool.EnqueueTask(ClusterInit, terrain, CHVector(i, 0, j), &m_forestClusters, &mutex);
        }
    }
}

void Forest::CBTreeInit(CherryBlossomTree* tree, unsigned int lod)
{
    tree->SetRandomSeed(CBTREE_SEED);
    tree->Iterate(150.0f, 0.2f, 0.0f);
    tree->Init(tree, lod);
    tree->DeIterate();
}

void Forest::ClusterInit(CGeoTerrain* terrain, CHVector position, std::vector<ForestCluster*>* clusters, std::mutex* mutex)
{
    ForestCluster* newCluster = new ForestCluster(TREES_PER_CLUSTER, terrain, position, CLUSTER_SIZE);
    mutex->lock();
    clusters->push_back(newCluster);
    mutex->unlock();
}