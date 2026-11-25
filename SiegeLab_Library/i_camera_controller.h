#ifndef SIEGE_LAB_I_CAMERA_CONTROLLER_H_
#define SIEGE_LAB_I_CAMERA_CONTROLLER_H_

#include "raylib.h"

namespace siege_lab
{
    class ICameraController
    {
    public:
        virtual ~ICameraController() = default;

        virtual Camera3D GetCamera() const = 0;
    };
}

#endif  // SIEGE_LAB_I_CAMERA_CONTROLLER_H_