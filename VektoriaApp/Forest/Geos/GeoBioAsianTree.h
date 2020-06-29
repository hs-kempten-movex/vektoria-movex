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

		void Init(IPlantGeo* pzgTemplate, unsigned int uLoD) override;

		void DeIterate() override;

		float GetOptimalLoDMin(float fAge, unsigned int uLoD);

		float GetOptimalLoDMax(float fAge, unsigned int uLoD);


	private:

		CGeoLeaf m_zgLeafMain;
		bool m_bIsHitbox;

	};

}

