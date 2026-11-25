#include "raylib.h"

#include "input_controller.h"
#include "orbit_camera.h"
#include "camera_manager.h"
#include "launcher.h"
#include "shot_settings.h"

int main()
{
  InitWindow(1280, 720, "SiegeLab - Orbit Camera");
  SetTargetFPS(60);

  siege_lab::OrbitCamera camera({0, 1, 0}, 0, 30, 10);
  siege_lab::CameraManager camera_manager;
  camera_manager.SetController(&camera);
  siege_lab::InputController input_controller;
  siege_lab::Launcher launcher(
      { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);
  while (!WindowShouldClose())
  {
    
      float dt = GetFrameTime();
      siege_lab::InputSnapshot input = input_controller.Capture();

      camera_manager.Update(input, dt);
      launcher.Update(input, dt);

      siege_lab::ShotSettings settings = launcher.GetShotSettings();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera_manager.GetCamera());
    DrawSphere(settings.origin, 0.2f, DARKGRAY);

    Vector3 aim_end =
    {
        settings.origin.x + settings.direction.x * 3.0f,
        settings.origin.y + settings.direction.y * 3.0f,
        settings.origin.z + settings.direction.z * 3.0f
    };

    DrawLine3D(settings.origin, aim_end, RED);
    DrawSphere(aim_end, 0.08f, RED);
    DrawGrid(20, 1.0f);
    DrawCube({0, 1, 0}, 2, 2, 2, RED);
    DrawCubeWires({0, 1, 0}, 2, 2, 2, BLACK);
    EndMode3D();
    DrawText(TextFormat("Yaw: %.1f", launcher.GetYaw()),
        10, 40, 20, BLACK);

    DrawText(TextFormat("Pitch: %.1f", launcher.GetPitch()),
        10, 65, 20, BLACK);

    DrawText(TextFormat("Speed: %.1f m/s", launcher.GetSpeed()),
        10, 90, 20, BLACK);

    DrawText(
        settings.projectile_kind == siege_lab::ProjectileKind::kStandard
        ? "Projectile: Standard" : "Projectile: Heavy",
        10, 115, 20, BLACK);
    DrawFPS(10, 10);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}