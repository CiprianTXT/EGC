#include "projectile.h"

using namespace projectile;

Projectile::Projectile()
{
    this->type = "none";
    this->xCoord = 0;
    this->yCoord = 0;
    this->rotation = -1;
    this->isHit = false;
}

Projectile::Projectile(const std::string& type, const float xCoord, const float yCoord, const float rotation, const bool isHit)
{
    this->type = type;
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->rotation = rotation;
    this->isHit = isHit;
}
