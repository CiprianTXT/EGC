#include "hexagon.h"

using namespace hexagon;

Hexagon::Hexagon()
{
    this->type = "none";
    this->scale = 0;
    this->xCoord = 0;
    this->yCoord = 0;
    this->hp = 0;
    this->isKilled = true;
}

Hexagon::Hexagon(const std::string& type, const float scale, const float xCoord, const float yCoord, const int hp, const bool isKilled)
{
    this->type = type;
    this->scale = scale;
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->hp = hp;
    this->isKilled = isKilled;
}

