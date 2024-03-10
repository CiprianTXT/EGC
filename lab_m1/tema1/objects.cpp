#include "objects.h"

#include <string>
#include <cmath>

#include "core/gpu/mesh.h"

using namespace objects;

#define SIN(x) sin((x) * M_PI / 180)
#define COS(x) cos((x) * M_PI / 180)

Mesh* Objects::CreateRectangle(const std::string& name, const glm::vec3 corner, const float width, const float height, const glm::vec3 color,
                             bool fill)
{
    const auto rectangle = new Mesh(name);

    std::vector<unsigned int> indices = {0, 1, 2, 3};
    const std::vector<VertexFormat> vertices
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    if (!fill)
    {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else
    {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* Objects::CreateRhombus(const std::string& name, const glm::vec3 corner, const float width, const float height, const glm::vec3 color)
{
    const auto rhombus = new Mesh(name);

    const std::vector<unsigned int> indices
    {
        0, 3, 7,
        1, 2, 3,
        2, 4, 3,
        4, 5, 3,
        3, 6, 7
    };
    const std::vector<VertexFormat> vertices
    {
        VertexFormat(corner + glm::vec3(width / 2, 0, 0), color),
        VertexFormat(corner + glm::vec3(width * 0.9, height * 0.4, 0), color),
        VertexFormat(corner + glm::vec3(width * 1.8, height * 0.4, 0), color),
        VertexFormat(corner + glm::vec3(width, height / 2, 0), color),
        VertexFormat(corner + glm::vec3(width * 1.8, height * 0.6, 0), color),
        VertexFormat(corner + glm::vec3(width * 0.9, height * 0.6, 0), color),
        VertexFormat(corner + glm::vec3(width / 2, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height / 2, 0), color)
    };

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

Mesh* Objects::CreateHexagon(const std::string& name, const glm::vec3 center, const double radius, const glm::vec3 color,
                             const glm::vec3 accentColor)
{
    const auto hexagon = new Mesh(name);

    const std::vector<unsigned int> indices
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1,
        0, 7, 8,
        0, 8, 9,
        0, 9, 10,
        0, 10, 11,
        0, 11, 12,
        0, 12, 7
    };
    const std::vector<VertexFormat> vertices
    {
        VertexFormat(center, accentColor),
        VertexFormat(center + glm::vec3(0, -radius * 0.7, 0), accentColor),
        VertexFormat(center + glm::vec3(radius * 0.7 * sqrt(3) / 2, -radius * 0.7 / 2, 0), accentColor),
        VertexFormat(center + glm::vec3(radius * 0.7 * sqrt(3) / 2, radius * 0.7 / 2, 0), accentColor),
        VertexFormat(center + glm::vec3(0, radius * 0.7, 0), accentColor),
        VertexFormat(center + glm::vec3(-radius * 0.7 * sqrt(3) / 2, radius * 0.7 / 2, 0), accentColor),
        VertexFormat(center + glm::vec3(-radius * 0.7 * sqrt(3) / 2, -radius * 0.7 / 2, 0), accentColor),

        VertexFormat(center + glm::vec3(0, -radius, 0), color),
        VertexFormat(center + glm::vec3(radius * sqrt(3) / 2, -radius / 2, 0), color),
        VertexFormat(center + glm::vec3(radius * sqrt(3) / 2, radius / 2, 0), color),
        VertexFormat(center + glm::vec3(0, radius, 0), color),
        VertexFormat(center + glm::vec3(-radius * sqrt(3) / 2, radius / 2, 0), color),
        VertexFormat(center + glm::vec3(-radius * sqrt(3) / 2, -radius / 2, 0), color)
    };

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* Objects::CreateStar(const std::string& name, const glm::vec3 center, const double radius, const glm::vec3 color)
{
    const auto star = new Mesh(name);
    const double innerRadius = radius * 0.4;

    const std::vector<unsigned int> indices
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9,
        0, 9, 10,
        0, 10, 1
    };
    const std::vector<VertexFormat> vertices
    {
        VertexFormat(center, color),
        VertexFormat(center + glm::vec3(innerRadius * COS(270), innerRadius * SIN(270), 0), color),
        VertexFormat(center + glm::vec3(radius * COS(306), radius * SIN(306), 0), color),
        VertexFormat(center + glm::vec3(innerRadius * COS(342), innerRadius * SIN(342), 0), color),
        VertexFormat(center + glm::vec3(radius * COS(18), radius * SIN(18), 0), color),
        VertexFormat(center + glm::vec3(innerRadius * COS(54), innerRadius * SIN(54), 0), color),
        VertexFormat(center + glm::vec3(radius * COS(90), radius * SIN(90), 0), color),
        VertexFormat(center + glm::vec3(innerRadius * COS(126), innerRadius * SIN(126), 0), color),
        VertexFormat(center + glm::vec3(radius * COS(162), radius * SIN(162), 0), color),
        VertexFormat(center + glm::vec3(innerRadius * COS(198), innerRadius * SIN(198), 0), color),
        VertexFormat(center + glm::vec3(radius * COS(234), radius * SIN(234), 0), color)
    };

    star->InitFromData(vertices, indices);
    return star;
}
