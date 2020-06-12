#pragma once
#include "Vektoria\Root.h"
#include "GeoBioPoppy.h"
#include "CherryBlossomTree.h"
#include "ForestCluster.h"
#include <array>

using namespace Vektoria;

namespace ForestNS
{
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
        CPlacement m_CBTreePlacementLoD1;
        CPlacement m_CBTreePlacementLoD2;
        CPlacement m_CBTreePlacementLoD3;

        GeoBioPoppy m_PoppyLoD1;
        GeoBioPoppy m_PoppyLoD2;
        GeoBioPoppy m_PoppyLoD3;
        CPlacement m_PoppyPlacementLoD1;
        CPlacement m_PoppyPlacementLoD2;
        CPlacement m_PoppyPlacementLoD3;

        std::vector<ForestCluster*> m_forestClusters;
        std::array<CPlacement, 2> m_plants;

        void InitGeos(CGeoTerrain* terrain);

        static void CBTreeInit(CherryBlossomTree* tree, unsigned int lod);
        static void PoppyInit(GeoBioPoppy* poppy, unsigned int lod);
        static void ClusterInit(CGeoTerrain* terrain, CHVector position, std::vector<ForestCluster*>* clusters, std::mutex* mutex);
    };
}