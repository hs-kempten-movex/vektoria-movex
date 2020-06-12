#include "ForestCluster.h"
#include <iostream>

#define TREE_LINE_LOWER 0.0f
#define TREE_LINE_UPPER 1000.f

using namespace ForestNS;

ForestCluster::ForestCluster(CGeoTerrain* terrain, CHVector position, float size) :
    m_terrain{terrain},
    m_size{size}
{
    Translate(position);
}

void ForestCluster::AddPlacementsForSpecies(uint8_t numPlants, float minHeight, float maxHeight, float minSlope, float maxSlope)
{
    std::vector<CPlacement*> plantPlacements;

    for (uint8_t i = 0; i < numPlants; i++)
    {
        CHVector plantPosition = m_terrain->GetRandomPos(minHeight, maxHeight, minSlope, maxSlope, GetPos(), m_size);
        if (plantPosition != CHVector())
        {
            CPlacement* plantPlacement = new CPlacement();
            plantPlacement->RotateYDelta(UM_FRAND()*TWOPI);
            plantPlacement->TranslateDelta(plantPosition - GetPos());

            plantPlacements.push_back(plantPlacement);
            AddPlacement(plantPlacement);
        }
    }

    m_plantPlacements.push_back(plantPlacements);
}