#include "Butterfly.h"

Butterfly::Butterfly()
{
	torso = butterfly_torso_obj.LoadGeo("models\\ButterflyTorso.obj");
	wingsL = butterfly_wingsL_obj.LoadGeo("models\\ButterflyWingsLeft.obj");
	wingsR = butterfly_wingsR_obj.LoadGeo("models\\ButterflyWingsRight.obj");

	this->AddPlacement(&zp_Torso);
	this->AddPlacement(&zp_WingsL);
	this->AddPlacement(&zp_WingsR);
	this->RotateY(PI / 2);
	this->TranslateZDelta(-30);

	zp_Torso.AddGeo(torso);
	zp_WingsL.AddGeo(wingsL);
	zp_WingsR.AddGeo(wingsR);
}

Butterfly::~Butterfly() {
	delete torso;
	delete wingsL;
	delete wingsR;
}