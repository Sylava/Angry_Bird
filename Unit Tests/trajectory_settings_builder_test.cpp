#include "pch.h"

#include <gtest/gtest.h>

#include "shot_settings.h"
#include "trajectory_settings_builder.h"
#include "standard_projectile.h"

namespace siege_lab
{
	TEST(TrajectorySettingsBuilder, ConvertsShotSettings)
	{
		ShotSettings shot{};
		shot.origin = { -8.0f, 1.0f, 0.0f };
		shot.direction = { 0.6f, 0.8f, 0.0f };
		shot.speed = 20.0f;
		shot.projectile_kind = ProjectileKind::kStandard;

		const TrajectorySettingsBuilder builder;
		const TrajectorySettings settings = builder.Build(shot);

		EXPECT_FLOAT_EQ(settings.origin.x, -8.0f);
		EXPECT_FLOAT_EQ(settings.origin.y, 1.0f);
		EXPECT_FLOAT_EQ(settings.origin.z, 0.0f);

		EXPECT_FLOAT_EQ(settings.velocity.x, 12.0f);
		EXPECT_FLOAT_EQ(settings.velocity.y, 16.0f);
		EXPECT_FLOAT_EQ(settings.velocity.z, 0.0f);
	}

	TEST(TrajectorySettingsBuilder, UsesHeavyProjectileProfile)
	{
		ShotSettings shot{};
		shot.projectile_kind = ProjectileKind::kHeavy;

		const TrajectorySettingsBuilder builder;
		const TrajectorySettings settings = builder.Build(shot);

		EXPECT_FLOAT_EQ(settings.mass, 2.0f);
		EXPECT_FLOAT_EQ(settings.radius, 0.36f);
	}

	TEST(TrajectorySettingsBuilder, UsesStandardProjectileProfile)
	{
		ShotSettings shot{};
		shot.projectile_kind = ProjectileKind::kStandard;

		const TrajectorySettingsBuilder builder;
		const TrajectorySettings settings = builder.Build(shot);

		EXPECT_FLOAT_EQ(settings.mass, 1.0f);
		EXPECT_FLOAT_EQ(settings.radius, 0.28f);
	}

	TEST(TrajectorySettingsBuilder, MatchesProjectilePhysics)
	{
		ShotSettings shot{};
		shot.projectile_kind = ProjectileKind::kStandard;

		StandardProjectile projectile;
		cyclone::RigidBody& body = projectile.GetBody();

		const TrajectorySettingsBuilder builder;
		const TrajectorySettings settings = builder.Build(shot);

		const cyclone::Vector3 acceleration = body.getAcceleration();

		EXPECT_NEAR(settings.acceleration.x, acceleration.x, 0.0001f);
		EXPECT_NEAR(settings.acceleration.y, acceleration.y, 0.0001f);
		EXPECT_NEAR(settings.acceleration.z, acceleration.z, 0.0001f);

		EXPECT_NEAR(settings.damping,
			body.getLinearDamping(), 0.0001f);

		EXPECT_NEAR(settings.angular_damping,
			body.getAngularDamping(), 0.0001f);
	}
}  // namespace siege_lab