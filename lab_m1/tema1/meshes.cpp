#include "meshes.h"

#include "transform2D.h"
#include "objects.h"

using namespace meshes;
using namespace objects;

Meshes::Meshes()
{
    // Creating dead zone shape
    auto dzCorner = glm::vec3(20, 30, -1);
    float dzWidth = 70;
    float dzHeight = 420;
    auto dzColor = glm::vec3(0.8f, 0, 0);
    deadzone = Objects::CreateRectangle("deadzone", dzCorner, dzWidth, dzHeight, dzColor, true);

    // Creating tile shape
    auto tileCorner = glm::vec3(120, 330, -1);
    float tileLength = 120;
    auto tileColor = glm::vec3(0, 0.5f, 0);
    tile = Objects::CreateRectangle("tile", tileCorner, tileLength, tileLength, tileColor, true);

    // Creating GUI health bar
    auto healthFrameCorner = glm::vec3(1200, 570, -1);
    float healthFrameWidth = 360;
    float healthFrameHeight = 120;
    auto healthFrameColor = glm::vec3(0, 0, 0);
    healthFrame = Objects::CreateRectangle("healthFrame", healthFrameCorner, healthFrameWidth, healthFrameHeight, healthFrameColor);

    auto healthCorner = glm::vec3(1090, 580, -1);
    float healthLength = 100;
    auto healthColor = glm::vec3(0.8f, 0, 0);
    health = Objects::CreateRectangle("health", healthCorner, healthLength, healthLength, healthColor, true);

    // Creating cheat health bar for GUI
    auto cheatHealthCorner = glm::vec3(1090, 580, -1);
    float cheatHealthWidth = 340;
    float cheatHealthHeight = 100;
    auto cheatHealthColor = glm::vec3(0.8f, 0, 0);
    cheatHealth = Objects::CreateRectangle("cheatHealth", cheatHealthCorner, cheatHealthWidth, cheatHealthHeight, cheatHealthColor, true);

    // Creating GUI rhombus frames
    auto frameCorner = glm::vec3(80, 570, -1);
    float frameLength = 120;
    auto frameColor = glm::vec3(0, 0, 0);
    frame = Objects::CreateRectangle("frame", frameCorner, frameLength, frameLength, frameColor);

    // Creating GUI locked frames
    auto lockedFrameCorner = glm::vec3(80, 570, -1);
    float lockedFrameLength = 120;
    auto lockedFrameColor = glm::vec3(0.8f, 0, 0);
    lockedFrame = Objects::CreateRectangle("lockedFrame", lockedFrameCorner, lockedFrameLength, lockedFrameLength, lockedFrameColor);

    // Creating star for GUI rhombus frames
    auto frameStarCenter = frameCorner - glm::vec3(0, 30, 0);
    double frameStarRadius = 20;
    auto frameStarColor = glm::vec3(0.5f, 0.5f, 0.5f);
    frameStar = Objects::CreateStar("frameStar", frameStarCenter, frameStarRadius, frameStarColor);

    // Creating cheat star for GUI
    auto cheatStarCenter = frameCorner - glm::vec3(0, 30, 0);
    double cheatStarRadius = 20;
    auto cheatStarColor = glm::vec3(0.8f, 0.8f, 0);
    cheatStar = Objects::CreateStar("cheatStar", cheatStarCenter, cheatStarRadius, cheatStarColor);

    // Creating collectible star
    auto starCenter = glm::vec3(0, 0, 3);
    double starRadius = 31;
    auto starColor = glm::vec3(1, 0, 0.8f);
    star = Objects::CreateStar("star", starCenter, starRadius, starColor);

    // Defining colors for rhombuses, hexagons and projectiles
    auto orange = glm::vec3(0.8f, 0.4f, 0);
    auto accentOrange = glm::vec3(1, 0.65f, 0.3f);

    auto blue = glm::vec3(0, 0, 1);
    auto accentBlue = glm::vec3(0, 0.5f, 1);

    auto yellow = glm::vec3(0.8f, 0.8f, 0);
    auto accentYellow = glm::vec3(1, 1, 0.5f);

    auto purple = glm::vec3(0.5, 0, 1);
    auto accentPurple = glm::vec3(0.7f, 0.4f, 1);

    // Creating rhombuses
    auto frameRhombusCorner = glm::vec3(105, 580, -1);
    auto rhombusCorner = glm::vec3(-20, -50, 1);
    float rhombusWidth = 40;
    float rhombusHeight = 100;

    frameRhombus1 = Objects::CreateRhombus("frameRhombus1", frameRhombusCorner, rhombusWidth, rhombusHeight, orange);
    rhombus1 = Objects::CreateRhombus("rhombus1", rhombusCorner, rhombusWidth, rhombusHeight, orange);

    frameRhombus2 = Objects::CreateRhombus("frameRhombus2", frameRhombusCorner, rhombusWidth, rhombusHeight, blue);
    rhombus2 = Objects::CreateRhombus("rhombus2", rhombusCorner, rhombusWidth, rhombusHeight, blue);

    frameRhombus3 = Objects::CreateRhombus("frameRhombus3", frameRhombusCorner, rhombusWidth, rhombusHeight, yellow);
    rhombus3 = Objects::CreateRhombus("rhombus3", rhombusCorner, rhombusWidth, rhombusHeight, yellow);

    frameRhombus4 = Objects::CreateRhombus("frameRhombus4", frameRhombusCorner, rhombusWidth, rhombusHeight, purple);
    rhombus4 = Objects::CreateRhombus("rhombus4", rhombusCorner, rhombusWidth, rhombusHeight, purple);

    // Creating hexagons
    auto hexagonCenter = glm::vec3(0, 0, 2);
    double hexagonRadius = 45;

    hexagon1 = Objects::CreateHexagon("hexagon1", hexagonCenter, hexagonRadius, orange, accentOrange);
    hexagon2 = Objects::CreateHexagon("hexagon2", hexagonCenter, hexagonRadius, blue, accentBlue);
    hexagon3 = Objects::CreateHexagon("hexagon3", hexagonCenter, hexagonRadius, yellow, accentYellow);
    hexagon4 = Objects::CreateHexagon("hexagon4", hexagonCenter, hexagonRadius, purple, accentPurple);

    // Creating projectiles
    auto projectileCenter = glm::vec3(0, 0, 1);
    double projectileRadius = 45;

    projectile1 = Objects::CreateStar("projectile1", projectileCenter, projectileRadius, orange);
    projectile2 = Objects::CreateStar("projectile2", projectileCenter, projectileRadius, blue);
    projectile3 = Objects::CreateStar("projectile3", projectileCenter, projectileRadius, yellow);
    projectile4 = Objects::CreateStar("projectile4", projectileCenter, projectileRadius, purple);
}

Meshes::~Meshes()
{
    deadzone->ClearData();
    tile->ClearData();

    healthFrame->ClearData();
    health->ClearData();
    cheatHealth->ClearData();

    frame->ClearData();
    lockedFrame->ClearData();
    frameStar->ClearData();
    cheatStar->ClearData();
    star->ClearData();

    frameRhombus1->ClearData();
    frameRhombus2->ClearData();
    frameRhombus3->ClearData();
    frameRhombus4->ClearData();

    rhombus1->ClearData();
    rhombus2->ClearData();
    rhombus3->ClearData();
    rhombus4->ClearData();

    hexagon1->ClearData();
    hexagon2->ClearData();
    hexagon3->ClearData();
    hexagon4->ClearData();

    projectile1->ClearData();
    projectile2->ClearData();
    projectile3->ClearData();
    projectile4->ClearData();
}
