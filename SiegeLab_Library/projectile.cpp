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

    void Projectile::ConfigurePhysics(float _mass, float _radius)
    {
    }
}