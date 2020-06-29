#pragma once
#include "Vektoria\GeoBio.h"

namespace Vektoria
{

	class CGeoBioAsianTree : public CGeoBio
	{
	public:

		CGeoBioAsianTree();

		~CGeoBioAsianTree();

		void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD);

		void Init(CGeoBioAsianTree* pzgTemplate, unsigned int uLoD);

		void DeIterate();

		float GetOptimalLoDMin(float fAge, unsigned int uLoD);

		float GetOptimalLoDMax(float fAge, unsigned int uLoD);


	private:

		CGeoLeaf m_zgLeafMain;
		bool m_bIsHitbox;

	};

}

