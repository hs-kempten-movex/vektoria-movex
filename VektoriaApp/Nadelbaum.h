#include "Vektoria\Root.h"
using namespace Vektoria;

class Nadelbaum :
	public CGeoBio
{
public:

	Nadelbaum();
	~Nadelbaum();
	float GetOptimalLoDMax(float fAge, unsigned int uLoD);
	float GetOptimalLoDMin(float fAge, unsigned int uLoD);
	void Iterate(float fAge, float frTimeOfYear, float fRootCutHeight);
	void Init(Nadelbaum * pzgTemplate, unsigned int uLoD);
	void DeIterate();
	CGeo * test;
	CFileWavefront m_filewavefront;
	CGeoLeaf m_zgLeafMain;
	CGeoLeaf m_zgBlossomMain;
	CGeoLeaf m_zgStamenMain;
};

