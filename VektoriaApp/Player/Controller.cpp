#include "Controller.h"

using namespace PlayerNS;

Controller::Controller(){
    translation.AddPlacement(&yaw);
    yaw.AddPlacement(&pitch);
}

Controller::~Controller() {

}

void Controller::Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains) {
    this->collisionObjects = collisionObjects;
    this->collisionTerrains = collisionTerrains;
}

void Controller::Tick(float time, float fTimeDelta) {
    rotate(fTimeDelta);
    move(fTimeDelta);
}

void Controller::rotate(float fTimeDalta) {
    float relativeX = GetRelativeRX();
    if (abs(relativeX) > CONTROLLER_DRIFT_THRESHOLD) // prevent drifting
    {
        yaw.RotateYDelta(-relativeX * fTimeDalta);
    }
    float relativeY = GetRelativeRY();
    if (abs(relativeY) > CONTROLLER_DRIFT_THRESHOLD)
    {
        pitch.RotateXDelta(relativeY * fTimeDalta);
    }   
}

void Controller::move(float fTimeDalta) {
    CHVector yawDirection = yaw.GetDirection();
    CHVector pitchDirection = pitch.GetDirection();
    CHVector front = CHVector(yawDirection.x, pitchDirection.y, yawDirection.z).Normal();
    CHVector right = yawDirection ^ CHVector(0, 1, 0);
    
    CHVector translationVector = CHVector();

    // Controller
    float relativeY = GetRelativeY();
    if (abs(relativeY) > CONTROLLER_DRIFT_THRESHOLD)
    {
        translationVector += front * -relativeY * CONTROLLER_SENSITIVITY;
    }

    float relativeX = GetRelativeX();
    if (abs(relativeX) > CONTROLLER_DRIFT_THRESHOLD)
    {
        translationVector += right * relativeX * CONTROLLER_SENSITIVITY;
    }

    translationVector *= fTimeDalta;

    CHVector nextPos = translation.GetPos() + translationVector;
    CHitPoint terrainHitPoint;
    collisionTerrains->GetHitpoint(nextPos.x, nextPos.z, terrainHitPoint);

    CRay intersectionRay = CRay(translation.GetPos(), translationVector, QUASI_ZERO, translationVector.Length());
    CHitPoint ObjectHitPoint;
    collisionObjects->Intersects(intersectionRay, ObjectHitPoint);

    if ((terrainHitPoint.m_bExistent && terrainHitPoint.m_vPos.y > nextPos.y) || ObjectHitPoint.m_bExistent) {
        return;
    }
    
    translation.TranslateDelta(translationVector);
}