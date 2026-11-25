#include "pch.h"

#include "launcher.h"

TEST(Launcher, L01_ZeroAzimuthHasNoZComponent)
{
    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);

    siege_lab::ShotSettings settings =
        launcher.GetShotSettings();

    EXPECT_NEAR(settings.direction.x, 0.8660f, 0.0001f);
    EXPECT_NEAR(settings.direction.y, 0.5000f, 0.0001f);
    EXPECT_NEAR(settings.direction.z, 0.0000f, 0.0001f);
}