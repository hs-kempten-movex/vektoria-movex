#include "KeyboardControl.h"

using namespace PlayerNS;

KeyboardControl::KeyboardControl(){
    translation.AddPlacement(&yaw);
    yaw.AddPlacement(&pitch);
}

KeyboardControl::~KeyboardControl() {

}

void KeyboardControl::Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains) {
    this->collisionObjects = collisionObjects;
    this->collisionTerrains = collisionTerrains;
}

void KeyboardControl::Tick(float time, float fTimeDelta) {
    rotate();
    move(fTimeDelta);
}

void KeyboardControl::rotate() {
    yaw.RotateYDelta(-GetRelativeX() * MOUSE_SENSITIVITY);
    pitch.RotateXDelta(GetRelativeY() * MOUSE_SENSITIVITY);
}

void KeyboardControl::move(float fTimeDalta) {
    CHVector yawDirection = yaw.GetDirection();
    CHVector pitchDirection = pitch.GetDirection();
    CHVector directionCombined = CHVector(yawDirection.x, pitchDirection.y, yawDirection.z).Normal();
    CHVector right = yawDirection ^ CHVector(0, 1, 0);
    
    CHVector translationVector = CHVector();

    if (this->KeyPressed(DIK_W)) {
        translationVector += directionCombined;
    }

    if (this->KeyPressed(DIK_S)) {
        translationVector += -directionCombined;
    }

    if (this->KeyPressed(DIK_D)) {
        translationVector += right;
    }

    if (this->KeyPressed(DIK_A)) {
        translationVector += -right;
    }

    translationVector *= fTimeDalta * KEYBOARD_SENSITIVITY;

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