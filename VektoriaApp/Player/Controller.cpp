#include "Controller.h"

using namespace PlayerNS;

Controller::Controller(){
    translation.AddPlacement(&yaw);
    yaw.AddPlacement(&pitch);
}

Controller::~Controller() {

}

void Controller::Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains) {

    translation.SetCollisionObjects(collisionObjects);
    translation.SetCollisionTerrains(collisionTerrains);
}

void Controller::Tick(float fTime, float fTimeDelta) {
    rotate(fTimeDelta);
    move(fTimeDelta);

    translation.Tick(fTime, fTimeDelta);
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
    CHVector up = right ^ front;
    
    // gravity
    CHVector acceleration(0, -9.81, 0);

    float relativeY = -GetRelativeY();
    if (abs(relativeY) > CONTROLLER_DRIFT_THRESHOLD)
    {
        // slower backwards acceleration
        if (relativeY < 0.0f)
        {
            relativeY *= BACKWARDS_ACCELERATION_MULTIPLIER;
        }

        acceleration += front * relativeY * CONTROLLER_SENSITIVITY;
    }

    float relativeX = GetRelativeX();
    if (abs(relativeX) > CONTROLLER_DRIFT_THRESHOLD)
    {
        acceleration += right * relativeX * CONTROLLER_SENSITIVITY;
    }

    float relativeZ = -GetRelativeZ();
    if (abs(relativeZ) > CONTROLLER_DRIFT_THRESHOLD)
    {
        // only fly up
        if (relativeZ > 0.0f)
        {
            acceleration += up * relativeZ * CONTROLLER_SENSITIVITY;
        }
    }
    
    translation.SetAcceleration(acceleration);
}