#include "standard_projectile.h"

namespace siege_lab
{
    StandardProjectile::StandardProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    StandardProjectile::StandardProjectile(
        const ShotSettings& _settings)
        : StandardProjectile()
    {
        Fire(_settings);
    }

    Color StandardProjectile::GetColor() const
    {
        return RED;
    }
}