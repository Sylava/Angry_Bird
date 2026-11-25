#include "launcher.h"

#include <cmath>

namespace siege_lab
{
    Launcher::Launcher(Vector3 _origin, float _yaw,
        float _pitch, float _speed)
    {
        m_origin = _origin;
        m_yaw = _yaw;
        m_pitch = _pitch;
        m_speed = _speed;
        m_projectile_kind = ProjectileKind::kStandard;
    }

    ShotSettings Launcher::GetShotSettings() const
    {
        float yaw = m_yaw * DEG2RAD;
        float pitch = m_pitch * DEG2RAD;

        ShotSettings settings{};

        settings.origin = m_origin;

        settings.direction.x = std::cos(pitch) * std::cos(yaw);
        settings.direction.y = std::sin(pitch);
        settings.direction.z = std::cos(pitch) * std::sin(yaw);

        settings.speed = m_speed;
        settings.projectile_kind = m_projectile_kind;

        return settings;
    }
}