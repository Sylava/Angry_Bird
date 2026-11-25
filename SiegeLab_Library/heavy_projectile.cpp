#include "heavy_projectile.h"

namespace siege_lab
{
    HeavyProjectile::HeavyProjectile()
    {
        ConfigurePhysics(kMass, kRadius);
    }

    void HeavyProjectile::Draw()
    {
    }
}