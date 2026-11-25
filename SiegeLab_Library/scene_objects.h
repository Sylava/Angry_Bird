#ifndef SIEGE_LAB_SCENE_OBJECTS_H_
#define SIEGE_LAB_SCENE_OBJECTS_H_

#include <cstddef>
#include <memory>
#include <concepts>
#include <type_traits>
#include <utility>
#include <array>

#include "game_entity.h"
#include "object_pool.h"

namespace siege_lab
{
    template<std::size_t Capacity>
    class SceneObjects
    {
    private:
        ObjectPool<std::unique_ptr<GameEntity>, Capacity> m_pool;
        std::array<EntityId, Capacity> m_pending_removals{};
        std::size_t m_removal_count = 0;

        bool IsRemovalPending(EntityId _id) const
        {
            for (std::size_t i = 0; i < m_removal_count; ++i)
            {
                if (m_pending_removals[i].slot == _id.slot &&
                    m_pending_removals[i].generation == _id.generation)
                {
                    return true;
                }
            }

            return false;
        }

    public:
        template<typename T, typename... Args>
            requires std::derived_from<T, GameEntity>&&
        std::constructible_from<T, Args...>
            EntityId CreateEntity(Args&&... _args)
        {
            return m_pool.Create(
                std::make_unique<T>(std::forward<Args>(_args)...));
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

        bool RequestRemoval(EntityId _id)
        {
            if (Get(_id) == nullptr)
            {
                return false;
            }

            if (IsRemovalPending(_id))
            {
                return false;
            }

            if (m_removal_count >= Capacity)
            {
                return false;
            }

            m_pending_removals[m_removal_count] = _id;
            ++m_removal_count;

            return true;
        }

        std::size_t GetCount() const
        {
            return m_pool.GetCount();
        }
    };
}

#endif  // SIEGE_LAB_SCENE_OBJECTS_H_