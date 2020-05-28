#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

class BaumCluster :
	public CPlacement
{
public:
	BaumCluster(int tree, int flower);
	~BaumCluster();
	void updateTrees();
	void updateFlowers();
private:
	CGeoBio createTree();
};

