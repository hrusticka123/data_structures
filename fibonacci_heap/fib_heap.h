#pragma once
#include "fib_heap_common.h"

namespace fibonacci_heap
{
	class heap : public common_heap 
	{
		public:
			heap(size_t elements) : common_heap( elements) {};
			virtual void decrease(int identifier, int key);
	};
}