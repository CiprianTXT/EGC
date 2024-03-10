#pragma once

#include "utils/glm_utils.h"
#include "projectile.h"

namespace tank
{
    class Tank
    {
    public:
        float xCoord;
        float zCoord;
        float rotation;
        float turretRotation;
        int hp;
        std::string type;
        glm::vec3 color;
        int action;
        int actionCost;
        double lastActionTime;
        double lastShotElapsedTime;
        bool hasCooldown;
        bool isKilled;

        // Approximate tank radius: 3.29287f
        Tank();
        Tank(float xCoord, float zCoord, float rotation, float turretRotation, int hp, std::string type, glm::vec3 color,
            int action, int actionCost, double lastActionTime, double lastShotElapsedTime, bool hasCooldown, bool isKilled);

        projectile3D::Projectile Shoot();
    };
}
