#include "pch.h"

#include "heavy_projectile.h"
#include "standard_projectile.h"
#include "projectile.h"
#include "launcher.h"
#include "cyclone/collide_fine.h"
#include "cyclone/contacts.h"
#include "physics_world.h"

namespace
{
    class TestProjectile : public siege_lab::Projectile
    {
    protected:
        Color GetColor() const override
        {
            return WHITE;
        }

    public:
    

        void Configure(float _mass, float _radius)
        {
            ConfigurePhysics(_mass, _radius);
        }
    };
}

TEST(Projectile, ColliderIsLinkedToOwnBody)
{
    TestProjectile projectile;

    EXPECT_EQ(
        projectile.GetSphere().body,
        &projectile.GetBody());
}

TEST(Projectile, ConfiguresColliderRadius)
{
    TestProjectile projectile;

    projectile.Configure(1.0f, 0.28f);

    EXPECT_NEAR(projectile.GetSphere().radius, 0.28f, 0.0001f);
}

TEST(Projectile, ConfiguresGravity)
{
    TestProjectile projectile;

    projectile.Configure(1.0f, 0.28f);

    cyclone::Vector3 acceleration =
        projectile.GetBody().getAcceleration();

    EXPECT_NEAR(acceleration.x, 0.0f, 0.0001f);
    EXPECT_NEAR(acceleration.y, -9.81f, 0.0001f);
    EXPECT_NEAR(acceleration.z, 0.0f, 0.0001f);
}

TEST(Projectile, StandardProjectileHasCorrectProfile)
{
    siege_lab::StandardProjectile projectile;

    EXPECT_NEAR(projectile.GetSphere().radius, 0.28f, 0.0001f);
    EXPECT_NEAR(projectile.GetBody().getInverseMass(),
        1.0f, 0.0001f);
}

TEST(Projectile, HeavyProjectileHasCorrectProfile)
{
    siege_lab::HeavyProjectile projectile;

    EXPECT_NEAR(projectile.GetSphere().radius, 0.36f, 0.0001f);
    EXPECT_NEAR(projectile.GetBody().getInverseMass(),
        0.5f, 0.0001f);
}

TEST(Entities, ConcreteCollidersAreLinkedToOwnBodies)
{
    siege_lab::StandardProjectile standard;
    siege_lab::HeavyProjectile heavy;

    EXPECT_EQ(standard.GetSphere().body, &standard.GetBody());
    EXPECT_EQ(heavy.GetSphere().body, &heavy.GetBody());

    EXPECT_NE(&standard.GetSphere(), &heavy.GetSphere());
    EXPECT_NE(&standard.GetBody(), &heavy.GetBody());
}

TEST(Projectile, PR02_InitialVelocityMatchesAim)
{
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 20.0f);

    siege_lab::StandardProjectile projectile;

    projectile.Fire(launcher.GetShotSettings());

    cyclone::Vector3 velocity =
        projectile.GetBody().getVelocity();

    EXPECT_NEAR(velocity.x, 17.3205f, 0.001f);
    EXPECT_NEAR(velocity.y, 10.0f, 0.001f);
    EXPECT_NEAR(velocity.z, 0.0f, 0.001f);
}

TEST(Projectile, FireSetsInitialPosition)
{
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 20.0f);

    siege_lab::StandardProjectile projectile;

    projectile.Fire(launcher.GetShotSettings());

    cyclone::Vector3 position =
        projectile.GetBody().getPosition();

    EXPECT_NEAR(position.x, -8.0f, 0.0001f);
    EXPECT_NEAR(position.y, 1.0f, 0.0001f);
    EXPECT_NEAR(position.z, 0.0f, 0.0001f);
}

TEST(Projectile, FireUpdatesColliderPosition)
{
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 20.0f);

    siege_lab::StandardProjectile projectile;

    projectile.Fire(launcher.GetShotSettings());

    cyclone::Vector3 position =
        projectile.GetSphere().getAxis(3);

    EXPECT_NEAR(position.x, -8.0f, 0.0001f);
    EXPECT_NEAR(position.y, 1.0f, 0.0001f);
    EXPECT_NEAR(position.z, 0.0f, 0.0001f);
}

TEST(Projectile, PR03_FallsUnderGravity)
{
    siege_lab::StandardProjectile projectile;
    cyclone::RigidBody& body = projectile.GetBody();

    body.setPosition(0.0f, 20.0f, 0.0f);
    body.setVelocity(0.0f, 0.0f, 0.0f);
    body.setAcceleration(0.0f, -9.81f, 0.0f);
    body.setDamping(1.0f, 1.0f);
    body.setCanSleep(false);
    body.setAwake(true);
    body.calculateDerivedData();

    constexpr float kFixedDt = 1.0f / 60.0f;

    for (int i = 0; i < 60; ++i)
    {
        body.integrate(kFixedDt);
    }

    EXPECT_NEAR(body.getVelocity().y, -9.81f, 0.05f);
    EXPECT_NEAR(body.getPosition().y, 15.01f, 0.10f);
}

TEST(Projectile, PR04_DoesNotCrossGround)
{
    siege_lab::StandardProjectile projectile;
    cyclone::RigidBody& body = projectile.GetBody();
    cyclone::CollisionSphere& sphere = projectile.GetSphere();

    sphere.radius = 0.5f;

    body.setPosition(0.0f, 3.0f, 0.0f);
    body.setVelocity(0.0f, 0.0f, 0.0f);
    body.setCanSleep(false);
    body.calculateDerivedData();
    sphere.calculateInternals();

    siege_lab::PhysicsWorld world;

    cyclone::CollisionPlane ground;
    ground.direction = cyclone::Vector3(0.0f, 1.0f, 0.0f);
    ground.offset = 0.0f;

    world.RegisterSphere({ 0, 1 }, body, sphere);
    world.RegisterPlane(ground);

    constexpr float kFixedDt = 1.0f / 60.0f;

    for (int i = 0; i < 180; ++i)
    {
        world.Step(kFixedDt);
        EXPECT_GE(body.getPosition().y, 0.0f);
    }

    EXPECT_NEAR(body.getPosition().y, 0.5f, 0.1f);
}