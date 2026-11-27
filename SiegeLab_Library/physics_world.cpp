#include "physics_world.h"

#include <vector>

namespace siege_lab
{
    void PhysicsWorld::UnregisterObject(EntityId _id)
    {
        std::erase_if(
            m_registrations,
            [_id](const PhysicsRegistration& _registration)
            {
                return _registration.id.slot == _id.slot &&
                    _registration.id.generation == _id.generation;
            });
    }

    std::size_t PhysicsWorld::GetRegistrationCount() const
    {
        return m_registrations.size();
    }

    void PhysicsWorld::Step(float _dt)
    {
        for (const PhysicsRegistration& registration : m_registrations)
        {
            if (registration.body->getInverseMass() > 0.0f)
            {
                registration.body->integrate(_dt);
            }
        }

        RefreshColliders();
        DetectContacts();
        ResolveContacts(_dt);
        RefreshColliders();
    }

    void PhysicsWorld::RegisterPlane(
        const cyclone::CollisionPlane& _plane)
    {
        m_planes.push_back(_plane);
    }

    unsigned PhysicsWorld::GetContactCount() const
    {
        return m_collision_data.contactCount;
    }

    void PhysicsWorld::DetectSphereContacts(
        const PhysicsRegistration& _registration)
    {
        const cyclone::CollisionSphere& sphere =
            static_cast<const cyclone::CollisionSphere&>(
                *_registration.collider);

        for (const cyclone::CollisionPlane& plane : m_planes)
        {
            if (m_collision_data.contactsLeft <= 0)
            {
                return;
            }

            cyclone::CollisionDetector::sphereAndHalfSpace(
                sphere, plane, &m_collision_data);
        }
    }

    void PhysicsWorld::DetectBoxContacts(
        const PhysicsRegistration& _registration)
    {
        const cyclone::CollisionBox& box =
            static_cast<const cyclone::CollisionBox&>(
                *_registration.collider);

        for (const cyclone::CollisionPlane& plane : m_planes)
        {
            if (m_collision_data.contactsLeft < 8)
            {
                return;
            }

            cyclone::CollisionDetector::boxAndHalfSpace(
                box, plane, &m_collision_data);
        }
    }

    void PhysicsWorld::DetectObjectContacts()
    {
        for (std::size_t i = 0; i < m_registrations.size(); ++i)
        {
            for (std::size_t j = i + 1; j < m_registrations.size(); ++j)
            {
                if (m_collision_data.contactsLeft <= 0)
                {
                    return;
                }

                DetectObjectPair(m_registrations[i], m_registrations[j]);
            }
        }
    }

    void PhysicsWorld::DetectObjectPair(
        const PhysicsRegistration& _first,
        const PhysicsRegistration& _second)
    {
        if (_first.body == _second.body)
        {
            return;
        }

        if (_first.body->getInverseMass() <= 0.0f &&
            _second.body->getInverseMass() <= 0.0f)
        {
            return;
        }

        if (_first.kind == ShapeKind::kSphere &&
            _second.kind == ShapeKind::kSphere)
        {
            DetectSphereSphere(_first, _second);
        }
    }

    void PhysicsWorld::DetectSphereSphere(
        const PhysicsRegistration& _first,
        const PhysicsRegistration& _second)
    {
        const cyclone::CollisionSphere& first =
            static_cast<const cyclone::CollisionSphere&>(
                *_first.collider);

        const cyclone::CollisionSphere& second =
            static_cast<const cyclone::CollisionSphere&>(
                *_second.collider);

        cyclone::CollisionDetector::sphereAndSphere(
            first, second, &m_collision_data);
    }

    void PhysicsWorld::DetectContacts()
    {
        ResetContactData();
        DetectPlaneContacts();
        DetectObjectContacts();
    }

    void PhysicsWorld::ResolveContacts(float _dt)
    {
        if (m_collision_data.contactCount == 0)
        {
            return;
        }

        m_resolver.setIterations(kSolverIterations, kSolverIterations);

        m_resolver.resolveContacts(
            m_contacts.data(),
            m_collision_data.contactCount,
            _dt);
    }

    void PhysicsWorld::RefreshColliders()
    {
        for (const PhysicsRegistration& registration : m_registrations)
        {
            registration.body->calculateDerivedData();
            registration.collider->calculateInternals();
        }
    }

    void PhysicsWorld::RegisterSphere(
        EntityId _id,
        cyclone::RigidBody& _body,
        cyclone::CollisionSphere& _sphere)
    {
        RegisterObject(_id, _body, _sphere, ShapeKind::kSphere);
    }

    void PhysicsWorld::RegisterBox(
        EntityId _id,
        cyclone::RigidBody& _body,
        cyclone::CollisionBox& _box)
    {
        RegisterObject(_id, _body, _box, ShapeKind::kBox);
    }

    void PhysicsWorld::RegisterObject(
        EntityId _id,
        cyclone::RigidBody& _body,
        cyclone::CollisionPrimitive& _collider,
        ShapeKind _kind)
    {
        m_registrations.push_back(
            { _id, &_body, &_collider, _kind });
    }

    void PhysicsWorld::ResetContactData()
    {
        m_collision_data.contactArray = m_contacts.data();
        m_collision_data.reset(kMaxContacts);

        m_collision_data.friction = 0.5f;
        m_collision_data.restitution = 0.0f;
        m_collision_data.tolerance = 0.0f;
    }

    void PhysicsWorld::DetectPlaneContacts()
    {
        for (const PhysicsRegistration& registration : m_registrations)
        {
            if (registration.body->getInverseMass() <= 0.0f)
            {
                continue;
            }

            if (registration.kind == ShapeKind::kSphere)
            {
                DetectSphereContacts(registration);
            }
            else if (registration.kind == ShapeKind::kBox)
            {
                DetectBoxContacts(registration);
            }
        }
    }
}  // namespace siege_lab