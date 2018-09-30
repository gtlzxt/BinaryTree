#include "BinarySearchTree.h"
#include "gtest/gtest.h"
#include <iostream>
#include <set>
#include <random>

void checkSetAndTreeEqual(const std::set<int>& s, const BinarySearchTree<int>& tree)
{
	std::set<int> data = s;
	auto iter = tree.begin();
	while (iter != tree.end())
	{
		std::set<int>::iterator it = data.find(*iter);
		ASSERT_NE(it, data.end());
		data.erase(it);
		iter++;
	}
	EXPECT_EQ(0, data.size());
}

TEST(BinarySearchTreeTest, insertTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;	
	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	checkSetAndTreeEqual(data, tree);
}

TEST(BinarySearchTreeTest, removeTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	std::random_device rd2;
	for (int i = 0; i < data.size(); i++)
	{
		int removeIndex = rd2() % data.size();
		auto it = data.begin();
		while (removeIndex-- > 0)
		{
			it++;
		}

		tree.remove(*it);
		data.erase(it);
		checkSetAndTreeEqual(data, tree);
	}
}

TEST(BinarySearchTreeTest, findMaxTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	int max = *std::max_element(data.begin(), data.end());
	EXPECT_EQ(max, tree.findMax());
}

TEST(BinarySearchTreeTest, findMinTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	int min = *std::min_element(data.begin(), data.end());
	EXPECT_EQ(min, tree.findMin());
}

TEST(BinarySearchTreeTest, containsTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		EXPECT_TRUE(tree.contains(*iter));
	}
}

TEST(BinarySearchTreeTest, sizeTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
		EXPECT_EQ(data.size(), tree.size());
	}

	unsigned int size = tree.size();
	for (auto it = data.begin(); it != data.end(); it++)
	{
		tree.remove(*it);
		EXPECT_EQ(--size, tree.size());
	}
}

TEST(BinarySearchTreeTest, isEmptyTest)
{
	int dataSize = 100;
	BinarySearchTree<int> tree;
	std::set<int> data;
	std::random_device rd;

	for (int i = 0; i < dataSize; i++)
	{
		int value = rd() % 1000;
		data.insert(value);
		tree.insert(value);
	}

	tree.makeEmpty();

	EXPECT_TRUE(tree.isEmpty());
}