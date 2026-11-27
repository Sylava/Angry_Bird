#pragma once
#ifndef SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_
#define SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_

#include <cstddef>
#include <vector>

#include "cyclone/body.h"
#include "cyclone/collide_fine.h"

#include "entity_id.h"
#include "physics_registration.h"

namespace siege_lab
{
    class PhysicsWorld
    {
    private:
        std::vector<PhysicsRegistration> m_registrations;

    public:
        void RegisterSphere(
            EntityId _id,
            cyclone::RigidBody& _body,
            cyclone::CollisionSphere& _sphere);

        void UnregisterObject(EntityId _id);

        std::size_t GetRegistrationCount() const;
    };
}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_