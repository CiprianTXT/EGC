#pragma once

#include <string>

namespace projectile
{
    class Projectile
    {
    public:
        std::string type;
        float xCoord;
        float yCoord;
        float rotation;
        bool isHit;

        Projectile();
        Projectile(const std::string& type, float xCoord, float yCoord, float rotation, bool isHit);
    };
}
