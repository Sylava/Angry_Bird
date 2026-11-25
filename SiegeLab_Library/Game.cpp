#include "Game.h"

#include "raylib.h"

#include "shot_settings.h"

namespace siege_lab
{
    Game::Game()
        : m_camera({ 0, 1, 0 }, 0, 30, 10),
        m_launcher({ -8, 1, 0 }, 0, 30, 16)
    {
        m_camera_manager.SetController(&m_camera);
    }

    void Game::Run()
    {
        InitWindow(1280, 720, "SiegeLab");
        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            Update();
            Draw();
        }

        CloseWindow();
    }

    void Game::Update()
    {
        float dt = GetFrameTime();
        InputSnapshot input = m_input_controller.Capture();

        m_camera_manager.Update(input, dt);
        m_launcher.Update(input, dt);
    }

    void Game::Draw()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(m_camera_manager.GetCamera());

        DrawLauncher();
        DrawGrid(20, 1.0f);
        DrawCube({ 0, 1, 0 }, 2, 2, 2, RED);
        DrawCubeWires({ 0, 1, 0 }, 2, 2, 2, BLACK);

        EndMode3D();

        DrawHud();
        DrawFPS(10, 10);

        EndDrawing();
    }

    void Game::DrawLauncher() const
    {
        ShotSettings settings = m_launcher.GetShotSettings();

        DrawSphere(settings.origin, 0.2f, DARKGRAY);

        Vector3 aim_end =
        {
          settings.origin.x + settings.direction.x * 3.0f,
          settings.origin.y + settings.direction.y * 3.0f,
          settings.origin.z + settings.direction.z * 3.0f
        };

        DrawLine3D(settings.origin, aim_end, RED);
        DrawSphere(aim_end, 0.08f, RED);
    }

    void Game::DrawHud() const
    {
        ShotSettings settings = m_launcher.GetShotSettings();

        DrawText(TextFormat("Yaw: %.1f", m_launcher.GetYaw()),
            10, 40, 20, BLACK);

        DrawText(TextFormat("Pitch: %.1f", m_launcher.GetPitch()),
            10, 65, 20, BLACK);

        DrawText(TextFormat("Speed: %.1f m/s", m_launcher.GetSpeed()),
            10, 90, 20, BLACK);

        DrawText(
            settings.projectile_kind == ProjectileKind::kStandard
            ? "Projectile: Standard" : "Projectile: Heavy",
            10, 115, 20, BLACK);
    }
}