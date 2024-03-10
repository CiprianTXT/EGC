#pragma once

#include "core/gpu/mesh.h"

namespace objects
{
    class Objects
    {
    public:
        static Mesh* CreateRectangle(const std::string& name, glm::vec3 corner, float width, float height, glm::vec3 color, bool fill = false);
        static Mesh* CreateRhombus(const std::string& name, glm::vec3 corner, float width, float height, glm::vec3 color);
        static Mesh* CreateHexagon(const std::string& name, glm::vec3 center, double radius, glm::vec3 color, glm::vec3 accentColor);
        static Mesh* CreateStar(const std::string& name, glm::vec3 center, double radius, glm::vec3 color);
    };
}
