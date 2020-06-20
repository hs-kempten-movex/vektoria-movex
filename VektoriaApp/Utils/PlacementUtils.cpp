#include "PlacementUtils.h"

using namespace UtilsNS;

std::vector<CHVector> PlacementUtils::GetGlobalPositions(CPlacement* placement)
{
    std::vector<CHVector> positions;

    for (int i = 0; i < placement->GetNrOfParents(); i++)
    {
        CPlacement* parentPlacement = dynamic_cast<CPlacement*>(placement->GetParent(i));
        if (parentPlacement)
        {
            for (auto& it : GetGlobalPositions(parentPlacement))
            {
                positions.push_back(it + placement->GetPos());
            }
        }
        else
        {
            positions.push_back(placement->GetPos());
        }
    }

    return positions;
}
