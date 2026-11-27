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

		bool has_contact = false;
		Vector3 contact_point = {};
		int contact_step = -1;
	};

}

#endif