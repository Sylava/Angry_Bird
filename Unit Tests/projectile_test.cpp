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
    };
}

TEST(Projectile, ColliderIsLinkedToOwnBody)
{
    TestProjectile projectile;

    EXPECT_EQ(
        projectile.GetSphere().body,
        &projectile.GetBody());
}