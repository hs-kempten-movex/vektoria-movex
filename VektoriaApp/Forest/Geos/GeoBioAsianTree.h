#pragma once
#include "Vektoria\GeoBio.h"
#include "IPlantGeo.h"

using namespace Vektoria;

namespace ForestNS
{
    class CGeoBioAsianTree :
        public IPlantGeo
    {
    public:
        CGeoBioAsianTree();
        ~CGeoBioAsianTree();
        void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD) override;
        void DeIterate() override;

        void Init(IPlantGeo* pzgTemplate, unsigned int uLoD) override;

    private:
        CGeoLeaf m_zgLeafMain;
    };
}

