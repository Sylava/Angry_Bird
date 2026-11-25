#ifndef SIEGE_LAB_SCENE_OBJECTS_H_
#define SIEGE_LAB_SCENE_OBJECTS_H_

#include <cstddef>
#include <memory>
#include <concepts>
#include <type_traits>

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
            requires std::derived_from<T, GameEntity> &&
        (!std::is_abstract_v<T>)
            EntityId CreateEntity()
        {
            return m_pool.Create(std::make_unique<T>());
        }
        template<typename T, typename... Args>
            requires std::derived_from<T, GameEntity> &&
        (!std::is_abstract_v<T>) &&
            (sizeof...(Args) > 0)
            EntityId CreateEntity(Args... _args)
        {
            return {};
        }
        GameEntity* Get(EntityId _id)
        {
            auto entity = m_pool.Get(_id);

            if (entity == nullptr)
            {
                return nullptr;
            }

            return entity->get();
        }

        std::size_t GetCount() const
        {
            return m_pool.GetCount();
        }
    };
}

#endif  // SIEGE_LAB_SCENE_OBJECTS_H_