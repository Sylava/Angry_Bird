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
        }
    };
}

#endif  // SIEGE_LAB_SHOT_CONTROLLER_H_