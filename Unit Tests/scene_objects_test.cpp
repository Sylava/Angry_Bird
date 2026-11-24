#include "pch.h"

#include "scene_object.h"


class TestEntity : public siege_lab::GameEntity
{
public:
	void Draw() override
	{
	}
};

template<typename T>
concept CanCreateEntity = requires(siege_lab::SceneObjects<4>&_scene)
{
	_scene.template CreateEntity<T>();
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

TEST(SceneObjects, RejectsInvalidEntityTypes)
{
	EXPECT_TRUE(CanCreateEntity<TestEntity>);
	EXPECT_FALSE(CanCreateEntity<int>);
	EXPECT_FALSE(CanCreateEntity<siege_lab::GameEntity>);
}