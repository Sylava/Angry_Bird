#include "projectile.h"

namespace siege_lab
{
    Projectile::Projectile()
    {
        m_sphere.body = &GetBody();
    }

    cyclone::CollisionSphere& Projectile::GetSphere()
    {
        return m_sphere;
    }

    void Projectile::ConfigurePhysics(float _mass, float _radius)
    {
        cyclone::RigidBody& body = GetBody();

        body.setMass(_mass);

        float inertia = 0.4f * _mass * _radius * _radius;
        cyclone::Matrix3 tensor;
        tensor.setDiagonal(inertia, inertia, inertia);
        body.setInertiaTensor(tensor);

        body.setDamping(1.0f, 0.85f);
        body.setPosition(0.0f, 0.0f, 0.0f);
        body.setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
        body.setVelocity(0.0f, 0.0f, 0.0f);
        body.setRotation(0.0f, 0.0f, 0.0f);
        body.setAcceleration(0.0f, -9.81f, 0.0f);
        body.clearAccumulators();
        body.setCanSleep(false);
        body.setAwake(true);
        body.calculateDerivedData();

        m_sphere.radius = _radius;
        m_sphere.calculateInternals();
    }

    void Projectile::Draw()
    {
        cyclone::Vector3 position = GetBody().getPosition();

        ::Vector3 center = { position.x, position.y, position.z };

        DrawSphere(center, m_sphere.radius, GetColor());
    }

    void Projectile::Fire(const ShotSettings& _settings)
    {
        cyclone::RigidBody& body = GetBody();

        body.setPosition(
            _settings.origin.x,
            _settings.origin.y,
            _settings.origin.z);

        body.setVelocity(
            _settings.direction.x * _settings.speed,
            _settings.direction.y * _settings.speed,
            _settings.direction.z * _settings.speed);

        body.setAwake(true);
        body.calculateDerivedData();
        m_sphere.calculateInternals();
    }
}