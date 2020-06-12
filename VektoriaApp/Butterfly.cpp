#include "Butterfly.h"

Butterfly::Butterfly()
{
	torso = objLoader.LoadGeo("models\\ButterflyTorso.obj", true);
	wingsL = objLoader.LoadGeo("models\\ButterflyWingsLeft.obj", true);
	wingsR = objLoader.LoadGeo("models\\ButterflyWingsRight.obj", true);

	m_zmWings.MakeTextureDiffuse("textures\\butterfly\\WingsDiff.png");
	wingsL->SetMaterial(&m_zmWings);
	wingsR->SetMaterial(&m_zmWings);

	this->AddPlacement(&zp_Torso);
	this->AddPlacement(&zp_WingsL);
	this->AddPlacement(&zp_WingsR);
	this->RotateY(HALFPI);
	this->RotateXDelta(-HALFPI);
  this->ScaleDelta(0.1);

	zp_Torso.AddGeo(torso);
	zp_WingsL.AddGeo(wingsL);
	zp_WingsR.AddGeo(wingsR);

	this->SetFrustumCullingOff();
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