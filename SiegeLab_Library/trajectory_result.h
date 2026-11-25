#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_RESULT_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_RESULT_H_

#include <vector>

#include <raylib.h>

namespace siege_lab
{

	struct TrajectoryResult
	{
		std::vector<Vector3> positions;
	};

}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_RESULT_H_