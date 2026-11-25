#include "pch.h"

#include "orbit_camera.h"

TEST(OrbitCamera, C01_CameraPosition)
{
	siege_lab::OrbitCamera orbit_a({ 2, 1, 0 }, 0, 20, 10);
	Camera3D camera_a = orbit_a.GetCamera();

	EXPECT_NEAR(camera_a.position.x, 2.0f, 0.001f);
	EXPECT_NEAR(camera_a.position.y, 4.4202f, 0.001f);
	EXPECT_NEAR(camera_a.position.z, 9.3969f, 0.001f);

	siege_lab::OrbitCamera orbit_b({ 2, 1, 0 }, 90, 30, 10);
	Camera3D camera_b = orbit_b.GetCamera();

	EXPECT_NEAR(camera_b.position.x, 10.6603f, 0.001f);
	EXPECT_NEAR(camera_b.position.y, 6.0f, 0.001f);
	EXPECT_NEAR(camera_b.position.z, 0.0f, 0.001f);
}

TEST(OrbitCamera, C02_ClampsPitchAndRadius)
{
	siege_lab::OrbitCamera orbit_a({ 0, 0, 0 }, 0, -20, 1);

	EXPECT_FLOAT_EQ(orbit_a.GetPitch(), 10.0f);
	EXPECT_FLOAT_EQ(orbit_a.GetRadius(), 4.0f);

	siege_lab::OrbitCamera orbit_b({ 0, 0, 0 }, 0, 100, 50);

	EXPECT_FLOAT_EQ(orbit_b.GetPitch(), 80.0f);
	EXPECT_FLOAT_EQ(orbit_b.GetRadius(), 25.0f);
}

TEST(OrbitCamera, C03_YawPeriodicity)
{
	siege_lab::OrbitCamera orbit_a({ 0, 0, 0 }, 30, 20, 10);
	siege_lab::OrbitCamera orbit_b({ 0, 0, 0 }, 390, 20, 10);

	Camera3D camera_a = orbit_a.GetCamera();
	Camera3D camera_b = orbit_b.GetCamera();

	EXPECT_NEAR(camera_a.position.x,
		camera_b.position.x, 0.001f);

	EXPECT_NEAR(camera_a.position.y,
		camera_b.position.y, 0.001f);

	EXPECT_NEAR(camera_a.position.z,
		camera_b.position.z, 0.001f);
}

TEST(OrbitCamera, C04_KeyboardFrameRateIndependent)
{
	siege_lab::OrbitCamera orbit_a({ 0, 0, 0 }, 0, 20, 10);
	siege_lab::OrbitCamera orbit_b({ 0, 0, 0 }, 0, 20, 10);

	orbit_a.RotateKeyboard(1, 0, 0.5f);

	orbit_b.RotateKeyboard(1, 0, 0.25f);
	orbit_b.RotateKeyboard(1, 0, 0.25f);

	EXPECT_NEAR(orbit_a.GetYaw(), 45.0f, 0.001f);
	EXPECT_NEAR(orbit_b.GetYaw(), 45.0f, 0.001f);
}

TEST(OrbitCamera, C05_MouseFrameRateIndependent)
{
	siege_lab::OrbitCamera orbit_a({ 0, 0, 0 }, 0, 20, 10);
	siege_lab::OrbitCamera orbit_b({ 0, 0, 0 }, 0, 20, 10);

	for (int i = 0; i < 60; ++i)
	{
		orbit_a.RotateMouse(2.0f, 0.0f);
	}

	for (int i = 0; i < 30; ++i)
	{
		orbit_b.RotateMouse(4.0f, 0.0f);
	}

	EXPECT_NEAR(orbit_a.GetYaw(), 30.0f, 0.001f);
	EXPECT_NEAR(orbit_b.GetYaw(), 30.0f, 0.001f);
}

TEST(OrbitCamera, ZoomChangesRadius)
{
	siege_lab::OrbitCamera orbit({ 0, 0, 0 }, 0, 20, 10);

	orbit.Zoom(1.0f);
	EXPECT_FLOAT_EQ(orbit.GetRadius(), 9.0f);

	orbit.Zoom(-1.0f);
	EXPECT_FLOAT_EQ(orbit.GetRadius(), 10.0f);
}

TEST(OrbitCamera, ZoomClampsRadius)
{
	siege_lab::OrbitCamera orbit({ 0, 0, 0 }, 0, 20, 10);

	orbit.Zoom(100.0f);
	EXPECT_FLOAT_EQ(orbit.GetRadius(), 4.0f);

	orbit.Zoom(-100.0f);
	EXPECT_FLOAT_EQ(orbit.GetRadius(), 25.0f);
}