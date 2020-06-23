#pragma once
#include "Vektoria\Root.h"
#include "IPlantGeo.h"

using namespace Vektoria;

namespace ForestNS
{
    class Nadelbaum :
        public IPlantGeo
    {
    public:
        Nadelbaum();
        ~Nadelbaum();
		void Iterate(float fAge, float fRootCutHeight, bool hasNeedles = true);
		void DeIterate() override;
        
        void Init(IPlantGeo * pzgTemplate, unsigned int uLoD = 0) override;
        float GetOptimalLoDMax(float fAge, unsigned int uLoD);
        float GetOptimalLoDMin(float fAge, unsigned int uLoD);
    private:
        CGeo * test;
        CFileWavefront m_filewavefront;
        CGeoLeaf m_zgLeafMain;
        CGeoLeaf m_zgBlossomMain;
        CGeoLeaf m_zgStamenMain;
    };
}