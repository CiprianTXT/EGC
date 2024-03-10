#pragma once

namespace building
{
    class Building
    {
    public:
        float xCoord;
        float yHeight;
        float zCoord;
        float length;
        float width;

        Building();
        Building(float xCoord, float yHeight, float zCoord, float length, float width);
    };
}
