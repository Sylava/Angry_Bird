#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_

#include <raylib.h>

namespace siege_lab
{

	struct TrajectorySettings
	{
		Vector3 origin = {};
		Vector3 velocity = {};
		float   radius = 0.28f;
		float   fixed_dt = 1.0f / 60.0f;
	};

}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_H_