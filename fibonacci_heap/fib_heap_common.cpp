#include "fib_heap_common.h"
#include <iostream>
#include <string>

using namespace fibonacci_heap;


void common_heap::insert(int identifier, int key)
{
	node * new_node = new node(identifier, key);
	//initialized minimum
	if (min != nullptr)
	{
		//relink new node before the current minimum
		min->previous->next = new_node;
		new_node->next = min;
		new_node->previous = min->previous;
		min->previous = new_node;
		//swap if min is bigger than new node
		min = (new_node->key < min->key) ? new_node : min;
	}
	//create first minimum
	else
		min = new_node;
	//dev
	traverse();
}


void common_heap::delete_min()
{
	std::cout << "Min is " << "(" << min->key << "," << min->identifier << ")" << std::endl;
}

void common_heap::decrease(int identifier, int key)
{
	std::cout << "I am decreasing" << std::endl;
}

void fibonacci_heap::common_heap::traverse()
{
	node * copy = min;
	if (copy != nullptr) {
		do {
			std::cout << "(" << copy->key << "," << copy->identifier << ")";
			copy = copy->next;
			if (copy != min) {
				std::cout << "-->";
			}
		} while (copy != min && copy->next != nullptr);
		std::cout << std::endl;
	}
}
