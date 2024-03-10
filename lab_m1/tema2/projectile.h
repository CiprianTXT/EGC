#pragma once

namespace projectile3D
{
    class Projectile
    {
    public:
        float xCoord;
        float yCoord;
        float zCoord;
        float rotation;
        double shotElapsedTime;
        bool isFromPlayer;
        bool isHit;

        Projectile();
        Projectile(float xCoord, float yCoord, float zCoord, float rotation, double shotElapsedTime, bool isFromPlayer, bool isHit);
    };
}
