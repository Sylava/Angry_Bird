#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_OBSTACLE_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_OBSTACLE_H_

#include <raylib.h>

namespace siege_lab
{

	struct TrajectoryObstacle
	{
		Vector3 position = {};
		Vector3 half_size = {};
	};

}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_OBSTACLE_H_