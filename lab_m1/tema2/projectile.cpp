#include "projectile.h"

using namespace projectile3D;

Projectile::Projectile()
{
    this->xCoord = 0;
    this->yCoord = 0;
    this->zCoord = 0;
    this->rotation = 0;
    this->shotElapsedTime = 0;
    this->isFromPlayer = false;
    this->isHit = false;
}

Projectile::Projectile(const float xCoord, const float yCoord, const float zCoord, const float rotation,
    const double shotElapsedTime, const bool isFromPlayer, const bool isHit)
{
    this->xCoord = xCoord;
    this->yCoord = yCoord;
    this->zCoord = zCoord;
    this->rotation = rotation;
    this->shotElapsedTime = shotElapsedTime;
    this->isFromPlayer = isFromPlayer;
    this->isHit = isHit;
}
