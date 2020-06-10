#pragma once
#include "Vektoria\Root.h"
#include "GeoBioPoppy.h"
#include "CherryBlossomTree.h"
#include "ForestCluster.h"
#include <thread>
#include <mutex>

using namespace Vektoria;

class Forest :
	  public CPlacement
{
public:
    Forest() {};

    Forest(CGeoTerrain* terrain);
    ~Forest();
private:

    CherryBlossomTree m_CBTreeLoD1;
    CherryBlossomTree m_CBTreeLoD2;
    CherryBlossomTree m_CBTreeLoD3;
    CPlacement m_CBTreePlacement;
    CPlacement m_CBTreePlacementLoD1;
    CPlacement m_CBTreePlacementLoD2;
    CPlacement m_CBTreePlacementLoD3;

	  GeoBioPoppy m_poopy;

    std::vector<ForestCluster*> m_forestClusters;

    static void CBTreeInit(CherryBlossomTree* tree, unsigned int lod);
    static void ClusterInit(CGeoTerrain* terrain, CHVector position, std::vector<ForestCluster*>* clusters, std::mutex* mutex);
};

