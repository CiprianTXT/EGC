#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"

#include "tank.h"
#include "projectile.h"
#include "building.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void LoadMeshes();
        void LoadShader();

        void SpawnPlayer();
        void SpawnBuildings();
        void SpawnEnemies();

        void RenderSimpleMesh(const Mesh *mesh, const Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color);
        void RenderGround();
        void RenderBuildings();
        void RenderTanks();
        void RenderProjectiles(float deltaTimeSeconds);

        void EnemiesAutopilot(float deltaTimeSeconds);

        void CheckTanks();
        void CheckProjectiles();

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        camera::Camera *camera;
        glm::mat4 projectionMatrix;

        glm::vec3 lightPosition;
        int materialShininess;
        float materialKd;
        float materialKs;

        int score;
        bool isGameFrozen;
        float tankSpeed, tankRotationSpeed;
        float mouseRotation;

        tank::Tank player;
        std::vector<tank::Tank> enemies;
        std::vector<projectile3D::Projectile> projectiles;
        std::vector<building::Building> buildings;

        bool isRenderingEnemyTank;
        int shaderTankHp;
    };
}   // namespace m1
