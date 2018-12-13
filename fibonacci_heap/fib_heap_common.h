#pragma once

namespace fibonacci_heap
{
	struct node
	{
		node(int identifier, int key) : identifier(identifier), key(key), parent(nullptr), child(nullptr) { next = previous = this; }
		node * parent;
		node * child;
		node * next;
		node * previous;
		int identifier;
		int key = 0;
		bool marked = false;
	};

	class common_heap
	{
	public:
		common_heap() { min = nullptr; }
		void insert(int identifier, int key);
		void delete_min();
		void decrease(int identifier, int key);
		node * find(node * heap, int identifier);
		void reset();
		~common_heap() { clear(min); }
	protected:
		node * min;
		void traverse();
		node * cut(node * heap, node * node);
		node * merge(node * first, node * second);
		void clear(node * heap);
	};
}
