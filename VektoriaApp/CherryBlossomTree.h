#include "Vektoria\Root.h"
using namespace Vektoria;

class CherryBlossomTree : public CGeoBio
{
public:
	CherryBlossomTree();
	~CherryBlossomTree();
	void Iterate(float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0f);
	void DeIterate();
	void Init(CherryBlossomTree * pzgTemplate, unsigned int uLoD = 0);
	float GetOptimalLoDMin(float fAge, unsigned int uLoD);
	float GetOptimalLoDMax(float fAge, unsigned int uLoD);

private:
	CGeoBio m_zgCherryblossom;
	CMaterial m_zmBlossom;
	bool m_bIsBlossoming = false;
};