#include "camera_manager.h"

namespace siege_lab
{
    void CameraManager::SetController(ICameraController* _controller)
    {
        m_controller = _controller;
    }

    void CameraManager::Update(const InputSnapshot& _input, float _dt)
    {
        if (m_controller != nullptr)
        {
            m_controller->Update(_input, _dt);
        }
    }

    Camera3D CameraManager::GetCamera() const
    {
        if (m_controller != nullptr)
        {
            return m_controller->GetCamera();
        }

        return {};
    }
}