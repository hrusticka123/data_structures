#include "fib_heap.h"
#include <iostream>

using namespace fibonacci_heap;

void heap::decrease(int identifier, int key)
{
	//find corresponding node
	auto node = map[identifier];
	//node exists and the new key is smaller than the current one
	if (node != nullptr && node->key >= key)
	{
		node->key = key;

		//no need to (cascade) cut if the node is actually minimum/node's parent's key is smaller than node's
		if ((node->parent == nullptr || node->key < node->parent->key) && node != min)
		{
			//cut the node first from minimum
			decrease_steps++;
			min = cut(min, node);
			auto parent = node->parent;
			node->parent = nullptr;
			//while there is marked parent, keep cutting it node from him
			while (parent != nullptr && parent->mark)
			{
				decrease_steps++;
				min = cut(min, parent);
				node = parent;
				parent = node->parent;
				node->parent = nullptr;
			}
			//mark if there is parent
			if (parent != nullptr)
				parent->mark = true;
		}	
	}
	//dev
	if (DEV)
	{
		traverse(min);
		std::cout << std::endl;
	}
}
