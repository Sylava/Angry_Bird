#ifndef SIEGE_LAB_CAMERA_MANAGER_H_
#define SIEGE_LAB_CAMERA_MANAGER_H_

#include "raylib.h"

#include "i_camera_controller.h"
#include "input_snapshot.h"

namespace siege_lab
{
    class CameraManager
    {
    private:
        ICameraController* m_controller = nullptr;

    public:
        void SetController(ICameraController* _controller);
        void Update(const InputSnapshot& _input, float _dt);
        Camera3D GetCamera() const;
    };
}

#endif