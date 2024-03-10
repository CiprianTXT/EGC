#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>


using namespace std;
using namespace m1;
using namespace camera;

using namespace tank;


#define SIN(x) static_cast<float>(sin((x) * M_PI / 180))
#define COS(x) static_cast<float>(cos((x) * M_PI / 180))


Tema2::Tema2() = default;


Tema2::~Tema2() = default;


void Tema2::LoadMeshes()
{
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("building");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tracks");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tracks.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("body");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "body.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turret");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "turret.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cannon");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "cannon.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
}


void Tema2::LoadShader()
{
    // Create a shader program for drawing face polygon with the color of the normal
    Shader *shader = new Shader("Shader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);

    lightPosition = glm::vec3(0, 500, 0);
    materialShininess = 30;
    materialKd = 0.3f;
    materialKs = 0.3f;
}


void Tema2::SpawnPlayer()
{
    const float randX = static_cast<float>(-50 + rand() % 101);
    const float randZ = static_cast<float>(-50 + rand() % 101);

    player = Tank(
        randX,
        randZ,
        90.0f,
        0.0f,
        5,
        "player",
        glm::vec3(0, 0.25, 0),
        -1,
        0,
        0,
        0,
        false,
        false
        );
}


void Tema2::SpawnBuildings()
{
    const int numberOfBuildings = 10 + rand() % 6;
    for (int i = 0; i < numberOfBuildings; i++)
    {
        float randX = static_cast<float>(-100 + rand() % 201);
        float randY = static_cast<float>(10 + rand() % 16);
        float randZ = static_cast<float>(-100 + rand() % 201);
        float randLength = static_cast<float>(10 + rand() % 11);
        float randWidth = static_cast<float>(10 + rand() % 11);
        while (glm::distance(glm::vec2(player.xCoord, player.zCoord), glm::vec2(randX, randZ)) < fmin(randLength, randWidth))
        {
            randX = static_cast<float>(-100 + rand() % 201);
            randZ = static_cast<float>(-100 + rand() % 201);
        }

        buildings.emplace(buildings.end(), randX, randY, randZ, randLength, randWidth);
    }
}


void Tema2::SpawnEnemies()
{
    const int numberOfEnemies = 5 + rand() % 6;
    for (int i = 0; i < numberOfEnemies; i++)
    {
        const int maxColorIndex = rand() % 3;
        int colorIndex = maxColorIndex;
        while (colorIndex == maxColorIndex)
        {
            colorIndex = rand() % 3;
        }
        float randColor[3] = {0, 0, 0};
        randColor[maxColorIndex] = 0.5f;
        randColor[colorIndex] = static_cast<float>(rand()) / RAND_MAX / 0.5f;

        float randX = static_cast<float>(-100 + rand() % 201);
        float randZ = static_cast<float>(-100 + rand() % 201);
        float randRotation = static_cast<float>(rand() % 361);
        for (auto building = buildings.begin(); building != buildings.end(); ++building)
        {
            if (glm::distance(glm::vec2(building->xCoord, building->zCoord), glm::vec2(randX, randZ)) < fmin(building->length, building->width) ||
                glm::distance(glm::vec2(player.xCoord, player.zCoord), glm::vec2(randX, randZ)) < 7)
            {
                randX = static_cast<float>(-100 + rand() % 201);
                randZ = static_cast<float>(-100 + rand() % 201);
                building = buildings.begin();
            }
        }

        enemies.emplace(enemies.end(),
            randX,
            randZ,
            randRotation,
            0.0f,
            3,
            "enemy",
            glm::vec3(randColor[0],randColor[1],randColor[2]),
            -1,
            0,
            0,
            0,
            false,
            false
            );
    }
}


void Tema2::RenderSimpleMesh(const Mesh *mesh, const Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light properties
    const int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

    // Set eye position (camera position) uniform
    const glm::vec3 eyePosition = camera->position;
    const int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color)
    const int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    const int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    const int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    const int is_rendering_enemy_tank = glGetUniformLocation(shader->program, "is_rendering_enemy_tank");
    glUniform1i(is_rendering_enemy_tank, isRenderingEnemyTank);

    const int shader_tank_hp = glGetUniformLocation(shader->program, "shader_tank_hp");
    glUniform1i(shader_tank_hp, shaderTankHp);

    const int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    // Bind model matrix
    const GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    const glm::mat4 viewMatrix = camera->GetViewMatrix();
    const int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    const int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, nullptr);
}


