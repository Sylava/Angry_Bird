#include "pch.h"

#include "launcher.h"
#include "projectile_factory.h"

TEST(ProjectileFactory, CreatesHeavyProjectile)
{
    siege_lab::SceneObjects<4> scene;
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);

    siege_lab::InputSnapshot input{};
    input.select_heavy = true;
    launcher.Update(input, 0.0f);

    siege_lab::EntityId id = siege_lab::ProjectileFactory::Create(
        scene, launcher.GetShotSettings());

    siege_lab::GameEntity* entity = scene.Get(id);

    ASSERT_NE(entity, nullptr);
    EXPECT_NEAR(entity->GetBody().getMass(), 2.0f, 0.0001f);
}

TEST(ProjectileFactory, CreatesStandardProjectile)
{
    siege_lab::SceneObjects<4> scene;
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);

    siege_lab::InputSnapshot input{};
    input.select_heavy = true;
    launcher.Update(input, 0.0f);

    input.select_heavy = false;
    input.select_standard = true;
    launcher.Update(input, 0.0f);

    siege_lab::EntityId id = siege_lab::ProjectileFactory::Create(
        scene, launcher.GetShotSettings());

    siege_lab::GameEntity* entity = scene.Get(id);

    ASSERT_NE(entity, nullptr);
    EXPECT_NEAR(entity->GetBody().getMass(), 1.0f, 0.0001f);
}

TEST(ProjectileFactory, CreatedProjectileReceivesShotSettings)
{
    siege_lab::SceneObjects<4> scene;
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);

    siege_lab::EntityId id = siege_lab::ProjectileFactory::Create(
        scene, launcher.GetShotSettings());

    siege_lab::GameEntity* entity = scene.Get(id);
    ASSERT_NE(entity, nullptr);

    cyclone::Vector3 position = entity->GetBody().getPosition();
    cyclone::Vector3 velocity = entity->GetBody().getVelocity();

    EXPECT_NEAR(position.x, -8.0f, 0.0001f);
    EXPECT_NEAR(position.y, 1.0f, 0.0001f);
    EXPECT_NEAR(position.z, 0.0f, 0.0001f);

    EXPECT_NEAR(velocity.x, 13.8564f, 0.001f);
    EXPECT_NEAR(velocity.y, 8.0f, 0.001f);
    EXPECT_NEAR(velocity.z, 0.0f, 0.001f);
}