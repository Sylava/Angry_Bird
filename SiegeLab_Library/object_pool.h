#ifndef SIEGE_LAB_OBJECT_POOL_H_
#define SIEGE_LAB_OBJECT_POOL_H_

#include <cstddef>
#include <array>
#include <optional>
#include <utility>
#include "entity_id.h"

namespace siege_lab
{
    template<typename T, std::size_t Capacity>
    class ObjectPool
    {
    private:
        std::array<std::optional<T>, Capacity> m_objects;
        std::size_t m_count = 0;

    public:
        template<typename... Args>
        EntityId Create(T _object)
        {
            for (std::size_t i = 0; i < Capacity; ++i)
            {
                if (!m_objects[i].has_value())
                {
                    m_objects[i] = std::move(_object);
                    ++m_count;

                    return { static_cast<int>(i), 0 };
                }
            }
            return {};
        }

        T* Get(EntityId _id)
        {
            if (_id.slot < 0)
            {
                return nullptr;
            }

            auto index = static_cast<std::size_t>(_id.slot);

            if (index >= Capacity || !m_objects[index].has_value())
            {
                return nullptr;
            }

            return &m_objects[index].value();
        }

        bool Destroy(EntityId _id)
        {
            return false;
        }

        template<typename Func>
        void ForEach(Func&& _func)
        {
        }

        void Clear()
        {
        }

        std::size_t GetCount() const
        {
            return m_count;
        }
    };
}

#endif  // SIEGE_LAB_OBJECT_POOL_H_