void Tema2::RenderGround()
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(8));
    RenderSimpleMesh(meshes["plane"], shaders["Shader"], modelMatrix, glm::vec3(0, 0.65, 0));
}


void Tema2::RenderBuildings()
{
    for (const auto& building: buildings)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(building.xCoord, building.yHeight / 2, building.zCoord));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(building.length, building.yHeight, building.width));
        RenderSimpleMesh(meshes["building"], shaders["Shader"], modelMatrix, glm::vec3(0.65, 0.65, 0.65));
    }
}


void Tema2::RenderTanks()
{
    for (int i = -1; i < static_cast<int>(enemies.size()); i++)
    {
        const Tank currentRenderingTank = i == -1 ? player : enemies[i];
        isRenderingEnemyTank = currentRenderingTank.type != "player";
        shaderTankHp = 3 - currentRenderingTank.hp;

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(currentRenderingTank.xCoord, 0, currentRenderingTank.zCoord));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(currentRenderingTank.rotation), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["tracks"], shaders["Shader"], modelMatrix, glm::vec3(0.5, 0.5, 0.5));
        RenderSimpleMesh(meshes["body"], shaders["Shader"], modelMatrix, currentRenderingTank.color);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(currentRenderingTank.xCoord, 0, currentRenderingTank.zCoord));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(currentRenderingTank.rotation), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(SIN(currentRenderingTank.rotation) - 1, 0, -COS(currentRenderingTank.rotation)));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(currentRenderingTank.turretRotation), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["turret"], shaders["Shader"], modelMatrix, currentRenderingTank.color + glm::vec3(0.25));
        if (!currentRenderingTank.isKilled)
        {
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.5, 0));
            RenderSimpleMesh(meshes["cannon"], shaders["Shader"], modelMatrix, glm::vec3(0.5, 0.5, 0.5));
        }

        isRenderingEnemyTank = false;
    }
}


void Tema2::RenderProjectiles(const float deltaTimeSeconds)
{
    for (auto projectile = projectiles.begin(); projectile != projectiles.end(); ++projectile)
    {
        const double shotTime = Engine::GetElapsedTime() - projectile->shotElapsedTime;
        if (projectile->isHit || shotTime >= 5)
        {
            projectile = projectiles.erase(projectile);
            if (projectile == projectiles.end())
            {
                break;
            }
        }
        else
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(projectile->xCoord, projectile->yCoord, projectile->zCoord));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
            RenderSimpleMesh(meshes["projectile"], shaders["Shader"], modelMatrix, glm::vec3(0.15f, 0.15f, 0.15f));
            projectile->xCoord += 20 * deltaTimeSeconds * COS(projectile->rotation);
            projectile->zCoord -= 20 * deltaTimeSeconds * SIN(projectile->rotation);
        }
    }
}


void Tema2::EnemiesAutopilot(const float deltaTimeSeconds)
{
    for (auto& enemy: enemies)
    {
        if (!enemy.isKilled)
        {
            const glm::vec3 playerPosition = glm::vec3(player.xCoord, 0, player.zCoord);
            const glm::vec3 enemyPosition = glm::vec3(enemy.xCoord, 0, enemy.zCoord);
            const glm::vec3 enemyTurretPosition = glm::vec3(enemy.xCoord - COS(enemy.rotation), 0, enemy.zCoord + SIN(enemy.rotation));
            const glm::vec3 enemyMuzzlePosition = glm::vec3(
                enemyTurretPosition.x + 5.9f * COS(enemy.rotation + enemy.turretRotation),
                enemyTurretPosition.y,
                enemyTurretPosition.z - 5.9f * SIN(enemy.rotation + enemy.turretRotation)
                );
            const glm::vec3 enemyTurretDirection = glm::normalize(enemyMuzzlePosition - enemyTurretPosition);

            if (glm::distance(enemyPosition, playerPosition) > 30)
            {
                if (enemy.action == -1 || Engine::GetElapsedTime() - enemy.lastActionTime >= static_cast<double>(enemy.actionCost))
                {
                    enemy.action = rand() % 4;
                    if (enemy.action <= 1)
                    {
                        enemy.actionCost = rand() % 5;
                    }
                    else
                    {
                        enemy.actionCost = rand() % 3;
                    }
                    enemy.lastActionTime = Engine::GetElapsedTime();
                }

                switch (enemy.action)
                {
                case 0:
                    enemy.xCoord += deltaTimeSeconds * tankSpeed * COS(enemy.rotation);
                    enemy.zCoord -= deltaTimeSeconds * tankSpeed * SIN(enemy.rotation);
                    break;

                case 1:
                    enemy.xCoord -= deltaTimeSeconds * tankSpeed * COS(enemy.rotation);
                    enemy.zCoord += deltaTimeSeconds * tankSpeed * SIN(enemy.rotation);
                    break;

                case 2:
                    enemy.rotation += deltaTimeSeconds * tankRotationSpeed;
                    break;

                case 3:
                    enemy.rotation -= deltaTimeSeconds * tankRotationSpeed;
                    break;

                default:
                    break;
                }
            }
            else if (!enemy.hasCooldown)
            {
                glm::vec3 playerDirection = glm::normalize(playerPosition - enemyTurretPosition);
                if (glm::distance(playerDirection, enemyTurretDirection) < 0.01)
                {
                    enemy.lastShotElapsedTime = Engine::GetElapsedTime();
                    enemy.hasCooldown = true;
                    projectiles.emplace(projectiles.end(), enemy.Shoot());
                }
                else
                {
                    enemy.turretRotation += deltaTimeSeconds * 50;
                }
            }
        }
    }
}


