#include "pch.h"

#include "gtest/gtest.h"

#include "physics_world.h"
#include "scene_objects.h"
#include "standard_projectile.h"

namespace siege_lab
{

    ////////////////// FUNCTIONS ////////////////////////

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

    void InitializeGroundBox(
        cyclone::RigidBody& _body,
        cyclone::CollisionBox& _box)
    {
        _body.setMass(1.0f);

        cyclone::Matrix3 inertia;
        inertia.setBlockInertiaTensor(
            cyclone::Vector3(0.5f, 0.5f, 0.5f), 1.0f);

        _body.setInertiaTensor(inertia);
        _body.setPosition(0.0f, 0.45f, 0.0f);
        _body.setOrientation(1.0f, 0.0f, 0.0f, 0.0f);
        _body.setVelocity(0.0f, 0.0f, 0.0f);
        _body.setRotation(0.0f, 0.0f, 0.0f);
        _body.setAcceleration(0.0f, 0.0f, 0.0f);
        _body.setDamping(1.0f, 1.0f);
        _body.setCanSleep(false);
        _body.setAwake(true);
        _body.calculateDerivedData();

        _box.body = &_body;
        _box.halfSize = cyclone::Vector3(0.5f, 0.5f, 0.5f);
        _box.calculateInternals();
    }

    void InitializeCollisionSphere(
        StandardProjectile& _projectile,
        float _position_x)
    {
        cyclone::RigidBody& body = _projectile.GetBody();

        body.setPosition(_position_x, 2.0f, 0.0f);
        body.setVelocity(0.0f, 0.0f, 0.0f);
        body.setAcceleration(0.0f, 0.0f, 0.0f);
        body.setCanSleep(false);
        body.setAwake(true);
        body.calculateDerivedData();

        _projectile.GetSphere().radius = 0.5f;
        _projectile.GetSphere().calculateInternals();
    }

    void InitializeCollisionBox(
        cyclone::RigidBody& _body,
        cyclone::CollisionBox& _box)
    {
        InitializeGroundBox(_body, _box);

        _body.setPosition(0.0f, 2.0f, 0.0f);
        _body.calculateDerivedData();
        _box.calculateInternals();
    }

    void CheckBoxSphereContact(bool _box_first)
    {
        cyclone::RigidBody body;
        cyclone::CollisionBox box;
        StandardProjectile projectile;

        InitializeCollisionBox(body, box);
        InitializeCollisionSphere(projectile, 0.9f);

        PhysicsWorld world;

        if (_box_first)
        {
            world.RegisterBox({ 0, 1 }, body, box);
            world.RegisterSphere(
                { 1, 1 }, projectile.GetBody(), projectile.GetSphere());
        }
        else
        {
            world.RegisterSphere(
                { 1, 1 }, projectile.GetBody(), projectile.GetSphere());
            world.RegisterBox({ 0, 1 }, body, box);
        }

        world.Step(1.0f / 60.0f);

        EXPECT_EQ(world.GetContactCount(), 1u);

        EXPECT_NEAR(projectile.GetBody().getPosition().x -
            body.getPosition().x, 1.0f, 0.01f);
    }



    ////////////////// TESTS ////////////////////////



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

    TEST(PhysicsWorld, RegisterBorrowsBox)
    {
        cyclone::RigidBody body;
        cyclone::CollisionBox box;

        box.body = &body;
        box.halfSize = cyclone::Vector3(0.5f, 0.5f, 0.5f);

        PhysicsWorld world;
        const EntityId id{ 0, 1 };

        EXPECT_EQ(world.GetRegistrationCount(), 0u);

        world.RegisterBox(id, body, box);

        EXPECT_EQ(world.GetRegistrationCount(), 1u);
        EXPECT_EQ(box.body, &body);

        world.UnregisterObject(id);

        EXPECT_EQ(world.GetRegistrationCount(), 0u);
        EXPECT_EQ(box.body, &body);
    }

    TEST(PhysicsWorld, DetectsBoxGroundContact)
    {
        cyclone::RigidBody body;
        cyclone::CollisionBox box;

        InitializeGroundBox(body, box);

        cyclone::CollisionPlane ground;
        ground.direction = cyclone::Vector3(0.0f, 1.0f, 0.0f);
        ground.offset = 0.0f;

        PhysicsWorld world;

        world.RegisterBox({ 0, 1 }, body, box);
        world.RegisterPlane(ground);

        constexpr float kFixedDt = 1.0f / 60.0f;

        world.Step(kFixedDt);

        EXPECT_GE(world.GetContactCount(), 1u);
        EXPECT_GT(body.getPosition().y, 0.45f);
        EXPECT_NEAR(body.getPosition().y, 0.5f, 0.01f);
    }

    TEST(PhysicsWorld, DetectsSphereSphereContact)
    {
        StandardProjectile first;
        StandardProjectile second;

        InitializeCollisionSphere(first, -0.45f);
        InitializeCollisionSphere(second, 0.45f);

        PhysicsWorld world;

        world.RegisterSphere(
            { 0, 1 }, first.GetBody(), first.GetSphere());
        world.RegisterSphere(
            { 1, 1 }, second.GetBody(), second.GetSphere());

        constexpr float kFixedDt = 1.0f / 60.0f;
        world.Step(kFixedDt);

        EXPECT_EQ(world.GetContactCount(), 1u);

        const float distance =
            second.GetBody().getPosition().x -
            first.GetBody().getPosition().x;

        EXPECT_NEAR(distance, 1.0f, 0.01f);
    }

    TEST(PhysicsWorld, DetectsBoxSphereContact)
    {
        CheckBoxSphereContact(true);
    }

    TEST(PhysicsWorld, DetectsSphereBoxContact)
    {
        CheckBoxSphereContact(false);
    }

    TEST(PhysicsWorld, DetectsBoxBoxContact)
    {
        cyclone::RigidBody first_body;
        cyclone::RigidBody second_body;
        cyclone::CollisionBox first_box;
        cyclone::CollisionBox second_box;

        InitializeCollisionBox(first_body, first_box);
        InitializeCollisionBox(second_body, second_box);

        second_body.setPosition(0.9f, 2.0f, 0.0f);
        second_body.calculateDerivedData();
        second_box.calculateInternals();

        PhysicsWorld world;

        world.RegisterBox({ 0, 1 }, first_body, first_box);
        world.RegisterBox({ 1, 1 }, second_body, second_box);

        world.Step(1.0f / 60.0f);

        EXPECT_GE(world.GetContactCount(), 1u);

        const float distance = second_body.getPosition().x -
            first_body.getPosition().x;

        EXPECT_GT(distance, 0.9f);
    }
}  // namespace siege_lab