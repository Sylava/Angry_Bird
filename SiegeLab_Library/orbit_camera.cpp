#include "orbit_camera.h"

#include <cmath>

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
        float yaw = m_yaw * DEG2RAD;
        float pitch = m_pitch * DEG2RAD;

        Camera3D camera{};

        camera.position.x = m_target.x +
            m_radius * std::cos(pitch) * std::sin(yaw);

        camera.position.y = m_target.y +
            m_radius * std::sin(pitch);

        camera.position.z = m_target.z +
            m_radius * std::cos(pitch) * std::cos(yaw);

        camera.target = m_target;
        camera.up = { 0, 1, 0 };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        return camera;
    }

    float OrbitCamera::GetPitch() const
    {
        return m_pitch;
    }

    float OrbitCamera::GetRadius() const
    {
        return m_radius;
    }

}