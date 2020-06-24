#pragma once
#include "Vektoria\Root.h"
#include "Geos/GeoBioPoppy.h"
#include "Geos/CherryBlossomTree.h"
#include "Geos/Nadelbaum.h"
#include "ForestCluster.h"
#include "PlantPlacement.h"

using namespace Vektoria;

namespace ForestNS
{
    class Forest :
        public CPlacement
    {
    public:
        Forest(unsigned int seed);
        Forest(unsigned int seed, CGeoTerrain* terrain);
        ~Forest();

        void Init(CGeoTerrain *terrain);

        std::vector<CGeo*>& GetCollisionObjects()
        {
            return m_collisionGeos;
        }

        std::vector<CPlacement*>& GetFlowers()
        {
            return m_zpFlowers;
        }

    private:
        std::array<PlantPlacement<CherryBlossomTree, 4>*, 4> m_zpCherryBlossomTrees;
        std::array<PlantPlacement<GeoBioPoppy, 3>*, 4> m_zpPoppies;

        PlantPlacement<Nadelbaum, 4> m_zpConifer = PlantPlacement<Nadelbaum, 4>(time(NULL), 300.0f, 0.2f, 0.0f);

        std::vector<ForestCluster*> m_forestClusters;
        std::vector<CPlacement*> m_zpFlowers;
        std::vector<CGeo*> m_collisionGeos;

        CGeo* m_Barrel;
        CPlacement m_zpBarrel;

        void InitCluster(CGeoTerrain* terrain);

        CRandom m_random;
    };
}