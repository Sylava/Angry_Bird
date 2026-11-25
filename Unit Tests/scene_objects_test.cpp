#include "pch.h"

#include "scene_objects.h"


class TestEntity : public siege_lab::GameEntity
{
public:
	void Draw() override
	{
	}
};

class TestEntityWithArgs : public siege_lab::GameEntity
{
private:
	int m_value;

public:
	explicit TestEntityWithArgs(int _value)
	{
		m_value = _value;
	}

	void Draw() override
	{
	}

	int GetValue() const
	{
		return m_value;
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

TEST(SceneObjects, CreatesEntityWithArguments)
{
	siege_lab::SceneObjects<4> scene;

	auto id = scene.CreateEntity<TestEntityWithArgs>(42);

	auto entity = dynamic_cast<TestEntityWithArgs*>(scene.Get(id));

	ASSERT_NE(entity, nullptr);
	EXPECT_EQ(entity->GetValue(), 42);
}

TEST(SceneObjects, RemovalIsDeferred)
{
	siege_lab::SceneObjects<4> scene;

	auto id = scene.CreateEntity<TestEntity>();

	ASSERT_NE(scene.Get(id), nullptr);

	EXPECT_TRUE(scene.RequestRemoval(id));
	EXPECT_NE(scene.Get(id), nullptr);
	EXPECT_EQ(scene.GetCount(), 1);
}

TEST(SceneObjects, RejectsDuplicateRemovalRequests)
{
	siege_lab::SceneObjects<4> scene;

	auto id = scene.CreateEntity<TestEntity>();

	EXPECT_TRUE(scene.RequestRemoval(id));
	EXPECT_FALSE(scene.RequestRemoval(id));

	EXPECT_NE(scene.Get(id), nullptr);
	EXPECT_EQ(scene.GetCount(), 1);
}

TEST(SceneObjects, FlushRemovalsDestroysEntities)
{
	siege_lab::SceneObjects<4> scene;

	auto id_a = scene.CreateEntity<TestEntity>();
	auto id_b = scene.CreateEntity<TestEntity>();

	ASSERT_TRUE(scene.RequestRemoval(id_a));

	scene.FlushRemovals();

	EXPECT_EQ(scene.Get(id_a), nullptr);
	EXPECT_NE(scene.Get(id_b), nullptr);
	EXPECT_EQ(scene.GetCount(), 1);
}