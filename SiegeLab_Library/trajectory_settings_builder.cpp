#include "trajectory_settings_builder.h"

namespace siege_lab
{
    TrajectorySettings TrajectorySettingsBuilder::Build(
        const ShotSettings& _shot) const
    {
        TrajectorySettings settings;

        settings.origin = _shot.origin;

        settings.velocity =
        {
          _shot.direction.x * _shot.speed,
          _shot.direction.y * _shot.speed,
          _shot.direction.z * _shot.speed
        };

        return settings;
    }
}  // namespace siege_lab