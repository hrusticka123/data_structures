#include "fib_heap_common.h"
#include <iostream>

using namespace fibonacci_heap;


void fibonacci_heap::common_heap::insert(int identifier, int key)
{
	std::cout << "I am inserting" << std::endl;
}

void fibonacci_heap::common_heap::delete_min()
{
	std::cout << "I am deleting" << std::endl;
}

void fibonacci_heap::common_heap::decrease(int identifier, int key)
{
	std::cout << "I am decreasing" << std::endl;
}
