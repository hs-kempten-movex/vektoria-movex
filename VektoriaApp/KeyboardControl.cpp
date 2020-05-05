#include "KeyboardControl.h"
#include <iostream>

KeyboardControl::KeyboardControl(){
    translation.AddPlacement(&yaw);
    yaw.AddPlacement(&pitch);
}

KeyboardControl::~KeyboardControl() {

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

    if (this->KeyPressed(DIK_W)) {
        translation.TranslateDelta(directionCombined * fTimeDalta * KEYBOARD_SENSITIVITY);
    }

    if (this->KeyPressed(DIK_S)) {
        translation.TranslateDelta(-directionCombined * fTimeDalta * KEYBOARD_SENSITIVITY);
    }

    if (this->KeyPressed(DIK_D)) {
        translation.TranslateDelta(right * fTimeDalta * KEYBOARD_SENSITIVITY);
    }

    if (this->KeyPressed(DIK_A)) {
        translation.TranslateDelta(-right *fTimeDalta * KEYBOARD_SENSITIVITY);
    }
}