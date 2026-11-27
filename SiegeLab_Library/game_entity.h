#ifndef SIEGE_LAB_GAME_ENTITY_H_
#define SIEGE_LAB_GAME_ENTITY_H_
#include "raylib.h"

#include "cyclone/body.h"

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
    private:
        cyclone::RigidBody m_body{};

    public:
        virtual ~GameEntity() = default;

        cyclone::RigidBody& GetBody()
        {
            return m_body;
        }

        virtual void Draw() = 0;
    };
}

#endif  // SIEGE_LAB_GAME_ENTITY_H_