#pragma once

#include <string>

namespace rhombus
{
    class Rhombus
    {
    public:
        std::string type;
        int cost;
        float scale;
        double lastProjectileElapsedTime;
        bool readyToFire;
        bool isKilled;

        Rhombus();
        Rhombus(const std::string& type, int cost, float scale, double lastProjectileElapsedTime, bool readyToFire, bool isKilled);
    };
}
