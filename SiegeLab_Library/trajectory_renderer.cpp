#include "trajectory_renderer.h"

#include "raylib.h"

namespace siege_lab
{
    namespace
    {
        constexpr float kPointRadius = 0.04f;
        constexpr float kContactRadius = 0.12f;
    }  // namespace

    void TrajectoryRenderer::Draw(
        const TrajectoryResult& _result) const
    {
        for (const Vector3& position : _result.positions)
        {
            DrawSphere(position, kPointRadius, GREEN);
        }

        if (_result.has_contact)
        {
            DrawSphere(_result.contact_point, kContactRadius, RED);
        }
    }
}  // namespace siege_lab