#pragma once
#include "Vektoria\Root.h"
#include <vector>

using namespace Vektoria;

namespace ForestNS
{
    class ForestCluster :
        public CPlacement
    {
    public:
        ForestCluster(CGeoTerrain* terrain, CHVector position, float size);

        void AddPlacementsForSpecies(uint8_t numPlants, float minHeight, float maxHeight, float minSlope = 0.0f, float maxSlope = HALFPI);

        std::vector<std::vector<CPlacement*>>& GetPlantPlacements()
        {
            return m_plantPlacements;
        };

    private:
        float m_size;
        CGeoTerrain* m_terrain;

        std::vector<std::vector<CPlacement*>> m_plantPlacements;
    };
}