#include "pch.h"

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