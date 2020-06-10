#include "Forest.h"
#include "Island.h"
#include <iostream>

#define CLUSTER_SIZE 2500

using namespace Vektoria;


Forest::Forest(CGeoTerrain * terrain)
{
	  //gleiche für poppy machen
    m_CBTree.SetRandomSeed(30285);
    m_CBTree.Iterate(150.0f, 0.2f, 0.0f);
    m_CBTree.Init(&m_CBTree, 1);
    m_CBTree.DeIterate();

    m_CBTreePlacement.AddGeo(&m_CBTree);
    m_CBTreePlacement.Scale(3.0f);

    m_poopy.SetRandomSeed(44444);
    m_poopy.Iterate(1.0f, 0.2f, 0.0f);
    m_poopy.Init(&m_poopy, 0);
    m_poopy.DeIterate();

    for (int i = -TERRAIN_SIZE/2; i < TERRAIN_SIZE; i+= CLUSTER_SIZE * 2)
    {
        for (int j = -TERRAIN_SIZE / 2; j < TERRAIN_SIZE; j += CLUSTER_SIZE * 2)
        {
            ForestCluster* newCluster = new ForestCluster(&m_CBTreePlacement, 5, terrain, CHVector(i, 0, j), CLUSTER_SIZE);
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
