#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

namespace ForestNS
{
    class IPlantGeo :
        public CGeoBio
    {
    public:
        virtual void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD) = 0;
        virtual void Init(IPlantGeo * pzgTemplate, unsigned int uLoD) = 0;
        virtual void DeIterate() = 0;
    };
}