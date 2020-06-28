#pragma once
#include "Vektoria\Root.h"
#include "Forest/Geos/IPlantGeo.h"

using namespace Vektoria;

namespace ForestNS
{
	class GeoBioJapanischerSchildfarn :
		public IPlantGeo
	{
	public:
		GeoBioJapanischerSchildfarn();
		~GeoBioJapanischerSchildfarn();
		void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD) override;
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
		bool m_bIsHitbox = false;
	};
}

