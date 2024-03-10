#pragma once

#include <string>

namespace hexagon
{
    class Hexagon
    {
    public:
        std::string type;
        float scale;
        float xCoord;
        float yCoord;
        int hp;
        bool isKilled;

        Hexagon();
        Hexagon(const std::string& type, float scale, float xCoord, float yCoord, int hp, bool isKilled);
    };
}
