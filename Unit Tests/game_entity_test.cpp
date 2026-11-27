#include "pch.h"

#include "game_entity.h"

namespace
{
    class TestPhysicsEntity : public siege_lab::GameEntity
    {
    public:
        void Draw() override
        {
        }
    };
}

TEST(GameEntity, OwnsIndependentRigidBody)
{
    TestPhysicsEntity first;
    TestPhysicsEntity second;

    first.GetBody().setMass(2.0f);
    second.GetBody().setMass(5.0f);

    EXPECT_NEAR(first.GetBody().getMass(), 2.0f, 0.0001f);
    EXPECT_NEAR(second.GetBody().getMass(), 5.0f, 0.0001f);

    EXPECT_NE(&first.GetBody(), &second.GetBody());
}