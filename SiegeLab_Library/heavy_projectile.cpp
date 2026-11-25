#include "heavy_projectile.h"

namespace siege_lab
{
    HeavyProjectile::HeavyProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    Color HeavyProjectile::GetColor() const
    {
        return DARKGRAY;
    }
}