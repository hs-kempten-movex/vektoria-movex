#pragma once
#include "Vektoria\Root.h"

#define MAX_WING_ROTATION 1.22173F
#define WING_ROTATION_SPEED 600.0F * 0.0174533F

using namespace Vektoria;

class Butterfly: public CPlacement
{
	public:
		Butterfly();
		~Butterfly();

    void Tick(float fTime, float fTimeDelta);

	private:
		CGeo* torso;
		CGeo* wingsL;
		CGeo* wingsR;

    CFileWavefront objLoader;
		CPlacement zp_Torso, zp_WingsL, zp_WingsR;

    float wingRotation;
    float wingRotationDirection = -1.0f;
};

