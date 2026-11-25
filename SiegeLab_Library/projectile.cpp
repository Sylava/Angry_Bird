#include "projectile.h"

namespace siege_lab
{
    Projectile::Projectile()
    {
    }

    cyclone::CollisionSphere& Projectile::GetSphere()
    {
        return m_sphere;
    }
}