#pragma once
#include "Vektoria\Root.h"
#include "Geos/GeoBioPoppy.h"
#include "Geos/CherryBlossomTree.h"
#include "Geos/Nadelbaum.h"
#include "ForestCluster.h"
#include "PlantPlacement.h"

#define CBTREE_SEED 30285
#define CONIFER_SEED 29486
#define POPPY_SEED 44444

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
                &m_zpCherryBlossomTree.GetCollisionGeo()
            };
        }

        std::vector<CPlacement*>& GetFlowers()
        {
            return m_flowers;
        }

    private:
        PlantPlacement<CherryBlossomTree, 4> m_zpCherryBlossomTree = PlantPlacement<CherryBlossomTree, 4>(CBTREE_SEED, 150.0f, 0.2f, 0.0f);
        PlantPlacement<GeoBioPoppy, 3> m_zpPoppy = PlantPlacement<GeoBioPoppy, 3>(POPPY_SEED, 1.0f, 0.2f, 0.0f);
        PlantPlacement<Nadelbaum, 4> m_zpConifer = PlantPlacement<Nadelbaum, 4>(CONIFER_SEED, 300.0f, 0.2f, 0.0f);

        std::vector<ForestCluster*> m_forestClusters;
        std::vector<CPlacement*> m_flowers;

        void InitCluster(CGeoTerrain* terrain);
    };
}