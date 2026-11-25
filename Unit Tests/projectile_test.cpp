#include "pch.h"

#include "projectile.h"

namespace
{
    class TestProjectile : public siege_lab::Projectile
    {
    public:
        void Draw() override
        {
        }

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