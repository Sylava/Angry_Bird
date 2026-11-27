#ifndef SIEGE_LAB_GAME_H_
#define SIEGE_LAB_GAME_H_

#include <cstddef>

#include "camera_manager.h"
#include "input_controller.h"
#include "launcher.h"
#include "orbit_camera.h"
#include "scene_objects.h"
#include "shot_controller.h"

namespace siege_lab
{
    class Game
    {
    public:
        Game();
        void Run();

    private:
        static constexpr int kInitialAmmo = 5;
        static constexpr std::size_t kSceneCapacity = 32;

        OrbitCamera m_camera;
        CameraManager m_camera_manager;
        InputController m_input_controller;
        Launcher m_launcher;

        SceneObjects<kSceneCapacity> m_scene_objects;
        ShotController m_shot_controller{ kInitialAmmo };

        void Update();
        void Draw();
        void DrawEntities();
        void DrawLauncher() const;
        void DrawHud() const;
    };
}

#endif  // SIEGE_LAB_GAME_H_