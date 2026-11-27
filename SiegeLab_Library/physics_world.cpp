#include "physics_world.h"

#include <vector>

namespace siege_lab
{
    void PhysicsWorld::RegisterSphere(
        EntityId _id,
        cyclone::RigidBody& _body,
        cyclone::CollisionSphere& _sphere)
    {
        m_registrations.push_back(
            { _id, &_body, &_sphere, ShapeKind::kSphere });
    }

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
        for (PhysicsRegistration& registration : m_registrations)
        {
            if (registration.body->getInverseMass() > 0.0f)
            {
                registration.body->integrate(_dt);
            }

            registration.collider->calculateInternals();
        }
    }
}  // namespace siege_lab