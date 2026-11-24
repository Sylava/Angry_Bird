#include "pch.h"

#include "scene_object.h"


class TestEntity : public siege_lab::GameEntity
{
public:
	void Draw() override
	{
	}
};


TEST(SceneObjects, CreateAndGetEntities)
{
	siege_lab::SceneObjects<4> scene;

	auto id_a = scene.CreateEntity<TestEntity>();
	auto id_b = scene.CreateEntity<TestEntity>();

	EXPECT_NE(id_a.slot, -1);
	EXPECT_NE(id_b.slot, -1);
	EXPECT_NE(id_a.slot, id_b.slot);

	EXPECT_NE(scene.Get(id_a), nullptr);
	EXPECT_NE(scene.Get(id_b), nullptr);

	EXPECT_EQ(scene.GetCount(), 2);
}