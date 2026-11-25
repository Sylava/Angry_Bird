#include "input_controller.h"

#include "raylib.h"

namespace siege_lab
{
    InputSnapshot InputController::Capture() const
    {
        InputSnapshot input{};

        input.camera_yaw = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        input.camera_pitch = IsKeyDown(KEY_UP) - IsKeyDown(KEY_DOWN);

        input.launcher_yaw = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
        input.launcher_pitch = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
        input.launcher_speed = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);

        input.select_standard = IsKeyPressed(KEY_ONE);
        input.select_heavy = IsKeyPressed(KEY_TWO);

        Vector2 mouse_delta = GetMouseDelta();
        input.mouse_delta_x = mouse_delta.x;
        input.mouse_delta_y = mouse_delta.y;
        input.mouse_wheel = GetMouseWheelMove();
        input.right_mouse_down = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        return input;
    }
}