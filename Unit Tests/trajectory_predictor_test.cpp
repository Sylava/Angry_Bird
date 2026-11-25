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

}