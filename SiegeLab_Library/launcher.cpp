#include "launcher.h"

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
        return {};
    }
}