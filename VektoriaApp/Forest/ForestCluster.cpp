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

#ifdef DEBUG_FORESTCLUSTER
    m_debugCylinderMaterial.Init();
    m_debugCylinderMaterial.SetTransparencyOn();
    m_debugCylinderMaterial.SetTransparency(0.2);
    m_debugCylinder.Init(size, size, 100, &m_debugCylinderMaterial);
    AddGeo(&m_debugCylinder);
#endif // DEBUG_FORESTCLUSTER
}

void ForestCluster::AddPlacementsForSpecies(CPlacement* plant, uint8_t numPlants, float minHeight, float maxHeight, float minSlope, float maxSlope)
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
            plantPlacement->AddPlacement(plant);

            plantPlacements.push_back(plantPlacement);
            AddPlacement(plantPlacement);
        }
        else
        {
            //no position found
            break;
        }
    }

    m_plantPlacements.push_back(plantPlacements);
}