#include "standard_projectile.h"

namespace siege_lab
{
    StandardProjectile::StandardProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    Color StandardProjectile::GetColor() const
    {
        return RED;
    }
}