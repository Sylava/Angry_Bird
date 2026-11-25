#include "standard_projectile.h"

namespace siege_lab
{
    StandardProjectile::StandardProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    void StandardProjectile::Draw()
    {
    }
}