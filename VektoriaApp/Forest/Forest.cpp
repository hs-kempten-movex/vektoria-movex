#include "Forest.h"
#include "../Island.h"
#include "../ThreadPool.h"

#define CBTREE_SEED 30285
#define NBTREE_SEED 29486
#define POPPY_SEED 44444

#define CLUSTER_SIZE 250
#define TREES_PER_CLUSTER 20

using namespace Vektoria;
using namespace ForestNS;
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
    InitGeos(terrain);

    m_CBTreePlacementLoD1.AddGeo(&m_CBTreeLoD1);
    m_CBTreePlacementLoD1.SetLoD(0.0f, 100.0f);
    m_CBTreePlacementLoD2.AddGeo(&m_CBTreeLoD2);
    m_CBTreePlacementLoD2.SetLoD(100.0f, 500.0f);
    m_CBTreePlacementLoD3.AddGeo(&m_CBTreeLoD3);
    m_CBTreePlacementLoD3.SetLoD(500.0f, 1000.0f);
    m_CBTreePlacementLoD4.AddGeo(&m_CBTreeLoD4);
    m_CBTreePlacementLoD4.SetLoD(1000.0f, 1500.0f);
    m_CbTreePlacementCollision.AddGeo(&m_CBTreeCollision);
    //m_CbTreePlacementCollision.SetLoD(0.0, 50.0f); // Seems like this causes exceptions with collision detections
    m_CbTreePlacementCollision.SetDrawingOff(); // Dont show collision objects
    m_CbTreePlacementCollision.Scale(1.1f);

    m_plants[0].AddPlacement(&m_CBTreePlacementLoD1);
    m_plants[0].AddPlacement(&m_CBTreePlacementLoD2);
    m_plants[0].AddPlacement(&m_CBTreePlacementLoD3);
    m_plants[0].AddPlacement(&m_CBTreePlacementLoD4);
    m_plants[0].AddPlacement(&m_CbTreePlacementCollision);
    m_plants[0].Scale(2.0f);

    m_PoppyPlacementLoD1.AddGeo(&m_PoppyLoD1);
    m_PoppyPlacementLoD1.SetLoD(0.0f, 250.0f);
    m_PoppyPlacementLoD2.AddGeo(&m_PoppyLoD2);
    m_PoppyPlacementLoD2.SetLoD(250.0f, 750.0f);
    m_PoppyPlacementLoD3.AddGeo(&m_PoppyLoD3);
    m_PoppyPlacementLoD3.SetLoD(750.0f, 1500.0f);

    m_plants[1].AddPlacement(&m_PoppyPlacementLoD1);
    m_plants[1].AddPlacement(&m_PoppyPlacementLoD2);
    m_plants[1].AddPlacement(&m_PoppyPlacementLoD3);
    m_plants[1].Scale(1.5f);

    m_NBTreePlacementLoD1.AddGeo(&m_NBTreeLoD1);
    m_NBTreePlacementLoD1.SetLoD(0.0f, 100.0f);
    m_NBTreePlacementLoD2.AddGeo(&m_NBTreeLoD2);
    m_NBTreePlacementLoD2.SetLoD(100.0f, 500.0f);
    m_NBTreePlacementLoD3.AddGeo(&m_NBTreeLoD3);
    m_NBTreePlacementLoD3.SetLoD(500.0f, 1000.0f);
    m_NBTreePlacementLoD4.AddGeo(&m_NBTreeLoD4);
    m_NBTreePlacementLoD4.SetLoD(1000.0f, 1500.0f);

    m_plants[2].AddPlacement(&m_NBTreePlacementLoD1);
    m_plants[2].AddPlacement(&m_NBTreePlacementLoD2);
    m_plants[2].AddPlacement(&m_NBTreePlacementLoD3);
    m_plants[2].AddPlacement(&m_NBTreePlacementLoD4);
    m_plants[2].Scale(3.5f);

    for (auto& cluster : m_forestClusters)
    {
        AddPlacement(cluster);
        auto species = cluster->GetPlantPlacements();
        for (int i = 0; i < species.size(); i++)
        {
            for (auto& plantPlacement : species[i])
            {
                plantPlacement->AddPlacement(&m_plants[i]);
            }
        }
    }
}

void Forest::InitGeos(CGeoTerrain* terrain)
{
    ThreadPool threadPool(4);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD1, 0.2f, 1);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD2, 0.2f, 2);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD3, 0.2f, 3);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeLoD4, 0.2f, 4);
    threadPool.EnqueueTask(CBTreeInit, &m_CBTreeCollision, 0.8f, 9);
    threadPool.EnqueueTask(PoppyInit, &m_PoppyLoD1, 0);
    threadPool.EnqueueTask(PoppyInit, &m_PoppyLoD2, 1);
    threadPool.EnqueueTask(PoppyInit, &m_PoppyLoD3, 2);
    threadPool.EnqueueTask(NBTreeInit, &m_NBTreeLoD1, 0.2f, 1);
    threadPool.EnqueueTask(NBTreeInit, &m_NBTreeLoD2, 0.2f, 2);
    threadPool.EnqueueTask(NBTreeInit, &m_NBTreeLoD3, 0.2f, 3);
    threadPool.EnqueueTask(NBTreeInit, &m_NBTreeLoD4, 0.2f, 4);


    std::mutex mutex;
    for (int i = -TERRAIN_SIZE / 2; i < TERRAIN_SIZE; i += CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            threadPool.EnqueueTask(ClusterInit, terrain, CHVector(i, 0, j), &m_forestClusters, &mutex);
        }
    }
}

void Forest::CBTreeInit(CherryBlossomTree* tree, float frTimeOfYear, unsigned int lod)
{
    tree->SetRandomSeed(CBTREE_SEED);
    tree->Iterate(150.0f, frTimeOfYear, 0.0f);
    tree->Init(tree, lod);
    tree->DeIterate();
}

void Forest::PoppyInit(GeoBioPoppy* poppy, unsigned int lod)
{
    poppy->SetRandomSeed(POPPY_SEED);
    poppy->Iterate(1.0f, 0.2f, 0.0f);
    poppy->Init(poppy, lod);
    poppy->DeIterate();
}

void Forest::NBTreeInit(Nadelbaum* tree, float frTimeOfYear, unsigned int lod)
{
    tree->SetRandomSeed(NBTREE_SEED);
    tree->Iterate(300.0f, frTimeOfYear, 0.0f);
    tree->Init(tree, lod);
    tree->DeIterate();
}

void Forest::ClusterInit(CGeoTerrain* terrain, CHVector position, std::vector<ForestCluster*>* clusters, std::mutex* mutex)
{

    ForestCluster* newCluster = new ForestCluster(terrain, position, CLUSTER_SIZE);
    newCluster->AddPlacementsForSpecies(TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI); //cherrytrees höhe wo sie wachsen dürfen, abhang etc
    newCluster->AddPlacementsForSpecies(TREES_PER_CLUSTER, 10.0, 130.0f); //poppies
    newCluster->AddPlacementsForSpecies(TREES_PER_CLUSTER, 0.0, 130.0f, 0.0f, QUARTERPI); // Nadelbaum
    mutex->lock();
    clusters->push_back(newCluster);
    mutex->unlock();
}