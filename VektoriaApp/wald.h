#pragma once
#include "Vektoria\Root.h"
#include "CherryBlossomTree.h"

using namespace Vektoria;

class Wald :
	public CPlacement
{
private:
	//waldzeug
	CPlacement m_pBaum1;
	CPlacement m_pBaum2;
	CPlacement m_pBaum3;
	CPlacement m_pBaumCluster1;
	CPlacement m_pBaumCluster2;
	CPlacement m_pBaumCluster3;

	//cherrytree zeug
	//CPlacement m_zpLSystem; 
	CherryBlossomTree m_CBTBaum;

public:
	Wald();
	~Wald();
};

