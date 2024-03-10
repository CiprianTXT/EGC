#include "tank.h"

using namespace tank;
using namespace projectile3D;

#define SIN(x) static_cast<float>(sin((x) * M_PI / 180))
#define COS(x) static_cast<float>(cos((x) * M_PI / 180))

Tank::Tank()
{
    this->xCoord = 0;
    this->zCoord = 0;
    this->rotation = 0;
    this->turretRotation = 0;
    this->hp = 0;
    this->type = "none";
    this->color = glm::vec3(0);
    this->action = -1;
    this->actionCost = 0;
    this->lastActionTime = 0;
    this->lastShotElapsedTime = 0;
    this->hasCooldown = false;
    this->isKilled = false;
}

Tank::Tank(const float xCoord, const float zCoord, const float rotation, const float turretRotation, const int hp,
    const std::string type, const glm::vec3 color, const int action, const int actionCost, const double lastActionTime,
    const double lastShotElapsedTime, const bool hasCooldown, const bool isKilled)
{
    this->xCoord = xCoord;
    this->zCoord = zCoord;
    this->rotation = rotation;
    this->turretRotation = turretRotation;
    this->hp = hp;
    this->type = type;
    this->color = color;
    this->action = action;
    this->actionCost = actionCost;
    this->lastActionTime = lastActionTime;
    this->lastShotElapsedTime = lastShotElapsedTime;
    this->hasCooldown = hasCooldown;
    this->isKilled = isKilled;
}

Projectile Tank::Shoot()
{
    float cannonMuzzleXCoord = xCoord - COS(rotation) + 5.9f * COS(rotation + turretRotation);
    float cannonMuzzleYCoord = 1.5;
    float cannonMuzzleZCoord = zCoord + SIN(rotation) - 5.9f * SIN(rotation + turretRotation);

    return {
        cannonMuzzleXCoord,
        cannonMuzzleYCoord,
        cannonMuzzleZCoord,
        rotation + turretRotation,
        this->lastShotElapsedTime,
        this->type == "player",
        false
    };
}
