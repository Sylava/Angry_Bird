#ifndef SIEGE_LAB_OBJECT_POOL_H_
#define SIEGE_LAB_OBJECT_POOL_H_

#include <cstddef>

#include "entity_id.h"

namespace siege_lab
{
    template<typename T, std::size_t Capacity>
    class ObjectPool
    {
    public:
        template<typename... Args>
        EntityId Create(Args&&... _args)
        {
            return {};
        }

        T* Get(EntityId _id)
        {
            return nullptr;
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
            return 0;
        }
    };
}

#endif  // SIEGE_LAB_OBJECT_POOL_H_