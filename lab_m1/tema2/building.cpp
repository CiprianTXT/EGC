#include "building.h"

using namespace building;

Building::Building()
{
    this->xCoord = 0;
    this->yHeight = 0;
    this->zCoord = 0;
    this->length = 0;
    this->width = 0;
}

Building::Building(const float xCoord, const float yHeight, const float zCoord, const float length, const float width)
{
    this->xCoord = xCoord;
    this->yHeight = yHeight;
    this->zCoord = zCoord;
    this->length = length;
    this->width = width;
}
