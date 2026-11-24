#include "pch.h"
#include <memory>

#include "object_pool.h"


TEST(Pool, P01_CapacityLimit)
{
	siege_lab::ObjectPool<int, 3> pool;

	auto id_a = pool.Create(10);
	auto id_b = pool.Create(20);
	auto id_c = pool.Create(30);
	auto id_d = pool.Create(40);

	ASSERT_NE(pool.Get(id_a), nullptr);
	ASSERT_NE(pool.Get(id_b), nullptr);
	ASSERT_NE(pool.Get(id_c), nullptr);

	EXPECT_EQ(id_d.slot, -1);

	EXPECT_EQ(*pool.Get(id_a), 10);
	EXPECT_EQ(*pool.Get(id_b), 20);
	EXPECT_EQ(*pool.Get(id_c), 30);

	EXPECT_EQ(pool.GetCount(), 3);
}

TEST(Pool, P02_RecycledSlotChangesGeneration)
{
	siege_lab::ObjectPool<int, 1> pool;

	auto id_a = pool.Create(7);

	ASSERT_TRUE(pool.Destroy(id_a));

	auto id_b = pool.Create(42);

	EXPECT_EQ(id_b.slot, id_a.slot);
	EXPECT_NE(id_b.generation, id_a.generation);
}

TEST(Pool, P03_StaleHandleRejected)
{
	siege_lab::ObjectPool<int, 1> pool;

	auto id_a = pool.Create(7);

	ASSERT_TRUE(pool.Destroy(id_a));

	auto id_b = pool.Create(42);

	EXPECT_EQ(pool.Get(id_a), nullptr);

	ASSERT_NE(pool.Get(id_b), nullptr);
	EXPECT_EQ(*pool.Get(id_b), 42);
}

TEST(Pool, P04_LiveAddressStable)
{
	siege_lab::ObjectPool<int, 3> pool;

	auto id_a = pool.Create(10);
	int* address = pool.Get(id_a);

	ASSERT_NE(address, nullptr);

	pool.Create(20);
	pool.Create(30);

	EXPECT_EQ(pool.Get(id_a), address);
	EXPECT_EQ(*address, 10);
}

TEST(Pool, P05_ClearInvalidatesHandles)
{
	siege_lab::ObjectPool<int, 2> pool;

	auto id_a = pool.Create(10);
	auto id_b = pool.Create(20);

	pool.Clear();

	EXPECT_EQ(pool.GetCount(), 0);
	EXPECT_EQ(pool.Get(id_a), nullptr);
	EXPECT_EQ(pool.Get(id_b), nullptr);

	auto id_c = pool.Create(30);

	ASSERT_NE(pool.Get(id_c), nullptr);
	EXPECT_EQ(*pool.Get(id_c), 30);

	EXPECT_EQ(pool.Get(id_a), nullptr);
	EXPECT_EQ(pool.Get(id_b), nullptr);
}

TEST(Pool, ForEachVisitsLiveObjects)
{
	siege_lab::ObjectPool<int, 4> pool;

	pool.Create(10);
	auto id_b = pool.Create(20);
	pool.Create(30);
	pool.Create(40);

	pool.Destroy(id_b);

	int sum = 0;
	int count = 0;

	pool.ForEach([&](int& _value)
		{
			sum += _value;
			++count;
		});

	EXPECT_EQ(sum, 80);
	EXPECT_EQ(count, 3);
}

TEST(Pool, SupportsUniquePtr)
{
	siege_lab::ObjectPool<std::unique_ptr<int>, 2> pool;

	auto id = pool.Create(std::make_unique<int>(42));

	ASSERT_NE(pool.Get(id), nullptr);
	EXPECT_EQ(**pool.Get(id), 42);

	EXPECT_TRUE(pool.Destroy(id));
	EXPECT_EQ(pool.Get(id), nullptr);
	EXPECT_EQ(pool.GetCount(), 0);
}