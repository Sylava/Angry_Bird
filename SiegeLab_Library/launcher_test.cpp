#include "pch.h"
#include <cmath>

#include "launcher.h"
#include "orbit_camera.h"

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

TEST(Launcher, L02_DirectionIsNormalized)
{
    siege_lab::Launcher launcher_a(
        { -8, 1, 0 }, 30.0f, 30.0f, 16.0f);
    siege_lab::Launcher launcher_b(
        { -8, 1, 0 }, -30.0f, 45.0f, 16.0f);

    Vector3 a = launcher_a.GetShotSettings().direction;
    Vector3 b = launcher_b.GetShotSettings().direction;

    EXPECT_NEAR(a.x, 0.7500f, 0.0001f);
    EXPECT_NEAR(a.y, 0.5000f, 0.0001f);
    EXPECT_NEAR(a.z, 0.4330f, 0.0001f);

    EXPECT_NEAR(b.x, 0.6124f, 0.0001f);
    EXPECT_NEAR(b.y, 0.7071f, 0.0001f);
    EXPECT_NEAR(b.z, -0.3536f, 0.0001f);

    float norm_a = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    float norm_b = std::sqrt(b.x * b.x + b.y * b.y + b.z * b.z);

    EXPECT_NEAR(norm_a, 1.0f, 0.0001f);
    EXPECT_NEAR(norm_b, 1.0f, 0.0001f);
}

TEST(Launcher, L03_ParametersAreClamped)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 45.0f, -10.0f, 30.0f);

    EXPECT_FLOAT_EQ(launcher.GetYaw(), 30.0f);
    EXPECT_FLOAT_EQ(launcher.GetPitch(), 5.0f);
    EXPECT_FLOAT_EQ(launcher.GetSpeed(), 22.0f);
}

TEST(Launcher, L04_AimIsIndependentFromCamera)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 20.0f, 30.0f, 16.0f);

    siege_lab::OrbitCamera camera(
        { 0, 1, 0 }, 0.0f, 30.0f, 10.0f);

    Vector3 before = launcher.GetShotSettings().direction;

    camera.RotateKeyboard(1.0f, 0.0f, 120.0f / 90.0f);

    Vector3 after = launcher.GetShotSettings().direction;

    EXPECT_NEAR(camera.GetYaw(), 120.0f, 0.0001f);

    EXPECT_NEAR(before.x, 0.8138f, 0.0001f);
    EXPECT_NEAR(before.y, 0.5000f, 0.0001f);
    EXPECT_NEAR(before.z, 0.2962f, 0.0001f);

    EXPECT_NEAR(after.x, before.x, 0.0001f);
    EXPECT_NEAR(after.y, before.y, 0.0001f);
    EXPECT_NEAR(after.z, before.z, 0.0001f);
}

TEST(Launcher, L05_SelectsProjectileKind)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 0.0f, 30.0f, 16.0f);

    EXPECT_EQ(launcher.GetShotSettings().projectile_kind,
        siege_lab::ProjectileKind::kStandard);

    launcher.SetProjectileKind(
        siege_lab::ProjectileKind::kHeavy);

    EXPECT_EQ(launcher.GetShotSettings().projectile_kind,
        siege_lab::ProjectileKind::kHeavy);

    launcher.SetProjectileKind(
        siege_lab::ProjectileKind::kStandard);

    EXPECT_EQ(launcher.GetShotSettings().projectile_kind,
        siege_lab::ProjectileKind::kStandard);

    EXPECT_FLOAT_EQ(launcher.GetShotSettings().speed, 16.0f);
}

TEST(Launcher, AdjustAimChangesAngles)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 0.0f, 30.0f, 16.0f);

    launcher.AdjustAim(10.0f, -5.0f);

    EXPECT_FLOAT_EQ(launcher.GetYaw(), 10.0f);
    EXPECT_FLOAT_EQ(launcher.GetPitch(), 25.0f);
}

TEST(Launcher, AdjustSpeedChangesSpeed)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 0.0f, 30.0f, 16.0f);

    launcher.AdjustSpeed(3.0f);

    EXPECT_FLOAT_EQ(launcher.GetSpeed(), 19.0f);
}

TEST(Launcher, AdjustmentsRespectLimits)
{
    siege_lab::Launcher launcher(
        { -8, 1, 0 }, 0.0f, 30.0f, 16.0f);

    launcher.AdjustAim(100.0f, 100.0f);
    launcher.AdjustSpeed(100.0f);

    EXPECT_FLOAT_EQ(launcher.GetYaw(), 30.0f);
    EXPECT_FLOAT_EQ(launcher.GetPitch(), 55.0f);
    EXPECT_FLOAT_EQ(launcher.GetSpeed(), 22.0f);

    launcher.AdjustAim(-100.0f, -100.0f);
    launcher.AdjustSpeed(-100.0f);

    EXPECT_FLOAT_EQ(launcher.GetYaw(), -30.0f);
    EXPECT_FLOAT_EQ(launcher.GetPitch(), 5.0f);
    EXPECT_FLOAT_EQ(launcher.GetSpeed(), 8.0f);
}