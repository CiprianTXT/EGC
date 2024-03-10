#include "tema1.h"


#include <iostream>
#include <vector>


#include "transform2D.h"
#include "meshes.h"
#include "star.h"
#include "rhombus.h"
#include "hexagon.h"
#include "projectile.h"


using namespace std;
using namespace m1;
using namespace meshes;
using namespace star;
using namespace rhombus;
using namespace hexagon;
using namespace projectile;


Tema1::Tema1() = default;


Tema1::~Tema1() = default;


void Tema1::LoadMeshes()
{
    // Creating and loading all meshes
    const auto meshes = Meshes();
    AddMeshToList(meshes.deadzone);
    AddMeshToList(meshes.tile);

    AddMeshToList(meshes.healthFrame);
    AddMeshToList(meshes.health);
    AddMeshToList(meshes.cheatHealth);

    AddMeshToList(meshes.frame);
    AddMeshToList(meshes.lockedFrame);
    AddMeshToList(meshes.frameStar);
    AddMeshToList(meshes.cheatStar);
    AddMeshToList(meshes.star);

    AddMeshToList(meshes.frameRhombus1);
    AddMeshToList(meshes.frameRhombus2);
    AddMeshToList(meshes.frameRhombus3);
    AddMeshToList(meshes.frameRhombus4);

    AddMeshToList(meshes.rhombus1);
    AddMeshToList(meshes.rhombus2);
    AddMeshToList(meshes.rhombus3);
    AddMeshToList(meshes.rhombus4);

    AddMeshToList(meshes.hexagon1);
    AddMeshToList(meshes.hexagon2);
    AddMeshToList(meshes.hexagon3);
    AddMeshToList(meshes.hexagon4);

    AddMeshToList(meshes.projectile1);
    AddMeshToList(meshes.projectile2);
    AddMeshToList(meshes.projectile3);
    AddMeshToList(meshes.projectile4);
}


