#include "Butterfly.h"

Butterfly::Butterfly()
{
	torso = objLoader.LoadGeo("models\\ButterflyTorso.obj");
	wingsL = objLoader.LoadGeo("models\\ButterflyWingsLeft.obj");
	wingsR = objLoader.LoadGeo("models\\ButterflyWingsRight.obj");

	this->AddPlacement(&zp_Torso);
	this->AddPlacement(&zp_WingsL);
	this->AddPlacement(&zp_WingsR);
  this->RotateY(HALFPI);
  this->RotateXDelta(-HALFPI);

	zp_Torso.AddGeo(torso);
	zp_WingsL.AddGeo(wingsL);
	zp_WingsR.AddGeo(wingsR);
}

Butterfly::~Butterfly() {
	delete torso;
	delete wingsL;
	delete wingsR;
}

void Butterfly::Tick(float fTime, float fTimeDelta) {
  if (abs(wingRotation) >= MAX_WING_ROTATION) {
    wingRotation = wingRotationDirection * MAX_WING_ROTATION;
    wingRotationDirection *= -1.0f;
  }

  wingRotation += WING_ROTATION_SPEED * wingRotationDirection * fTimeDelta;

  zp_WingsL.RotateY(wingRotation);
  zp_WingsR.RotateY(-wingRotation);
}