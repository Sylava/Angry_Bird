#ifndef SIEGE_LAB_SHOT_SETTINGS_H_
#define SIEGE_LAB_SHOT_SETTINGS_H_

#include "raylib.h"

namespace siege_lab
{
    enum class ProjectileKind
    {
        kStandard,
        kHeavy
    };

    struct ShotSettings
    {
        Vector3 origin;
        Vector3 direction;
        float speed;
        ProjectileKind projectile_kind;
    };
}

#endif