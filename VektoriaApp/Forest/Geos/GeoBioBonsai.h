#pragma once
#include "Vektoria\GeoBio.h"
#include "Vektoria\Root.h"

namespace Vektoria
{

	class CGeoBioBonsai : public CGeoBio
	{
	public:

		CGeoBioBonsai();

		CGeoBioBonsai();

		void Iterate(float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0f);

		void Init(CGeoBioBonsai* pzgTemplate, unsigned int uLoD);

		void DeIterate();

		CGeoLeaf m_zgLeafMain;

	private:

		CGeoTriangleTable* m_zgBush;
		CFileWavefront m_zfwv;
		CMaterial m_zmBush;


	};
}

