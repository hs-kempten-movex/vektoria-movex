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

		void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight, bool isLoD);

		void Init(CGeoBioBonsai* pzgTemplate, unsigned int uLoD);

		void DeIterate();

		float GetOptimalLoDMin(float fAge, unsigned int uLoD);

		float GetOptimalLoDMax(float fAge, unsigned int uLoD);

	private:

		CGeoLeaf m_zgLeafMain;
		CGeoTriangleTable* m_zgBush;
		CFileWavefront m_zfwv;
		CMaterial m_zmBush;
		bool m_bIsHitbox;


	};
}

