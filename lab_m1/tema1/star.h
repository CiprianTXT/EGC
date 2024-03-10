#pragma once

namespace star
{
    class Star
    {
    public:
        float xPos;
        float yPos;
        float yStopPos;
        bool isCollected;

        Star();
        Star(float xPos, float yPos, float yStopPos, bool isCollected);
    };
}