void Tema1::RenderGUI()
{
    // Rendering 1st frame with 1 star cost
    modelMatrix = glm::mat3(1);
    if (stars >= 1)
    {
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    }
    else
    {
        RenderMesh2D(meshes["lockedFrame"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["frameRhombus1"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(60, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);

    // Rendering 2nd frame with 2 star cost
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(180, 0);
    if (stars >= 2)
    {
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    }
    else
    {
        RenderMesh2D(meshes["lockedFrame"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["frameRhombus2"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);

    // Rendering 3rd frame with 2 star cost
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(360, 0);
    if (stars >= 2)
    {
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    }
    else
    {
        RenderMesh2D(meshes["lockedFrame"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["frameRhombus3"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);

    // Rendering 4th frame with 3 star cost
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(540, 0);
    if (stars >= 3)
    {
        RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    }
    else
    {
        RenderMesh2D(meshes["lockedFrame"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["frameRhombus4"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(20, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);

    // Rendering health bar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(-360, 0);
    RenderMesh2D(meshes["healthFrame"], shaders["VertexColor"], modelMatrix);
    if (infiniteHealth)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(-240, 0);
        RenderMesh2D(meshes["cheatHealth"], shaders["VertexColor"], modelMatrix);
    }
    else for (float i = 0; i < (float)health; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(i * -120, 0);
        RenderMesh2D(meshes["health"], shaders["VertexColor"], modelMatrix);
    }

    // Rendering star counter
    for (float i = 0; i < (float)stars; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(i * 40 + 750, 0);
        if (infiniteStars)
        {
            RenderMesh2D(meshes["cheatStar"], shaders["VertexColor"], modelMatrix);
        }
        RenderMesh2D(meshes["frameStar"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::RenderScene(const float deltaTimeSeconds)
{
    // Rendering dead zone
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["deadzone"], shaders["VertexColor"], modelMatrix);

    // Rendering tiles and placed rhombuses
    for (float i = 0; i < 3; i++)
    {
        for (float j = 0; j < 3; j++)
        {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(j * 150, -(i * 150));
            RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(165, 390);
            if (playground[(int)i][(int)j]->isKilled)
            {
                playground[(int)i][(int)j]->scale -= deltaTimeSeconds;
                modelMatrix *= transform2D::Scale(playground[(int)i][(int)j]->scale, playground[(int)i][(int)j]->scale);
                RenderMesh2D(meshes[playground[(int)i][(int)j]->type], shaders["VertexColor"], modelMatrix);
                if (playground[(int)i][(int)j]->scale <= 0)
                {
                    playground[(int)i][(int)j]->type = "none";
                    playground[(int)i][(int)j]->cost = 0;
                    playground[(int)i][(int)j]->scale = 0;
                    playground[(int)i][(int)j]->readyToFire = false;
                    playground[(int)i][(int)j]->isKilled = false;
                }
            }
            else
            {
                RenderMesh2D(meshes[playground[(int)i][(int)j]->type], shaders["VertexColor"], modelMatrix);
            }
        }
    }
}


void Tema1::RenderStars(const float deltaTimeSeconds)
{
    // Removing all stars from list and skipping render if cheat code is triggered
    if (infiniteStars)
    {
        starList.clear();
        return;
    }

    // Cleaning collected stars before rendering randomly generated stars
    for (auto star = starList.begin(); star != starList.end(); ++star)
    {
        if (star->isCollected)
        {
            star = starList.erase(star);
            if (star == starList.end())
            {
                break;
            }
        }
        modelMatrix = glm::mat3(1);
        if (star->yPos >= star->yStopPos)
        {
            star->yPos -= deltaTimeSeconds * 100;
        }
        modelMatrix *= transform2D::Translate((float)star->xPos, (float)star->yPos);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::RenderHexagons(const float deltaTimeSeconds)
{
    for (int i = 0; i < 3; i++)
    {
        for (auto hexagon = hexagonList[i].begin(); hexagon != hexagonList[i].end(); ++hexagon)
        {
            if (hexagon->isKilled)
            {
                hexagon->scale -= deltaTimeSeconds;
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(hexagon->xCoord, hexagon->yCoord);
                modelMatrix *= transform2D::Rotate(0.2f);
                modelMatrix *= transform2D::Scale(hexagon->scale, hexagon->scale);
                RenderMesh2D(meshes[hexagon->type], shaders["VertexColor"], modelMatrix);
                if (hexagon->scale <= 0)
                {
                    hexagon = hexagonList[i].erase(hexagon);
                    if (hexagon == hexagonList[i].end())
                    {
                        break;
                    }
                }
            }
            else
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(hexagon->xCoord, hexagon->yCoord);
                modelMatrix *= transform2D::Rotate(0.2f);
                RenderMesh2D(meshes[hexagon->type], shaders["VertexColor"], modelMatrix);
                hexagon->xCoord -= deltaTimeSeconds * 100;
            }
        }
    }
}


void Tema1::RenderProjectiles(const float deltaTimeSeconds)
{
    for (int i = 0; i < 3; i++)
    {
        for (auto projectile = projectileList[i].begin(); projectile != projectileList[i].end(); ++projectile)
        {
            if (projectile->isHit || projectile->xCoord >= 1330)
            {
                projectile = projectileList[i].erase(projectile);
                if (projectile == projectileList[i].end())
                {
                    break;
                }
            }
            else
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(projectile->xCoord, projectile->yCoord);
                modelMatrix *= transform2D::Rotate(projectile->rotation);
                RenderMesh2D(meshes[projectile->type], shaders["VertexColor"], modelMatrix);
                projectile->rotation -= deltaTimeSeconds * 5;
                projectile->xCoord += deltaTimeSeconds * 200;
            }
        }
    }
}


void Tema1::CheckRhombusSelection()
{
    if ((yMousePos >= 570 && yMousePos <= 690) || isRhombusSelected)
    {
        if (!isRhombusSelected)
        {
            if (xMousePos >= 80 && xMousePos <= 200 && stars >= 1)
            {
                isRhombusSelected = true;
                selectedRhombus.type = "rhombus1";
                selectedRhombus.cost = 1;
            }
            else if (xMousePos >= 260 && xMousePos <= 380 && stars >= 2)
            {
                isRhombusSelected = true;
                selectedRhombus.type = "rhombus2";
                selectedRhombus.cost = 2;
            }
            else if (xMousePos >= 440 && xMousePos <= 560 && stars >= 2)
            {
                isRhombusSelected = true;
                selectedRhombus.type = "rhombus3";
                selectedRhombus.cost = 2;
            }
            else if (xMousePos >= 620 && xMousePos <= 740 && stars >= 3)
            {
                isRhombusSelected = true;
                selectedRhombus.type = "rhombus4";
                selectedRhombus.cost = 3;
            }
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((float)xMousePos, (float)yMousePos);
        RenderMesh2D(meshes[selectedRhombus.type], shaders["VertexColor"], modelMatrix);
    }
}


void Tema1::CheckRhombusDrop()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (playground[i][j]->type == "none" &&
                xMousePos >= 120 + j * 150 && xMousePos <= 240 + j * 150 &&
                yMousePos >= 330 - i * 150 && yMousePos <= 450 - i * 150)
            {
                playground[i][j]->type = selectedRhombus.type;
                playground[i][j]->cost = selectedRhombus.cost;
                playground[i][j]->scale = (float)1;
                playground[i][j]->readyToFire = false;
                stars -= selectedRhombus.cost;
            }
        }
    }
}


void Tema1::CheckRhombusDelete() const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (playground[i][j]->type != "none" &&
                xMousePos >= 120 + j * 150 && xMousePos <= 240 + j * 150 &&
                yMousePos >= 330 - i * 150 && yMousePos <= 450 - i * 150)
            {
                playground[i][j]->readyToFire = false;
                playground[i][j]->isKilled = true;
            }
        }
    }
}


void Tema1::CheckPlayground(const double elapsedTime) const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Updating readyToFire status for placed rhombuses
            if (playground[i][j]->type != "none" && !playground[i][j]->isKilled && (int)playground[i][j]->lastProjectileElapsedTime != 0)
            {
                const double interval = elapsedTime - playground[i][j]->lastProjectileElapsedTime;
                if (!playground[i][j]->readyToFire && interval >= 1.5)
                {
                    playground[i][j]->readyToFire = true;
                }
            }
        }
    }
}


void Tema1::CheckHexagons(const double elapsedTime)
{
    for (int i = 0; i < 3; i++)
    {
        for (auto hexagon = hexagonList[i].begin(); hexagon != hexagonList[i].end(); ++hexagon)
        {
            // Check hexagon HP
            if (hexagon->hp <= 0)
            {
                hexagon->isKilled = true;
            }

            // Check if same rhombus type is on current row
            for (int j = 0; j < 3; j++)
            {
                if (!playground[i][j]->isKilled && playground[i][j]->readyToFire &&
                    playground[i][j]->type.back() == hexagon->type.back())
                {
                    // Firing projectile from same rhombus type if there
                    string projectileType = "projectile";
                    projectileType.push_back(hexagon->type.back());
                    const float projectileX = 240 + (float)j * 150;
                    const float projectileY = 390 - (float)i * 150;

                    projectileList[i].emplace(projectileList[i].end(), projectileType, projectileX, projectileY, (float)0, false);

                    playground[i][j]->lastProjectileElapsedTime = elapsedTime;
                    playground[i][j]->readyToFire = false;
                }
                else if (playground[i][j]->type.back() == hexagon->type.back() &&
                    (int)playground[i][j]->lastProjectileElapsedTime == 0)
                {
                    playground[i][j]->lastProjectileElapsedTime = elapsedTime;
                }
            }

            // Check if hexagon was hit by same projectile type
            for (auto projectile = projectileList[i].begin(); projectile != projectileList[i].end(); ++projectile)
            {
                if (projectile->type.back() == hexagon->type.back() &&
                    glm::distance(glm::vec2(projectile->xCoord, projectile->yCoord), glm::vec2(hexagon->xCoord, hexagon->yCoord)) < 90)
                {
                    hexagon->hp--;
                    projectile->isHit = true;
                }
            }

            // Check if hexagon reached a rhombus
            for (int j = 0; j < 3; j++)
            {
                if (playground[i][j]->type != "none" && !hexagon->isKilled &&
                    hexagon->xCoord + 45 >= 120 + (float)j * 150 && hexagon->xCoord - 45 <= 240 + (float)j * 150)
                {
                    playground[i][j]->readyToFire = false;
                    playground[i][j]->isKilled = true;
                }
            }

            // Check if hexagon reached the dead zone
            if (!hexagon->isKilled && hexagon->xCoord <= 55)
            {
                health--;
                hexagon->isKilled = true;
            }
        }
    }
}


void Tema1::CheckStarClick()
{
    for (auto& star: starList)
    {
        const float leftX = star.xPos - 31;
        const float rightX = star.xPos + 31;
        const float bottomY = star.yPos - 31;
        const float topY = star.yPos + 31;

        // If stars are generated on top of each other, collect only one of them
        if ((float)xMousePos >= leftX && (float)xMousePos <= rightX &&
            (float)yMousePos >= bottomY && (float)yMousePos <= topY)
        {
            stars++;
            star.isCollected = true;
            break;
        }
    }
}


void Tema1::GenerateHexagons(const double elapsedTime)
{
    // Generating hexagons with variable gap between them
    const int rand1 = rand() % 250;
    const int rand2 = rand() % 250;
    const double interval = elapsedTime - lastHexagonsElapsedTime;
    if (interval >= 5 && (interval >= 10 || rand1 == rand2))
    {
        const int randRow = rand() % 3;
        const int randHexagonType = 1 + rand() % 4;
        string randHexagon;
        switch (randHexagonType)
        {
            case 1:
                randHexagon = "hexagon1";
                break;
            case 2:
                randHexagon = "hexagon2";
                break;
            case 3:
                randHexagon = "hexagon3";
                break;
            default:
                randHexagon = "hexagon4";
        }

        // Adding newly generated hexagon to the list
        hexagonList[randRow].emplace(
            hexagonList[randRow].end(),
            randHexagon,
            (float)1,
            (float)1325,
            (float)(390 - randRow * 150),
            3,
            false
            );

        lastHexagonsElapsedTime = elapsedTime;
    }
}


void Tema1::GenerateStars(const double elapsedTime)
{
    // Generating 3 stars at random positions every 10 seconds unless cheat code is triggered
    const double interval = elapsedTime - lastStarsElapsedTime;
    if (!infiniteStars && (interval >= 10 || (elapsedTime > 1 && lastStarsElapsedTime == 0.0)))
    {
        for (int i = 0; i < 3; i++)
        {
            const auto randX = (float)(rand() % 1280);
            const auto randY = (float)(751 + rand() % 200);
            const auto randStopY = (float)(rand() % 720);

            // Adding newly generated star to the list
            starList.emplace(
                starList.end(),
                randX,
                randY,
                randStopY,
                false
                );
        }

        lastStarsElapsedTime = elapsedTime;
    }
}


void Tema1::Init()
{
    currentResolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)currentResolution.x, 0, (float)currentResolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Initializing player stats and misc
    health = 3;
    stars = 5;
    cheatCodeBuffer.append("aaaaaaa");
    infiniteHealth = false;
    infiniteStars = false;

    lastHexagonsElapsedTime = 0;
    lastStarsElapsedTime = 0;

    isLeftMouseBtnPressed = false;
    isRightMouseBtnPressed = false;
    isRhombusSelected = false;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            playground[i][j] = new Rhombus();
        }
    }

    // Initializing all meshes
    LoadMeshes();

    // Initializing seed for rand() function
    srand((unsigned int)time(nullptr));
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.15f, 0.15f, 0.15f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentResolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, currentResolution.x, currentResolution.y);

    // Keeping stats infinite if cheat codes are triggered
    if (infiniteHealth)
    {
        health = 3;
    }
    if (infiniteStars)
    {
        stars = 11;
    }
}


void Tema1::Update(const float deltaTimeSeconds)
{
    // Getting elapsed time for later use
    const double elapsedTime = Engine::GetElapsedTime();

    // Rendering the game GUI
    RenderGUI();

    // Rendering the game scene
    RenderScene(deltaTimeSeconds);

    // Generating and rendering falling stars
    GenerateStars(elapsedTime);
    RenderStars(deltaTimeSeconds);

    // Checking all placed rhombuses
    CheckPlayground(elapsedTime);

    // Rendering and checking incoming hexagons
    RenderHexagons(deltaTimeSeconds);
    CheckHexagons(elapsedTime);

    // Generating hexagon at a minimum interval of 5 seconds
    GenerateHexagons(elapsedTime);

    // Rendering all fired projectiles
    RenderProjectiles(deltaTimeSeconds);

    // Checking player input on GUI for drag and drop
    if (isLeftMouseBtnPressed)
    {
        CheckRhombusSelection();
    }
}


void Tema1::FrameEnd()
{
    // Checking player health
    if (health <= 0)
    {
        exit(EXIT_SUCCESS);
    }
}


void Tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_B)
    {
        cheatCodeBuffer.append("b");
    }

    if (key == GLFW_KEY_C)
    {
        cheatCodeBuffer.append("c");
    }

    if (key == GLFW_KEY_E)
    {
        cheatCodeBuffer.append("e");
    }

    if (key == GLFW_KEY_H)
    {
        cheatCodeBuffer.append("h");
    }

    if (key == GLFW_KEY_I)
    {
        cheatCodeBuffer.append("i");
    }

    if (key == GLFW_KEY_L)
    {
        cheatCodeBuffer.append("l");
    }

    if (key == GLFW_KEY_N)
    {
        cheatCodeBuffer.append("n");
    }

    if (key == GLFW_KEY_O)
    {
        cheatCodeBuffer.append("o");
    }

    if (key == GLFW_KEY_R)
    {
        cheatCodeBuffer.append("r");
    }

    if (key == GLFW_KEY_V)
    {
        cheatCodeBuffer.append("v");
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Checking if buffer is unnecessarily big
    if (cheatCodeBuffer.size() > 10)
    {
        cheatCodeBuffer = cheatCodeBuffer.substr(1, cheatCodeBuffer.size() - 1);
    }

    // Checking if cheat codes were triggered
    if (cheatCodeBuffer.substr(cheatCodeBuffer.size() - 7) == "richboi")
    {
        infiniteStars = true;
    }

    if (cheatCodeBuffer == "invincible")
    {
        infiniteHealth = true;
    }
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Updating current (x, y) mouse click position
    currentResolution = window->GetResolution();
    xMousePos = mouseX;
    yMousePos = currentResolution.y - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Checking if player is holding the left click pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        // Check if click was made on a star
        CheckStarClick();

        isLeftMouseBtnPressed = true;
    }

    // Checking if player is holding the right click pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        // Checking player delete input on playground
        CheckRhombusDelete();
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Checking if player stopped holding the left click pressed
    if (isLeftMouseBtnPressed)
    {
        // Checking the location where the rhombus was dropped
        CheckRhombusDrop();

        isLeftMouseBtnPressed = false;
        isRhombusSelected = false;
        selectedRhombus.type = "none";
        selectedRhombus.cost = 0;
    }
}
