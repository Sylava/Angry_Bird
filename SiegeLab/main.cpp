#include "raylib.h"

#include "input_controller.h"
#include "orbit_camera.h"

int main()
{
    InitWindow(1280, 720, "SiegeLab - Orbit Camera");
    SetTargetFPS(60);

    siege_lab::OrbitCamera camera({ 0, 1, 0 }, 0, 30, 10);
    siege_lab::InputController input_controller;

    while (!WindowShouldClose())
    {
        camera.Update(input_controller.Capture(), GetFrameTime());

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera.GetCamera());
        DrawGrid(20, 1.0f);
        DrawCube({ 0, 1, 0 }, 2, 2, 2, RED);
        DrawCubeWires({ 0, 1, 0 }, 2, 2, 2, BLACK);
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}