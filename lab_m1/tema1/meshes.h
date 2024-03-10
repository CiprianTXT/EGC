#pragma once

#include "core/gpu/mesh.h"

namespace meshes
{
    class Meshes
    {
    public:
        Mesh* deadzone;
        Mesh* tile;
        
        Mesh* healthFrame;
        Mesh* health;
        Mesh* cheatHealth;

        Mesh* frame;
        Mesh* lockedFrame;
        Mesh* frameStar;
        Mesh* cheatStar;
        Mesh* star;

        Mesh* frameRhombus1;
        Mesh* frameRhombus2;
        Mesh* frameRhombus3;
        Mesh* frameRhombus4;

        Mesh* rhombus1;
        Mesh* rhombus2;
        Mesh* rhombus3;
        Mesh* rhombus4;

        Mesh* hexagon1;
        Mesh* hexagon2;
        Mesh* hexagon3;
        Mesh* hexagon4;

        Mesh* projectile1;
        Mesh* projectile2;
        Mesh* projectile3;
        Mesh* projectile4;

        Meshes();
        ~Meshes();
    };
}
