#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_PREDICTOR_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_PREDICTOR_H_

#include "trajectory_result.h"
#include "trajectory_settings.h"

namespace siege_lab
{

	class TrajectoryPredictor
	{
	public:
		TrajectoryResult Predict(const TrajectorySettings& _settings) const;
	};

}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_PREDICTOR_H_