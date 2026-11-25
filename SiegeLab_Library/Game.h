#ifndef SIEGE_LAB_GAME_H_
#define SIEGE_LAB_GAME_H_

#include "camera_manager.h"
#include "input_controller.h"
#include "launcher.h"
#include "orbit_camera.h"

namespace siege_lab
{
    class Game
    {
    public:
        Game();
        void Run();

    private:
        OrbitCamera m_camera;
        CameraManager m_camera_manager;
        InputController m_input_controller;
        Launcher m_launcher;

        void Update();
        void Draw();
        void DrawLauncher() const;
        void DrawHud() const;
    };
}

#endif