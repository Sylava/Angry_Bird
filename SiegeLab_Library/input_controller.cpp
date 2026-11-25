#include "input_controller.h"

#include "raylib.h"

namespace siege_lab
{
    InputSnapshot InputController::Capture() const
    {
        InputSnapshot input;

        if (IsKeyDown(KEY_D))
            input.camera_yaw += 1.0f;

        if (IsKeyDown(KEY_A))
            input.camera_yaw -= 1.0f;

        if (IsKeyDown(KEY_W))
            input.camera_pitch += 1.0f;

        if (IsKeyDown(KEY_S))
            input.camera_pitch -= 1.0f;

        Vector2 mouse_delta = GetMouseDelta();

        input.mouse_delta_x = mouse_delta.x;
        input.mouse_delta_y = mouse_delta.y;
        input.mouse_wheel = GetMouseWheelMove();
        input.right_mouse_down = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        return input;
    }
}