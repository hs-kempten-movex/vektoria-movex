#pragma once
#include "Vektoria\Root.h"
#include "GeoBioPoppy.h"
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
	CPlacement m_pBaum4;
	CPlacement m_pBaum5;
	CPlacement m_pBaum6;
	CPlacement m_pBaum7;
	CPlacement m_pBaum8;
	CPlacement m_pBaum9;
	CPlacement m_pBaum10;

	CPlacement m_pBaumCluster1;
	CPlacement m_pBaumCluster2;
	CPlacement m_pBaumCluster3;

	void translateTreeToHeight(float x, float z, CPlacement* baum, CGeoTerrain* terrain);
	//cherrytree zeug
	//CPlacement m_zpLSystem; 
	CherryBlossomTree* m_CBTBaum = new CherryBlossomTree();
	GeoBioPoppy* poopy = new GeoBioPoppy();
	CPlacement m_pPoopy;

public:
	Wald(CGeoTerrain * terrain);
	~Wald();
};

