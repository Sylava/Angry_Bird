#ifndef SIEGE_LAB_GAME_ENTITY_H_
#define SIEGE_LAB_GAME_ENTITY_H_
#include "raylib.h"

namespace siege_lab
{
    struct CollisionContact
    {
        Vector3 point;
        Vector3 normal;
        float penetration;
    };

    class GameEntity
    {
    public:
        virtual ~GameEntity() = default;

        virtual void Draw() = 0;
    };
}

#endif  // SIEGE_LAB_GAME_ENTITY_H_