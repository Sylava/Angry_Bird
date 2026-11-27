#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_

#include <vector>

#include <raylib.h>

#include "trajectory_obstacle.h"

namespace siege_lab
{

	struct TrajectorySettings
	{
		Vector3 origin = {};
		Vector3 velocity = {};
		Vector3 acceleration = { 0.0f, -9.81f, 0.0f };

		float mass = 1.0f;
		float radius = 0.28f;
		float fixed_dt = 1.0f / 60.0f;
		float damping = 1.0f;
		float angular_damping = 0.85f;

		int max_steps = 120;

		std::vector<TrajectoryObstacle> obstacles;
	};

}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_