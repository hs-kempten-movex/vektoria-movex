#pragma once
#include "Vektoria\Root.h"
#include "GeoBioPoppy.h"
#include "CherryBlossomTree.h"
#include "ForestCluster.h"

using namespace Vektoria;

class Forest :
	  public CPlacement
{
public:
    Forest() {};

    Forest(CGeoTerrain * terrain);
    ~Forest();

private:
	  CherryBlossomTree m_CBTree;
    CPlacement m_CBTreePlacement;

	  GeoBioPoppy m_poopy;

    std::vector<ForestCluster*> m_forestClusters;
};

