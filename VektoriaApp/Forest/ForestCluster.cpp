#include "ForestCluster.h"
#include "../Utils/Random.h"

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

std::vector<CPlacement*> ForestCluster::AddPlacementsForSpecies(CPlacement* plant, uint8_t numPlants, float minHeight, float maxHeight, float minSlope, float maxSlope)
{
    std::vector<CPlacement*> plantPlacements;
    CHVector minVec = GetPos() - CHVector(m_size, 0, m_size);
    CHVector maxVec = GetPos() + CHVector(m_size, 0, m_size);

    for (uint8_t i = 0; i < numPlants; i++)
    {
        CHitPoint hitPoint;
        CHVector randomPosition = UtilsNS::Random::Vector(minVec, maxVec);
        randomPosition.y = m_terrain->GetHeight(randomPosition.x, randomPosition.z);
        float slope = m_terrain->GetSlope(randomPosition.x, randomPosition.z);

        if (randomPosition.y >= minHeight && randomPosition.y <= maxHeight && slope >= minSlope && slope <= maxSlope)
        {
            CPlacement* plantPlacement = new CPlacement();
            plantPlacement->RotateYDelta(UM_FRAND()*TWOPI);
            plantPlacement->TranslateDelta(randomPosition - GetPos());
            plantPlacement->AddPlacement(plant);

            plantPlacements.push_back(plantPlacement);
            AddPlacement(plantPlacement);
        }
    }

    m_zpPlants.push_back(plantPlacements);
    return plantPlacements;
}