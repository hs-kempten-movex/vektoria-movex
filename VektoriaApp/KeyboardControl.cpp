#include "KeyboardControl.h"
#include <iostream>

KeyboardControl::KeyboardControl(){
    translation.AddPlacement(&yaw);
    yaw.AddPlacement(&pitch);
}

KeyboardControl::~KeyboardControl() {

}

void KeyboardControl::Init(CGeos* collisionObjects) {
    this->collisionObjects = collisionObjects;
}

void KeyboardControl::Tick(float fTimeDalta) {
    rotate();
    move(fTimeDalta);
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
        translationVector += directionCombined * fTimeDalta * KEYBOARD_SENSITIVITY;
    }

    if (this->KeyPressed(DIK_S)) {
        translationVector += -directionCombined * fTimeDalta * KEYBOARD_SENSITIVITY;
    }

    if (this->KeyPressed(DIK_D)) {
        translationVector += right * fTimeDalta * KEYBOARD_SENSITIVITY;
    }

    if (this->KeyPressed(DIK_A)) {
        translationVector += -right * fTimeDalta * KEYBOARD_SENSITIVITY;
    }

    CRay intersectionRay = CRay(translation.GetPos(), translationVector, QUASI_ZERO, translationVector.Length());
    CHitPoint hitPoint;
    collisionObjects->Intersects(intersectionRay, hitPoint);
    if (!hitPoint.m_bExistent) {
        translation.TranslateDelta(translationVector);
    }    
}