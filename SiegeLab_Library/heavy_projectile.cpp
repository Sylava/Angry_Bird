#include "heavy_projectile.h"

namespace siege_lab
{
    HeavyProjectile::HeavyProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    HeavyProjectile::HeavyProjectile(
        const ShotSettings& _settings)
        : HeavyProjectile()
    {
        Fire(_settings);
    }



    Color HeavyProjectile::GetColor() const
    {
        return DARKGRAY;
    }
}