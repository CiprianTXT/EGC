#include "rhombus.h"

using namespace rhombus;

Rhombus::Rhombus()
{
    this->type = "none";
    this->cost = 0;
    this->scale = 0;
    this->lastProjectileElapsedTime = 0;
    this->readyToFire = false;
    this->isKilled = false;
}

Rhombus::Rhombus(const std::string& type, const int cost, const float scale, const double lastProjectileElapsedTime,
    const bool readyToFire, const bool isKilled)
{
    this->type = type;
    this->cost = cost;
    this->scale = scale;
    this->lastProjectileElapsedTime = lastProjectileElapsedTime;
    this->readyToFire = readyToFire;
    this->isKilled = isKilled;
}
