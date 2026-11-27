#include "pch.h"
#include <gtest/gtest.h>

#include "trajectory_predictor.h"
#include "trajectory_result.h"
#include "trajectory_settings.h"
#include <cyclone/body.h>
#include "trajectory_obstacle.h"

namespace siege_lab
{

	TEST(Trajectory, T01_StartsAtLauncher)
	{
		TrajectorySettings settings;
		settings.origin = { -8.0f, 1.0f, 0.0f };
		settings.velocity = { 10.0f, 5.0f, 0.0f };
		settings.radius = 0.20f;
		settings.fixed_dt = 1.0f / 60.0f;

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_FALSE(result.positions.empty());

		EXPECT_NEAR(result.positions.front().x, -8.0f, 0.0001f);
		EXPECT_NEAR(result.positions.front().y, 1.0f, 0.0001f);
		EXPECT_NEAR(result.positions.front().z, 0.0f, 0.0001f);
	}

	TEST(Trajectory, T02_StopsAtGroundContact)
	{
		TrajectorySettings settings;
		settings.origin = { 0.0f, 1.51f, 0.0f };
		settings.velocity = { 0.0f, -1.0f, 0.0f };
		settings.acceleration = {};
		settings.radius = 0.5f;
		settings.damping = 1.0f;
		settings.fixed_dt = 1.0f / 60.0f;
		settings.max_steps = 120;

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_TRUE(result.has_contact);
		ASSERT_EQ(result.positions.size(), 62u);

		EXPECT_EQ(result.contact_step, 61);
		EXPECT_NEAR(result.positions.back().y, 0.4933f, 0.005f);
		EXPECT_NEAR(result.contact_point.y, 0.0f, 0.005f);
	}

	void InitializeWitness(cyclone::RigidBody& _body)
	{
		_body.setMass(1.0f);
		_body.setPosition(-8.0f, 1.0f, 0.0f);
		_body.setVelocity(12.0f, 5.0f, 0.0f);
		_body.calculateDerivedData();
	}

	TEST(Trajectory, T03_DoesNotModifyRealBody)
	{
		cyclone::RigidBody real_body;
		InitializeWitness(real_body);

		TrajectorySettings settings;
		settings.origin = { -8.0f, 1.0f, 0.0f };
		settings.velocity = { 12.0f, 5.0f, 0.0f };
		settings.max_steps = 20;

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		EXPECT_EQ(result.positions.size(), 21u);
		EXPECT_FALSE(result.has_contact);

		const cyclone::Vector3 position = real_body.getPosition();
		const cyclone::Vector3 velocity = real_body.getVelocity();

		EXPECT_FLOAT_EQ(position.x, -8.0f);
		EXPECT_FLOAT_EQ(position.y, 1.0f);
		EXPECT_FLOAT_EQ(position.z, 0.0f);

		EXPECT_FLOAT_EQ(velocity.x, 12.0f);
		EXPECT_FLOAT_EQ(velocity.y, 5.0f);
		EXPECT_FLOAT_EQ(velocity.z, 0.0f);
	}

	TEST(Trajectory, T04_StopsAtObstacleContact)
	{
		TrajectorySettings settings;
		settings.origin = { -2.03f, 1.0f, 0.0f };
		settings.velocity = { 3.0f, 0.0f, 0.0f };
		settings.acceleration = {};
		settings.radius = 0.20f;
		settings.damping = 1.0f;

		TrajectoryObstacle obstacle;
		obstacle.position = { 0.0f, 1.0f, 0.0f };
		obstacle.half_size = { 0.25f, 0.25f, 0.25f };
		settings.obstacles.push_back(obstacle);

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_TRUE(result.has_contact);
		ASSERT_EQ(result.positions.size(), 33u);

		EXPECT_EQ(result.contact_step, 32);
		EXPECT_NEAR(result.positions.back().x, -0.43f, 0.005f);
		EXPECT_NEAR(result.contact_point.x, -0.25f, 0.005f);
		EXPECT_NEAR(result.contact_point.y, 1.0f, 0.005f);
	}

	TEST(Trajectory, T05_StopsAtRotatedObstacle)
	{
		TrajectorySettings settings;
		settings.origin = { -2.03f, 1.0f, 0.0f };
		settings.velocity = { 3.0f, 0.0f, 0.0f };
		settings.acceleration = {};
		settings.radius = 0.20f;
		settings.damping = 1.0f;

		TrajectoryObstacle obstacle;
		obstacle.position = { 0.0f, 1.0f, 0.0f };
		obstacle.half_size = { 0.25f, 0.25f, 1.0f };
		obstacle.orientation = { 0.0f, 0.70710678f,
								0.0f, 0.70710678f };
		settings.obstacles.push_back(obstacle);

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_TRUE(result.has_contact);
		ASSERT_EQ(result.contact_step, 17);
		EXPECT_EQ(result.positions.size(), 18u);
		EXPECT_NEAR(result.positions.back().x, -1.18f, 0.005f);
		EXPECT_NEAR(result.contact_point.x, -1.0f, 0.005f);
	}

	TEST(Trajectory, T06_HeavyProjectileGroundContact)
	{
		TrajectorySettings settings;
		settings.origin = { 0.0f, 1.505f, 0.0f };
		settings.velocity = { 0.0f, -1.0f, 0.0f };
		settings.acceleration = {};
		settings.mass = 2.0f;
		settings.radius = 0.36f;
		settings.damping = 1.0f;
		settings.max_steps = 120;

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_TRUE(result.has_contact);
		EXPECT_EQ(result.contact_step, 69);
		ASSERT_EQ(result.positions.size(), 70u);
		EXPECT_NEAR(result.positions.back().y, 0.355f, 0.005f);
		EXPECT_NEAR(result.contact_point.y, 0.0f, 0.005f);
	}

	TEST(Trajectory, T07_AppliesGravity)
	{
		TrajectorySettings settings;
		settings.origin = { 0.0f, 10.0f, 0.0f };
		settings.velocity = { 10.0f, 5.0f, 0.0f };
		settings.acceleration = { 0.0f, -9.81f, 0.0f };
		settings.damping = 1.0f;
		settings.max_steps = 60;

		const TrajectoryPredictor predictor;
		const TrajectoryResult result = predictor.Predict(settings);

		ASSERT_EQ(result.positions.size(), 61u);
		EXPECT_FALSE(result.has_contact);

		EXPECT_NEAR(result.positions[30].x, 5.0f, 0.005f);
		EXPECT_NEAR(result.positions[30].y, 11.232875f, 0.005f);

		EXPECT_NEAR(result.positions.back().x, 10.0f, 0.005f);
		EXPECT_NEAR(result.positions.back().y, 10.01325f, 0.005f);
		EXPECT_NEAR(result.positions.back().z, 0.0f, 0.005f);
	}

}