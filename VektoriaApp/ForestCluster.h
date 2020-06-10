#pragma once
#include "Vektoria\Root.h"
#include <vector>

using namespace Vektoria;

class ForestCluster :
    public CPlacement
{
public:
    ForestCluster(CPlacement* plant, uint8_t numPlants, CGeoTerrain* terrain, CHVector position, float size);

private:
    std::vector<CPlacement*> m_plantPlacements;
};

