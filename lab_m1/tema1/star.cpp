#include "star.h"

using namespace star;

Star::Star()
{
    this->xPos = 0;
    this->yPos = 0;
    this->yStopPos = 0;
    this->isCollected = false;
}

Star::Star(const float xPos, const float yPos, const float yStopPos, const bool isCollected)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->yStopPos = yStopPos;
    this->isCollected = isCollected;
}