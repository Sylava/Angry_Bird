#ifndef SIEGE_LAB_LAUNCHER_H_
#define SIEGE_LAB_LAUNCHER_H_

#include "raylib.h"

#include "input_snapshot.h"
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
        static constexpr float kMinYaw = -30.0f;
        static constexpr float kMaxYaw = 30.0f;

        static constexpr float kMinPitch = 5.0f;
        static constexpr float kMaxPitch = 55.0f;

        static constexpr float kMinSpeed = 8.0f;
        static constexpr float kMaxSpeed = 22.0f;

        static constexpr float kAimSpeed = 30.0f;
        static constexpr float kSpeedChangeRate = 5.0f;


    public:
        Launcher(Vector3 _origin, float _yaw,
            float _pitch, float _speed);

        ShotSettings GetShotSettings() const;

        float GetYaw() const;
        float GetPitch() const;
        float GetSpeed() const;
        void SetProjectileKind(ProjectileKind _kind);
        void AdjustAim(float _delta_yaw, float _delta_pitch);
        void AdjustSpeed(float _delta_speed);

        void Update(const InputSnapshot& _input, float _dt);
    };
}

#endif