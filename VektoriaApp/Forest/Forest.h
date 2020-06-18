#pragma once
#include "Vektoria\Root.h"
#include "GeoBioPoppy.h"
#include "CherryBlossomTree.h"
#include "Nadelbaum.h"
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

        void Init(CGeoTerrain *terrain);

        std::vector<CGeo*> GetCollisionObjects()
        {
            return std::vector<CGeo*>{
                &m_CBTreeCollision
            };
        }

    private:
        CherryBlossomTree m_CBTreeLoD1;
        CherryBlossomTree m_CBTreeLoD2;
        CherryBlossomTree m_CBTreeLoD3;
        CherryBlossomTree m_CBTreeLoD4;
        CherryBlossomTree m_CBTreeCollision;

        CPlacement m_CBTreePlacementLoD1;
        CPlacement m_CBTreePlacementLoD2;
        CPlacement m_CBTreePlacementLoD3;
        CPlacement m_CBTreePlacementLoD4;
        CPlacement m_CbTreePlacementCollision;

        GeoBioPoppy m_PoppyLoD1;
        GeoBioPoppy m_PoppyLoD2;
        GeoBioPoppy m_PoppyLoD3;
        CPlacement m_PoppyPlacementLoD1;
        CPlacement m_PoppyPlacementLoD2;
        CPlacement m_PoppyPlacementLoD3;

        Nadelbaum m_NBTreeLoD1;
        /*Nadelbaum m_NBTreeLoD2;*/

        CPlacement m_NBTreePlacementLoD1;
        /*CPlacement m_NBTreePlacementLoD2;*/

        std::vector<ForestCluster*> m_forestClusters;
        std::array<CPlacement, 3> m_plants;

        void InitGeos(CGeoTerrain* terrain);

        static void CBTreeInit(CherryBlossomTree* tree, float frTimeOfYear, unsigned int lod);
        static void PoppyInit(GeoBioPoppy* poppy, unsigned int lod);
        static void NBTreeInit(Nadelbaum* tree, float frTimeOfYear, unsigned int lod);
        static void ClusterInit(CGeoTerrain* terrain, CHVector position, std::vector<ForestCluster*>* clusters, std::mutex* mutex);
    };
}