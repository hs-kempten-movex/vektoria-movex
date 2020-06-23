#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;

namespace UtilsNS
{
    class Random
    {
    public:
        static float Float(float min, float max);

        static CHVector Vector(CHVector min, CHVector max);
    };
}