#pragma once
#include "Vektoria\Root.h"
#include <vector>

using namespace Vektoria;

namespace UtilsNS
{
    class PlacementUtils
    {
    public:
        static std::vector<CHVector> GetGlobalPositions(CPlacement* placement);
    };
}
