#include "ForestCluster.h"
#include <iostream>

#define TREE_LINE_LOWER 0.0f
#define TREE_LINE_UPPER 1000.f


ForestCluster::ForestCluster(uint8_t numPlants, CGeoTerrain* terrain, CHVector position, float size)
{
    Translate(position);

    for (uint8_t i = 0; i < numPlants; i++)
    {
        CHVector plantPosition = terrain->GetRandomPos(TREE_LINE_LOWER, TREE_LINE_UPPER, 0.0f, HALFPI, position, size);
        if (plantPosition != CHVector())
        {
            CPlacement* plantPlacement = new CPlacement();
            plantPlacement->RotateYDelta(UM_FRAND()*TWOPI);
            plantPlacement->TranslateDelta(plantPosition - position);

            m_plantPlacements.push_back(plantPlacement);
            AddPlacement(plantPlacement);
        }
    }
}