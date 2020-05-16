#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

#define KEYBOARD_SENSITIVITY 100
#define MOUSE_SENSITIVITY 1

class KeyboardControl: public CDeviceKeyboard, public CDeviceMouse
{
public:
    KeyboardControl();
    ~KeyboardControl();

    void Init(CGeos* collisionObjects, CGeoTerrains* collisionTerrains);

    void Tick(float fTimeDelta);

    CPlacement translation;
    CPlacement yaw;
    CPlacement pitch;

private:
    void rotate();
    void move(float fTimeDelta);

    CGeos* collisionObjects;
    CGeoTerrains* collisionTerrains;
};

