#pragma once

#include "components/simple_scene.h"

#include "star.h"
#include "rhombus.h"
#include "hexagon.h"
#include "projectile.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void LoadMeshes();
        
        void RenderGUI();
        void RenderScene(float deltaTimeSeconds);
        void RenderStars(float deltaTimeSeconds);
        void RenderHexagons(float deltaTimeSeconds);
        void RenderProjectiles(float deltaTimeSeconds);
        
        void CheckRhombusSelection();
        void CheckRhombusDrop();
        void CheckRhombusDelete() const;
        void CheckPlayground(double elapsedTime) const;
        void CheckHexagons(double elapsedTime);
        void CheckStarClick();
        
        void GenerateHexagons(double elapsedTime);
        void GenerateStars(double elapsedTime);
        
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

    protected:
        glm::ivec2 currentResolution;
        glm::mat3 modelMatrix;
        
        int health;
        int stars;
        
        std::vector<star::Star> starList;
        std::vector<hexagon::Hexagon> hexagonList[3];
        std::vector<projectile::Projectile> projectileList[3];
        rhombus::Rhombus *(playground[3][3]);

        int xMousePos;
        int yMousePos;

        bool isLeftMouseBtnPressed;
        bool isRightMouseBtnPressed;
        bool isRhombusSelected;
        rhombus::Rhombus selectedRhombus;

        double lastHexagonsElapsedTime;
        double lastStarsElapsedTime;

        std::string cheatCodeBuffer;
        bool infiniteHealth;
        bool infiniteStars;
    };
} // namespace m1
