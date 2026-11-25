#include "pch.h"

#include "heavy_projectile.h"
#include "standard_projectile.h"
#include "projectile.h"
#include "launcher.h"

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