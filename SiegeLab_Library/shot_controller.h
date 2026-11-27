#ifndef SIEGE_LAB_SHOT_CONTROLLER_H_
#define SIEGE_LAB_SHOT_CONTROLLER_H_

#include "input_snapshot.h"
#include "projectile_factory.h"
#include "shot_settings.h"

namespace siege_lab
{
    class ShotController
    {
    private:
        int m_ammo;

    public:
        explicit ShotController(int _ammo)
            : m_ammo(_ammo)
        {
        }

        int GetAmmo() const
        {
            return m_ammo;
        }

        template<std::size_t Capacity>
        void Update(
            const InputSnapshot& _input,
            const ShotSettings& _settings,
            SceneObjects<Capacity>& _scene)
        {
            if (!_input.fire_pressed || m_ammo <= 0)
            {
                return;
            }

            EntityId id = ProjectileFactory::Create(_scene, _settings);

            if (id.slot >= 0)
            {
                --m_ammo;
            }
        }
    };
}

#endif  // SIEGE_LAB_SHOT_CONTROLLER_H_