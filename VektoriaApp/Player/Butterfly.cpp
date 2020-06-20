#include "Butterfly.h"

using namespace PlayerNS;

Butterfly::Butterfly()
{
    CFileWavefront objLoader;
    m_torso = objLoader.LoadGeo("models\\ButterflyTorso.obj", true);
    m_wingsL = objLoader.LoadGeo("models\\ButterflyWingsLeft.obj", true);
    m_wingsR = objLoader.LoadGeo("models\\ButterflyWingsRight.obj", true);

    m_zmWings.MakeTextureDiffuse("textures\\butterfly\\WingsDiff.png");
    m_wingsL->SetMaterial(&m_zmWings);
    m_wingsR->SetMaterial(&m_zmWings);

    this->AddPlacement(&m_zpTorso);
    m_zpTorso.AddPlacement(&m_zpWingsL);
    m_zpTorso.AddPlacement(&m_zpWingsR);
    m_zpTorso.RotateY(HALFPI);
    m_zpTorso.RotateXDelta(-HALFPI);
    m_zpTorso.ScaleDelta(0.1f);

    m_zpTorso.AddGeo(m_torso);
    m_zpWingsL.AddGeo(m_wingsL);
    m_zpWingsR.AddGeo(m_wingsR);

    this->SetFrustumCullingOff();
}

Butterfly::~Butterfly() {
    delete m_torso;
    delete m_wingsL;
    delete m_wingsR;
}

void Butterfly::Tick(float fTime, float fTimeDelta) {
    if (m_glide && m_wingRotationDirection < 0.0f && abs(m_wingRotation) > 0.000174533)
    {
        m_zpWingsL.RotateY(0.0f);
        m_zpWingsR.RotateY(0.0f);
        return;
    }

    if (abs(m_wingRotation) >= MAX_WING_ROTATION) {
        m_wingRotation = m_wingRotationDirection * MAX_WING_ROTATION;
        m_wingRotationDirection *= -1.0f;
    }

    m_wingRotation += WING_ROTATION_SPEED * m_wingRotationDirection * fTimeDelta;

    m_zpWingsL.RotateY(m_wingRotation);
    m_zpWingsR.RotateY(-m_wingRotation);    
}