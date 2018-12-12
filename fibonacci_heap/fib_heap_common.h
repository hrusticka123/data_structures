#pragma once

namespace fibonacci_heap
{
	struct node
	{
		node * parent;
		node * child;
		node * next;
		node * previous;
	};

	class common_heap
	{
	public:
		void reset();
		void insert(int identifier, int key);
		void delete_min();
		void decrease(int identifier, int key);
	protected:
		node * h;
	};
}
