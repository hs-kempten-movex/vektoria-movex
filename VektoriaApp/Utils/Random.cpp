#include "Random.h"
#include <stdlib.h>

using namespace UtilsNS;

float Random::Float(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    return min + (random * (max - min));
}

CHVector Random::Vector(CHVector min, CHVector max)
{
    return CHVector
    (
        Random::Float(min.x, max.x),
        Random::Float(min.y, max.y),
        Random::Float(min.z, max.z)
    );
}
