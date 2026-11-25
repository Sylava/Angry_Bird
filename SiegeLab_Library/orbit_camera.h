#ifndef SIEGE_LAB_ORBIT_CAMERA_H_
#define SIEGE_LAB_ORBIT_CAMERA_H_

#include "raylib.h"

#include "i_camera_controller.h"

namespace siege_lab
{
    class OrbitCamera : public ICameraController
    {
    private:
        Vector3 m_target;
        float m_yaw;
        float m_pitch;
        float m_radius;

    public:
        OrbitCamera(Vector3 _target, float _yaw,
            float _pitch, float _radius);

        Camera3D GetCamera() const override;
    };
}

#endif  // SIEGE_LAB_ORBIT_CAMERA_H_