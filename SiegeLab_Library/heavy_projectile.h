#ifndef SIEGE_LAB_HEAVY_PROJECTILE_H_
#define SIEGE_LAB_HEAVY_PROJECTILE_H_

#include "projectile.h"

namespace siege_lab
{
    class HeavyProjectile : public Projectile
    {
    public:
        HeavyProjectile();
        void Draw() override;
    };
}

#endif  // SIEGE_LAB_HEAVY_PROJECTILE_H_