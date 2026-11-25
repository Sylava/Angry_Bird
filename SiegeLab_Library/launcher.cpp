#include "launcher.h"

#include <algorithm>
#include <cmath>

namespace siege_lab
{
    Launcher::Launcher(Vector3 _origin, float _yaw,
        float _pitch, float _speed)
    {
        m_origin = _origin;
        m_yaw = std::clamp(_yaw, kMinYaw, kMaxYaw);
        m_pitch = std::clamp(_pitch, kMinPitch, kMaxPitch);
        m_speed = std::clamp(_speed, kMinSpeed, kMaxSpeed);
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
    float Launcher::GetYaw() const
    {
        return m_yaw;
    }

    float Launcher::GetPitch() const
    {
        return m_pitch;
    }

    float Launcher::GetSpeed() const
    {
        return m_speed;
    }
    void Launcher::SetProjectileKind(ProjectileKind _kind)
    {
        m_projectile_kind = _kind;
    }

    void Launcher::AdjustAim(float _delta_yaw, float _delta_pitch)
    {
        m_yaw = std::clamp(m_yaw + _delta_yaw, kMinYaw, kMaxYaw);
        m_pitch = std::clamp(m_pitch + _delta_pitch, kMinPitch, kMaxPitch);
    }

    void Launcher::AdjustSpeed(float _delta_speed)
    {
        m_speed = std::clamp(m_speed + _delta_speed, kMinSpeed, kMaxSpeed);
    }

    void Launcher::Update(const InputSnapshot& _input, float _dt)
    {
    }
}