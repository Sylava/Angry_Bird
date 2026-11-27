#include "pch.h"

#include "gtest/gtest.h"

#include "physics_world.h"
#include "scene_objects.h"
#include "standard_projectile.h"

namespace siege_lab
{
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
}  // namespace siege_lab