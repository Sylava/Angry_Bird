#pragma once
#ifndef SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_BUILDER_H_
#define SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_BUILDER_H_

#include "shot_settings.h"
#include "trajectory_settings.h"

namespace siege_lab
{
	class TrajectorySettingsBuilder
	{
	public:
		TrajectorySettings Build(const ShotSettings& _shot) const;
	};
}  // namespace siege_lab

#endif  // SIEGE_LAB_LIBRARY_TRAJECTORY_SETTINGS_BUILDER_H_
