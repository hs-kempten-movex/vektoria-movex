#pragma once
#include "Vektoria\Root.h"
#include "IPlantGeo.h"

using namespace Vektoria;

namespace ForestNS
{
	class GeoBioPoppy : 
      public IPlantGeo
	{
	public:
		GeoBioPoppy();
		~GeoBioPoppy();
		void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD) override;
		void DeIterate() override;

		void Init(IPlantGeo * pzgTemplate, unsigned int uLoD = 0) override;
		float GetOptimalLoDMin(float fAge, unsigned int uLoD);
		float GetOptimalLoDMax(float fAge, unsigned int uLoD);

  private:
		CGeoLeaf m_zgStamenMain;
		CGeoLeaf m_zgBlossomMain;
		CGeoLeaf m_zgLeafMain;
  	CGeoTriangleTable m_zgFruitMain;
		CMaterial m_zmStamen;
		float fColorscaling;
	};
}
