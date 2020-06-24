#pragma once
#include "Vektoria\GeoBio.h"
#include "Vektoria\Root.h"

namespace Vektoria
{

	class CGeoBioAsianTree2 : public CGeoBio
	{
	public:

		CGeoBioAsianTree2();

		~CGeoBioAsianTree2();

		void Iterate(float fAge, float fRootCutHeight = 0.0f);

		void Init(CGeoBioAsianTree2* pzgTemplate, unsigned int uLoD);

		void DeIterate();

		CGeoLeaf m_zgLeafMain;

	private:

		CGeoTriangleTable* m_zgBush;
		CFileWavefront m_zfwv;
		CMaterial m_zmBush;


	};
}

