#ifndef SIEGE_LAB_GAME_ENTITY_H_
#define SIEGE_LAB_GAME_ENTITY_H_

namespace siege_lab
{
    class GameEntity
    {
    public:
        virtual ~GameEntity() = default;

        virtual void Draw() = 0;
    };
}

#endif  // SIEGE_LAB_GAME_ENTITY_H_