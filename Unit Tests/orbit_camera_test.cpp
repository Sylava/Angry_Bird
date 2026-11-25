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