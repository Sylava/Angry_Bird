#ifndef SIEGE_LAB_PROJECTILE_FACTORY_H_
#define SIEGE_LAB_PROJECTILE_FACTORY_H_

#include "heavy_projectile.h"
#include "scene_objects.h"
#include "shot_settings.h"
#include "standard_projectile.h"

namespace siege_lab
{
    class ProjectileFactory
    {
    public:
        template<std::size_t Capacity>
        static EntityId Create(
            SceneObjects<Capacity>& _scene,
            const ShotSettings& _settings)
        {
            return {};
        }
    };
}

#endif  // SIEGE_LAB_PROJECTILE_FACTORY_H_