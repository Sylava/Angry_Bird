#ifndef SIEGE_LAB_STANDARD_PROJECTILE_H_
#define SIEGE_LAB_STANDARD_PROJECTILE_H_

#include "projectile.h"

namespace siege_lab
{
    class StandardProjectile : public Projectile
    {
    public:
        StandardProjectile();
        void Draw() override;
    };
}

#endif  // SIEGE_LAB_STANDARD_PROJECTILE_H_