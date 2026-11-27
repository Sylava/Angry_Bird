#ifndef SIEGE_LAB_INPUT_SNAPSHOT_H_
#define SIEGE_LAB_INPUT_SNAPSHOT_H_

namespace siege_lab
{
    struct InputSnapshot
    {
        float camera_yaw = 0.0f;
        float camera_pitch = 0.0f;

        float mouse_delta_x = 0.0f;
        float mouse_delta_y = 0.0f;

        float mouse_wheel = 0.0f;

        bool right_mouse_down = false;

        float launcher_yaw = 0.0f;
        float launcher_pitch = 0.0f;
        float launcher_speed = 0.0f;

        bool select_standard = false;
        bool select_heavy = false;

        bool fire_pressed = false;
    };
}

#endif