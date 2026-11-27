#ifndef SIEGE_LAB_STANDARD_PROJECTILE_H_
#define SIEGE_LAB_STANDARD_PROJECTILE_H_

#include "projectile.h"

namespace siege_lab
{
    class StandardProjectile : public Projectile
    {
    protected:
        Color GetColor() const override;

    private:
        static constexpr float kMass = 1.0f;
        static constexpr float kRadius = 0.28f;

    public:
        StandardProjectile();
        explicit StandardProjectile(const ShotSettings& _settings);
        
    };
}

#endif  // SIEGE_LAB_STANDARD_PROJECTILE_H_