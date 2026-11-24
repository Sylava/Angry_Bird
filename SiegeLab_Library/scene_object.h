#ifndef SIEGE_LAB_SCENE_OBJECTS_H_
#define SIEGE_LAB_SCENE_OBJECTS_H_

#include <cstddef>
#include <memory>

#include "game_entity.h"
#include "object_pool.h"

namespace siege_lab
{
    template<std::size_t Capacity>
    class SceneObjects
    {
    private:
        ObjectPool<std::unique_ptr<GameEntity>, Capacity> m_pool;

    public:
        template<typename T>
        EntityId CreateEntity()
        {
            return {};
        }

        GameEntity* Get(EntityId _id)
        {
            return nullptr;
        }

        std::size_t GetCount() const
        {
            return 0;
        }
    };
}

#endif  // SIEGE_LAB_SCENE_OBJECTS_H_