void Tema2::CheckTanks()
{
    for (int i = -1; i < static_cast<int>(enemies.size()); i++)
    {
        Tank& currentTank = i == -1 ? player : enemies[i];

        // Check current tank health
        if (currentTank.hp <= 0)
        {
            currentTank.hasCooldown = true;
            currentTank.isKilled = true;
        }

        // Checking projectile-tank collision
        for (auto& projectile: projectiles)
        {
            const float projTankDistance = glm::distance(
                glm::vec3(projectile.xCoord, projectile.yCoord, projectile.zCoord),
                glm::vec3(currentTank.xCoord, 0, currentTank.zCoord)
                );
            if (projTankDistance < 3.367f)
            {
                projectile.isHit = true;
                if (!currentTank.isKilled)
                {
                    currentTank.hp--;
                    if (currentTank.hp <= 0)
                    {
                        currentTank.isKilled = true;
                        currentTank.action = -1;
                        currentTank.actionCost = 0;
                        currentTank.hasCooldown = true;
                        score = projectile.isFromPlayer ? score + 1 : score;
                    }
                }
            }
        }

        // Checking tank-tank collision
        for (int j = i + 1; j < static_cast<int>(enemies.size()); j++)
        {
            Tank& comparisionTank = enemies[j];

            const float tankTankDistance = glm::distance(
                glm::vec3(currentTank.xCoord, 0, currentTank.zCoord),
                glm::vec3(comparisionTank.xCoord, 0, comparisionTank.zCoord)
                );
            if (tankTankDistance < 6.58574f)
            {
                const glm::vec3 dif =
                    glm::vec3(comparisionTank.xCoord, 0, comparisionTank.zCoord) - glm::vec3(currentTank.xCoord, 0, currentTank.zCoord);
                const glm::vec3 overlap = std::abs(6.58574f - tankTankDistance) * glm::normalize(dif);
                currentTank.xCoord += overlap.x * -0.5f;
                currentTank.zCoord += overlap.z * -0.5f;
                comparisionTank.xCoord += overlap.x * 0.5f;
                comparisionTank.zCoord += overlap.z * 0.5f;
            }
        }

        // Checking tank-building collision
        for (const auto& building: buildings)
        {
            float tankBuildingDistance, radiusSum;
            if (currentTank.xCoord >= building.xCoord - building.length / 2 &&
                currentTank.xCoord <= building.xCoord + building.length / 2)
            {
                tankBuildingDistance = glm::distance(
                    glm::vec3(currentTank.xCoord, 0, currentTank.zCoord),
                    glm::vec3(currentTank.xCoord, 0, building.zCoord)
                    );
                radiusSum = 3.29287f + building.width / 2;
            }
            else if (currentTank.zCoord >= building.zCoord - building.width / 2 &&
                currentTank.zCoord <= building.zCoord + building.width / 2)
            {
                tankBuildingDistance = glm::distance(
                    glm::vec3(currentTank.xCoord, 0, currentTank.zCoord),
                    glm::vec3(building.xCoord, 0, currentTank.zCoord)
                    );
                radiusSum = 3.29287f + building.length / 2;
            }
            else
            {
                continue;
            }

            if (tankBuildingDistance < radiusSum)
            {
                const glm::vec3 dif =
                    glm::vec3(building.xCoord, 0, building.zCoord) - glm::vec3(currentTank.xCoord, 0, currentTank.zCoord);
                const glm::vec3 overlap = std::abs(radiusSum - tankBuildingDistance) * glm::normalize(dif);
                currentTank.xCoord += overlap.x * -0.5f;
                currentTank.zCoord += overlap.z * -0.5f;
            }
        }

        // Checking current tank's shoot cooldown
        const double lastShotTime = Engine::GetElapsedTime() - currentTank.lastShotElapsedTime;
        if (!currentTank.isKilled && currentTank.hasCooldown && lastShotTime >= 1)
        {
            currentTank.hasCooldown = false;
        }
    }
}


