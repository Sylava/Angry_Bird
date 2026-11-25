#include "trajectory_predictor.h"

namespace siege_lab
{

    TrajectoryResult TrajectoryPredictor::Predict(
        const TrajectorySettings& _settings) const
    {
        TrajectoryResult result;
        result.positions.push_back(_settings.origin);

        return result;
    }

}  // namespace siege_lab