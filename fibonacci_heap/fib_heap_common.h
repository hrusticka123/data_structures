#pragma once

namespace fibonacci_heap
{
	struct node
	{
		//node() : parent(nullptr), child(nullptr) { next = previous = this; }
		//node(int identifier) : identifier(identifier), parent(nullptr), child(nullptr), key(0) { next = previous = this;  }
		node(int identifier, int key) : identifier(identifier), key(key), parent(nullptr), child(nullptr) { next = previous = this; }
		node * parent;
		node * child;
		node * next;
		node * previous;
		int identifier;
		int key = 0;
		bool marked = false;
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
		common_heap() { min = nullptr; }
		void insert(int identifier, int key);
		void delete_min();
		void decrease(int identifier, int key);
		~common_heap() { delete min; }
	protected:
		node * min;
		void traverse();
	};
}
