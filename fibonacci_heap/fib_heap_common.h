#pragma once

namespace fibonacci_heap
{
	struct node
	{
		node * parent;
		node * child;
		node * next;
		node * previous;
		int identifier;
		~node() { 
			delete parent; parent = nullptr;
			delete child; child = nullptr;
			delete next; next = nullptr;
			delete previous; previous = nullptr;
		}
	};

	class common_heap
	{
	public:
		common_heap() { h = new node(); }
		void insert(int identifier, int key);
		void delete_min();
		void decrease(int identifier, int key);
		~common_heap() { delete h; }
	protected:
		node * h;
	};
}
