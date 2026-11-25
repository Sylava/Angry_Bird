#include "pch.h"

#include "camera_manager.h"


class FakeCameraController : public siege_lab::ICameraController
{
public:
    Camera3D camera{};
    int update_count = 0;

    void Update(const siege_lab::InputSnapshot& _input,
        float _dt) override
    {
        ++update_count;
    }

    Camera3D GetCamera() const override
    {
        return camera;
    }
};

TEST(CameraManager, ReturnsActiveCamera)
{
    siege_lab::CameraManager manager;
    FakeCameraController controller;

    controller.camera.position = { 1, 2, 3 };

    manager.SetController(&controller);

    Camera3D camera = manager.GetCamera();

    EXPECT_FLOAT_EQ(camera.position.x, 1.0f);
    EXPECT_FLOAT_EQ(camera.position.y, 2.0f);
    EXPECT_FLOAT_EQ(camera.position.z, 3.0f);
}

TEST(CameraManager, UpdatesActiveController)
{
    siege_lab::CameraManager manager;
    FakeCameraController controller;
    siege_lab::InputSnapshot input;

    manager.SetController(&controller);
    manager.Update(input, 0.1f);

    EXPECT_EQ(controller.update_count, 1);
}

TEST(CameraManager, SwitchesController)
{
    siege_lab::CameraManager manager;
    FakeCameraController first;
    FakeCameraController second;
    siege_lab::InputSnapshot input;

    first.camera.position = { 1, 2, 3 };
    second.camera.position = { 4, 5, 6 };

    manager.SetController(&first);
    manager.Update(input, 0.1f);

    manager.SetController(&second);
    manager.Update(input, 0.1f);

    EXPECT_EQ(first.update_count, 1);
    EXPECT_EQ(second.update_count, 1);
    EXPECT_FLOAT_EQ(manager.GetCamera().position.x, 4.0f);
}

TEST(CameraManager, HandlesNoController)
{
    siege_lab::CameraManager manager;
    siege_lab::InputSnapshot input;

    manager.Update(input, 0.1f);

    Camera3D camera = manager.GetCamera();

    EXPECT_FLOAT_EQ(camera.position.x, 0.0f);
    EXPECT_FLOAT_EQ(camera.position.y, 0.0f);
    EXPECT_FLOAT_EQ(camera.position.z, 0.0f);
}

TEST(CameraManager, CanRemoveController)
{
    siege_lab::CameraManager manager;
    FakeCameraController controller;
    siege_lab::InputSnapshot input;

    manager.SetController(&controller);
    manager.Update(input, 0.1f);

    manager.SetController(nullptr);
    manager.Update(input, 0.1f);

    EXPECT_EQ(controller.update_count, 1);
}