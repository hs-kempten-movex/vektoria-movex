#pragma once
#include "Vektoria\GeoBio.h"

namespace Vektoria
{

	class CGeoBioAsianTree : public CGeoBio
	{
	public:

		CGeoBioAsianTree();

		~CGeoBioAsianTree();

		void Iterate(float fAge, float fRootCutHeight);

		void Init(CGeoBioAsianTree* pzgTemplate, unsigned int uLoD);

		void DeIterate();

		CGeoLeaf m_zgLeafMain;

	};
}

