#include "trajectory_settings_builder.h"

#include "heavy_projectile.h"
#include "projectile.h"
#include "standard_projectile.h"

namespace siege_lab
{
    namespace
    {
        void CopyProjectileProfile(
            Projectile& _projectile,
            TrajectorySettings& _settings)
        {
            _settings.mass =
                static_cast<float>(_projectile.GetBody().getMass());

            _settings.radius =
                static_cast<float>(_projectile.GetSphere().radius);
        }
    }  // namespace

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

        if (_shot.projectile_kind == ProjectileKind::kHeavy)
        {
            HeavyProjectile projectile;
            CopyProjectileProfile(projectile, settings);
        }
        else
        {
            StandardProjectile projectile;
            CopyProjectileProfile(projectile, settings);
        }

        return settings;
    }
}  // namespace siege_lab