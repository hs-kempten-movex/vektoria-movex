#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class Butterfly: public CPlacement
{
	public:
		Butterfly();
		~Butterfly();

	private:
		CGeo* torso;
		CGeo* wingsL;
		CGeo* wingsR;
		CFileWavefront butterfly_torso_obj;
		CFileWavefront butterfly_wingsL_obj;
		CFileWavefront butterfly_wingsR_obj;
		CPlacement zp_Torso, zp_WingsL, zp_WingsR;
};

