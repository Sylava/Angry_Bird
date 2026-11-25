#include "projectile.h"

namespace siege_lab
{
    Projectile::Projectile()
    {
        m_sphere.body = &GetBody();
    }

    cyclone::CollisionSphere& Projectile::GetSphere()
    {
        return m_sphere;
    }
}