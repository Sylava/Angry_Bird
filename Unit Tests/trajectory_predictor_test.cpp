#include "pch.h"
#include <gtest/gtest.h>

#include "trajectory_predictor.h"
#include "trajectory_result.h"
#include "trajectory_settings.h"

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

}