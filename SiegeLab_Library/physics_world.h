#pragma once
#ifndef SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_
#define SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_

#include <cstddef>
#include <vector>
#include <array>

#include "cyclone/body.h"
#include "cyclone/collide_fine.h"
#include "entity_id.h"
#include "physics_registration.h"
#include "cyclone/contacts.h"

namespace siege_lab
{
    class PhysicsWorld
    {
    private:
        static constexpr unsigned kMaxContacts = 256;
        static constexpr unsigned kSolverIterations = 100;

        std::vector<PhysicsRegistration> m_registrations;
        std::vector<cyclone::CollisionPlane> m_planes;
        std::array<cyclone::Contact, kMaxContacts> m_contacts{};
        cyclone::CollisionData m_collision_data{};
        cyclone::ContactResolver m_resolver{ kSolverIterations };

        void DetectContacts();
        void DetectBoxContacts(const PhysicsRegistration& _registration);
        void DetectSphereContacts(const PhysicsRegistration& _registration);
        void ResolveContacts(float _dt);
        void RefreshColliders();
        void ResetContactData();
        void DetectPlaneContacts();
        void DetectObjectContacts();

        void DetectObjectPair(
            const PhysicsRegistration& _first,
            const PhysicsRegistration& _second);
        void DetectSphereSphere(
            const PhysicsRegistration& _first,
            const PhysicsRegistration& _second);
        void DetectBoxSphere(
            const PhysicsRegistration& _box,
            const PhysicsRegistration& _sphere);

        void RegisterObject(
            EntityId _id,
            cyclone::RigidBody& _body,
            cyclone::CollisionPrimitive& _collider,
            ShapeKind _kind);


    public:
        void RegisterSphere(
            EntityId _id,
            cyclone::RigidBody& _body,
            cyclone::CollisionSphere& _sphere);
        void RegisterBox(
            EntityId _id,
            cyclone::RigidBody& _body,
            cyclone::CollisionBox& _box);

        void UnregisterObject(EntityId _id);
        std::size_t GetRegistrationCount() const;
        void Step(float _dt);
        void RegisterPlane(const cyclone::CollisionPlane& _plane);

        unsigned GetContactCount() const;
    };
}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_PHYSICS_WORLD_H_