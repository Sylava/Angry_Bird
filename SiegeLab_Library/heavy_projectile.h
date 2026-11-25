#ifndef SIEGE_LAB_HEAVY_PROJECTILE_H_
#define SIEGE_LAB_HEAVY_PROJECTILE_H_

#include "projectile.h"

namespace siege_lab
{
    class HeavyProjectile : public Projectile
    {
    private:
        static constexpr float kMass = 2.0f;
        static constexpr float kRadius = 0.36f;

    public:
        HeavyProjectile();
        void Draw() override;
    };
}

#endif  // SIEGE_LAB_HEAVY_PROJECTILE_H_