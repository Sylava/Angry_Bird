#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_RENDERER_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_RENDERER_H_

#include "trajectory_result.h"

namespace siege_lab
{
	class TrajectoryRenderer
	{
	public:
		void Draw(const TrajectoryResult& _result) const;
	};
}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_RENDERER_H_