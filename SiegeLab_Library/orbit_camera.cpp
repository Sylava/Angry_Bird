#include "orbit_camera.h"

namespace siege_lab
{
    OrbitCamera::OrbitCamera(Vector3 _target, float _yaw,
        float _pitch, float _radius)
    {
        m_target = _target;
        m_yaw = _yaw;
        m_pitch = _pitch;
        m_radius = _radius;
    }

    Camera3D OrbitCamera::GetCamera() const
    {
        return {};
    }
}