void Tema2::CheckProjectiles()
{
    // Checking projectile-building collision
    for (auto& projectile: projectiles)
    {
        for (const auto& building: buildings)
        {
            if (projectile.xCoord >= building.xCoord - building.length / 2 &&
                projectile.xCoord <= building.xCoord + building.length / 2 &&
                projectile.zCoord >= building.zCoord - building.width / 2 &&
                projectile.zCoord <= building.zCoord + building.width / 2)
            {
                projectile.isHit = true;
            }
        }
    }
}


void Tema2::Init()
{
    LoadMeshes();
    LoadShader();

    score = 0;
    isGameFrozen = false;
    tankSpeed = 10;
    tankRotationSpeed = 50;
    mouseRotation = 0;

    isRenderingEnemyTank = false;
    shaderTankHp = 0;

    srand(static_cast<unsigned int>(time(nullptr)));
    SpawnPlayer();
    SpawnBuildings();
    SpawnEnemies();

    camera = new Camera(glm::vec3(0, 2, 3.5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    // Also sets the sky color :)
    glClearColor(0.53f, 0.81f, 0.92f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (player.hp <= 0)
    {
        cout << "YOU DIED!\n";
        exit(EXIT_SUCCESS);
    }

    camera->position = glm::vec3(player.xCoord, 2, player.zCoord);
    camera->TranslateForward(-10);

    RenderGround();
    RenderBuildings();
    RenderTanks();
    if (!isGameFrozen)
    {
        RenderProjectiles(deltaTimeSeconds);
    }
    else
    {
        RenderProjectiles(0);
    }

    if (Engine::GetElapsedTime() >= 5 && !isGameFrozen)
    {
        isGameFrozen = true;
        tankSpeed = 0;
        tankRotationSpeed = 0;
        for (int i = -1; i < static_cast<int>(enemies.size()); i++)
        {
            Tank& currentTank = i == -1 ? player : enemies[i];
            currentTank.hasCooldown = true;
        }

        cout << "SCORE: " << score << "\n";
    }

    if (Engine::GetElapsedTime() < 5)
    {
        EnemiesAutopilot(deltaTimeSeconds);

        CheckTanks();
        CheckProjectiles();
    }
}


void Tema2::FrameEnd()
{
}


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    const float lastRotation = player.rotation;
    if (window->KeyHold(GLFW_KEY_W)) {
        player.xCoord += deltaTime * tankSpeed * COS(player.rotation);
        player.zCoord -= deltaTime * tankSpeed * SIN(player.rotation);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        player.rotation += deltaTime * tankRotationSpeed;
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        player.xCoord -= deltaTime * tankSpeed * COS(player.rotation);
        player.zCoord += deltaTime * tankSpeed * SIN(player.rotation);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        player.rotation -= deltaTime * tankRotationSpeed;
    }

    // Keeps the camera behind the player
    camera->RotateThirdPerson_OY(RADIANS(player.rotation - lastRotation));
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Resetting camera rotation if needed
    if (key == GLFW_KEY_SPACE)
    {
        camera->RotateThirdPerson_OY(-mouseRotation);
        mouseRotation = 0;
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        constexpr float sensitivity = 0.001f;
        mouseRotation += sensitivity * static_cast<float>(-deltaX);
        camera->RotateThirdPerson_OY(sensitivity * static_cast<float>(-deltaX));
    }
    else
    {
        player.turretRotation = static_cast<float>(640 - mouseX) * 0.28125f;
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Shooting a projectile if the left mouse button is pressed and the player can shoot
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !player.hasCooldown)
    {
        player.lastShotElapsedTime = Engine::GetElapsedTime();
        player.hasCooldown = true;
        projectiles.emplace(projectiles.end(), player.Shoot());
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
