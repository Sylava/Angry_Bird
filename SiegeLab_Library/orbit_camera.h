#ifndef SIEGE_LAB_ORBIT_CAMERA_H_
#define SIEGE_LAB_ORBIT_CAMERA_H_

#include "raylib.h"

#include "i_camera_controller.h"
#include "input_snapshot.h"


namespace siege_lab
{
    class OrbitCamera : public ICameraController
    {
    private:
        Vector3 m_target;
        float m_yaw;
        float m_pitch;
        float m_radius;
        static constexpr float kMinPitch = 10.0f;
        static constexpr float kMaxPitch = 80.0f;
        static constexpr float kMinRadius = 4.0f;
        static constexpr float kMaxRadius = 25.0f;
        static constexpr float kRotationSpeed = 90.0f;
        static constexpr float kMouseSensitivity = 0.25f;
        static constexpr float kZoomSpeed = 1.0f;

    public:
        OrbitCamera(Vector3 _target, float _yaw,
            float _pitch, float _radius);

        Camera3D GetCamera() const override;

        float GetPitch() const;
        float GetRadius() const;
        float GetYaw() const;

        void RotateKeyboard(float _yaw_input,
            float _pitch_input, float _dt);

        void RotateMouse(float _delta_x, float _delta_y);
        void Zoom(float _wheel_delta);

        void Update(const InputSnapshot& _input, float _dt) override;
    };
}

#endif  // SIEGE_LAB_ORBIT_CAMERA_H_