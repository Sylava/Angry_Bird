#ifndef SIEGE_LAB_PROJECTILE_H_
#define SIEGE_LAB_PROJECTILE_H_

#include "cyclone/collide_fine.h"

#include "game_entity.h"

namespace siege_lab
{
    class Projectile : public GameEntity
    {
    private:
        cyclone::CollisionSphere m_sphere{};

    public:
        Projectile();

        cyclone::CollisionSphere& GetSphere();
    };
}

#endif  // SIEGE_LAB_PROJECTILE_H_