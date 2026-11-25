#ifndef SIEGE_LAB_GAME_ENTITY_H_
#define SIEGE_LAB_GAME_ENTITY_H_

#include "cyclone/body.h"

namespace siege_lab
{
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