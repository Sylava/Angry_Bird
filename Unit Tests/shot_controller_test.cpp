#include "pch.h"

#include "launcher.h"
#include "shot_controller.h"

TEST(Projectile, PR01_OnlyOneShotPerKeyPress)
{
    siege_lab::SceneObjects<16> scene;
    siege_lab::ShotController controller(5);

    siege_lab::Launcher launcher(
        { -8.0f, 1.0f, 0.0f }, 0.0f, 30.0f, 16.0f);

    siege_lab::InputSnapshot input{};

    for (int i = 0; i < 10; ++i)
    {
        input.fire_pressed = (i == 0);

        controller.Update(
            input, launcher.GetShotSettings(), scene);
    }

    EXPECT_EQ(scene.GetCount(), 1u);
    EXPECT_EQ(controller.GetAmmo(), 4);
}