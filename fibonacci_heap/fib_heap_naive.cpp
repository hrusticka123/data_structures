#include "fib_heap_naive.h"
#include <iostream>

using namespace fibonacci_heap;

void naive_heap::decrease(int identifier, int key)
{
	//find corresponding node
	auto node = map[identifier];
	//node exists and the new key is smaller than the current one
	if (node != nullptr && node->key >= key)
	{
		node->key = key;
		//no need to cut if the node is actually minimum/node's parent's key is smaller than node's
		if ((node->parent == nullptr || node->key < node->parent->key) && node != min)
		{
			//cut the node from minimum
			decrease_steps++;
			min = cut(min, node);
			node->parent = nullptr;
		}
	}
	//dev
	if (DEV)
	{
		traverse(min);
		std::cout << std::endl;
	}
}
