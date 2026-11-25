#ifndef SIEGE_LAB_LAUNCHER_H_
#define SIEGE_LAB_LAUNCHER_H_

#include "raylib.h"

#include "shot_settings.h"

namespace siege_lab
{
    class Launcher
    {
    private:
        Vector3 m_origin;
        float m_yaw;
        float m_pitch;
        float m_speed;
        ProjectileKind m_projectile_kind;

    public:
        Launcher(Vector3 _origin, float _yaw,
            float _pitch, float _speed);

        ShotSettings GetShotSettings() const;

        float GetYaw() const;
        float GetPitch() const;
        float GetSpeed() const;
    };
}

#endif