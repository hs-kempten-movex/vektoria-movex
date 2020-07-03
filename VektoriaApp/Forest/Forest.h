#pragma once
#include "Vektoria\Root.h"
#include "Geos/GeoBioPoppy.h"
#include "Geos/CherryBlossomTree.h"
#include "Geos/Nadelbaum.h"
#include "Geos/GeoBioJapanischerSchildfarn.h"
#include "Geos/GeoBioAsianTree.h"
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
        std::array<PlantPlacement<Nadelbaum, 4>*, 3> m_zpConifers;
        std::array<PlantPlacement<CGeoBioAsianTree, 3>*, 2> m_zpAsiaTrees;
        std::array<PlantPlacement<GeoBioPoppy, 3>*, 4> m_zpPoppies;
        std::array<PlantPlacement<GeoBioJapanischerSchildfarn, 3>*, 4> m_zpJapanischeSchildfarne;        

        std::vector<ForestCluster*> m_forestClusters;
        std::vector<CPlacement*> m_zpFlowers;
        std::vector<CGeo*> m_collisionGeos;

        CGeo* m_zgBarrel;
        CPlacement m_zpBarrel;
        CMaterial m_zmBarrel;

        CGeo* m_zgChest;
        CPlacement m_zpChest;
        CMaterial m_zmChest;

        CGeo* m_zgStone;
        CPlacement m_zpStone;
        CMaterial m_zmStone;

        void InitCluster(CGeoTerrain* terrain);

        CRandom m_random;
    };
}