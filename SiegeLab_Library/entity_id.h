#ifndef SIEGE_LAB_ENTITY_ID_H_
#define SIEGE_LAB_ENTITY_ID_H_

#include <cstdint>

namespace siege_lab
{
    struct EntityId
    {
        int slot = -1;
        std::uint64_t generation = 0;
    };
}

#endif  // SIEGE_LAB_ENTITY_ID_H_