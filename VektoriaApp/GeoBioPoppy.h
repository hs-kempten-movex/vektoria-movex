#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;


class GeoBioPoppy :
	public CGeoBio
{
public:
	GeoBioPoppy();
	~GeoBioPoppy();

private:

	CMaterial m_zmBlossom;
	CGeoLeaf m_zgLeafMain;
	CGeoLeaf m_zgBlossomMain;
	CGeoLeaf m_zgStamenMain;
};
