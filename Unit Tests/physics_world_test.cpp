#include "pch.h"

#include "gtest/gtest.h"

#include "physics_world.h"
#include "scene_objects.h"
#include "standard_projectile.h"

namespace siege_lab
{
    void InitializeFallingProjectile(StandardProjectile& _projectile)
    {
        cyclone::RigidBody& body = _projectile.GetBody();

        body.setPosition(0.0f, 20.0f, 0.0f);
        body.setVelocity(0.0f, 0.0f, 0.0f);
        body.setAcceleration(0.0f, -9.81f, 0.0f);
        body.setDamping(1.0f, 1.0f);
        body.setCanSleep(false);
        body.setAwake(true);
        body.calculateDerivedData();

        _projectile.GetSphere().calculateInternals();
    }

    void ExpectSameVector(
        const cyclone::Vector3& _actual,
        const cyclone::Vector3& _expected)
    {
        constexpr float kTolerance = 0.0001f;

        EXPECT_NEAR(_actual.x, _expected.x, kTolerance);
        EXPECT_NEAR(_actual.y, _expected.y, kTolerance);
        EXPECT_NEAR(_actual.z, _expected.z, kTolerance);
    }

    void InitializeGroundContact(StandardProjectile& _projectile)
    {
        cyclone::RigidBody& body = _projectile.GetBody();

        body.setPosition(0.0f, 0.45f, 0.0f);
        body.setVelocity(0.0f, 0.0f, 0.0f);
        body.setAcceleration(0.0f, 0.0f, 0.0f);
        body.setCanSleep(false);
        body.setAwake(true);
        body.calculateDerivedData();

        _projectile.GetSphere().radius = 0.5f;
        _projectile.GetSphere().calculateInternals();
    }

    TEST(PhysicsWorld, RegisterBorrowsObject)
    {
        SceneObjects<1> scene;
        PhysicsWorld world;

        const EntityId id =
            scene.CreateEntity<StandardProjectile>();

        GameEntity* entity = scene.Get(id);
        ASSERT_NE(entity, nullptr);

        StandardProjectile* projectile =
            static_cast<StandardProjectile*>(entity);

        cyclone::RigidBody* body = &projectile->GetBody();

        EXPECT_EQ(world.GetRegistrationCount(), 0u);

        world.RegisterSphere(id, *body, projectile->GetSphere());

        EXPECT_EQ(world.GetRegistrationCount(), 1u);

        world.UnregisterObject(id);

        EXPECT_EQ(world.GetRegistrationCount(), 0u);
        ASSERT_EQ(scene.Get(id), entity);
        EXPECT_EQ(&scene.Get(id)->GetBody(), body);
        EXPECT_EQ(scene.GetCount(), 1u);
    }

    TEST(PhysicsWorld, StepUsesCyclone)
    {
        PhysicsWorld world;
        StandardProjectile simulated;
        StandardProjectile reference;

        InitializeFallingProjectile(simulated);
        InitializeFallingProjectile(reference);

        world.RegisterSphere(
            { 0, 1 }, simulated.GetBody(), simulated.GetSphere());

        constexpr float kFixedDt = 1.0f / 60.0f;

        for (int i = 0; i < 60; ++i)
        {
            world.Step(kFixedDt);
            reference.GetBody().integrate(kFixedDt);
            reference.GetSphere().calculateInternals();
        }

        ExpectSameVector(simulated.GetBody().getPosition(),
            reference.GetBody().getPosition());
        ExpectSameVector(simulated.GetBody().getVelocity(),
            reference.GetBody().getVelocity());
        EXPECT_NEAR(simulated.GetBody().getVelocity().y,
            -9.81f, 0.0001f);
    }

    TEST(PhysicsWorld, RegisteredColliderIsUsed)
    {
        PhysicsWorld world;
        StandardProjectile projectile;

        InitializeGroundContact(projectile);

        cyclone::CollisionPlane ground;
        ground.direction = cyclone::Vector3(0.0f, 1.0f, 0.0f);
        ground.offset = 0.0f;

        const EntityId id{ 0, 1 };
        constexpr float kFixedDt = 1.0f / 60.0f;

        world.RegisterSphere(
            id, projectile.GetBody(), projectile.GetSphere());
        world.RegisterPlane(ground);

        world.Step(kFixedDt);

        EXPECT_GE(world.GetContactCount(), 1u);

        world.UnregisterObject(id);
        world.Step(kFixedDt);

        EXPECT_EQ(world.GetContactCount(), 0u);
    }
}  // namespace siege_lab