#pragma once
#include "Vektoria\Root.h"
#include <vector>

//#define DEBUG_FORESTCLUSTER

using namespace Vektoria;

namespace ForestNS
{
    class ForestCluster :
        public CPlacement
    {
    public:
        ForestCluster(unsigned int seed, CGeoTerrain* terrain, CHVector position, float size);

        std::vector<CPlacement*> AddPlacementsForSpecies(CPlacement* plant, uint8_t numPlants, float minHeight, float maxHeight, float minSlope = 0.0f, float maxSlope = HALFPI);

        std::vector<std::vector<CPlacement*>>& GetPlantPlacements()
        {
            return m_zpPlants;
        };

    private:
        float m_size;
        CGeoTerrain* m_terrain;

        std::vector<std::vector<CPlacement*>> m_zpPlants;

        CRandom m_random;

#ifdef DEBUG_FORESTCLUSTER
        CGeoCylinder m_debugCylinder;
        CMaterial m_debugCylinderMaterial;
#endif // DEBUG_FORESTCLUSTER
    };
}