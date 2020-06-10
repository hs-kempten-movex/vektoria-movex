#include "Forest.h"
#include "Island.h"
#include <iostream>

#define CBTREE_SEED 30285

#define CLUSTER_SIZE 500
#define TREES_PER_CLUSTER 20

using namespace Vektoria;


Forest::Forest(CGeoTerrain * terrain)
{
    m_CBTreeLoD1.SetRandomSeed(CBTREE_SEED);
    m_CBTreeLoD1.Iterate(150.0f, 0.2f, 0.0f);
    m_CBTreeLoD1.Init(&m_CBTreeLoD1, 0);
    m_CBTreeLoD1.DeIterate();
    
    m_CBTreeLoD2.SetRandomSeed(CBTREE_SEED);
    m_CBTreeLoD2.Iterate(150.0f, 0.2f, 0.0f);
    m_CBTreeLoD2.Init(&m_CBTreeLoD2, 1);
    m_CBTreeLoD2.DeIterate();

    m_CBTreeLoD3.SetRandomSeed(CBTREE_SEED);
    m_CBTreeLoD3.Iterate(150.0f, 0.2f, 0.0f);
    m_CBTreeLoD3.Init(&m_CBTreeLoD3, 2);
    m_CBTreeLoD3.DeIterate();

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

    for (int i = -TERRAIN_SIZE/2; i < TERRAIN_SIZE; i+= CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            ForestCluster* newCluster = new ForestCluster(&m_CBTreePlacement, TREES_PER_CLUSTER, terrain, CHVector(i, 0, j), CLUSTER_SIZE);
            m_forestClusters.push_back(newCluster);
            AddPlacement(newCluster);
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
