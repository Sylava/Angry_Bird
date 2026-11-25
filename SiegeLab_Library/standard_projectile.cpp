#include "standard_projectile.h"

namespace siege_lab
{
    StandardProjectile::StandardProjectile()
    {
        ConfigurePhysics(1.0f, 0.28f);
    }

    void StandardProjectile::Draw()
    {
    }
}