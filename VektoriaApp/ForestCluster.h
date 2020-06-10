#pragma once
#include "Vektoria\Root.h"
#include <vector>

using namespace Vektoria;

class ForestCluster :
    public CPlacement
{
public:
    ForestCluster(uint8_t numPlants, CGeoTerrain* terrain, CHVector position, float size);

    std::vector<CPlacement*>& GetPlantPlacements()
    {
        return m_plantPlacements;
    };

private:
    std::vector<CPlacement*> m_plantPlacements;
};

