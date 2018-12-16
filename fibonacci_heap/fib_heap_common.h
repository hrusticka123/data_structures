#pragma once
#define DEV false
#define DEGREES 64
#define ELEMENTS 4096
#include <algorithm>

namespace fibonacci_heap
{
	/* one node in heap
	* has pointers to his next, previous, parent and child
	* has information about its degree, key, identifier and mark
	*/
	struct node
	{
		node(int identifier, int key) : identifier(identifier), key(key), parent(nullptr), child(nullptr) { next = previous = this; }
		node * parent;
		node * child;
		node * next;
		node * previous;
		int identifier;
		int key = 0;
		int degree = 0;
		bool mark = false;
	};

	//helper structure for non recursive deallocation
	class stack
	{
	public:
		stack() : size(ELEMENTS), top(-1) { arr = new node*[ELEMENTS]; };
		~stack() { delete[] arr; }
		void push_back(node * node);
		node * pop_back();
		bool empty();
	private:
		node ** arr;
		size_t size;
		int top;
	};

	//helper structure for dynamic array
	class dyn_array
	{
	public:
		dyn_array() : size(DEGREES) { arr = new node*[DEGREES]; std::fill_n(arr, DEGREES, nullptr);}
		node * & operator[](size_t pos);
		~dyn_array() { delete[] arr; }
	private:
		node ** arr;
		size_t size;
	};

	/* common structure for both kinds of fibonacci heaps
	* implements most of the functionalities itself, except for decrease
	*/
	class common_heap
	{
	public:
		common_heap(size_t elements) { min = nullptr; delete_min_steps = 0; decrease_steps = 0; map = new node * [elements]; std::fill_n(map, elements, nullptr); }
		//insert new node with given identifier and key(priority)
		//duplicates are possible
		void insert(int identifier, int key);
		//remove minimum from heap
		void delete_min();
		//decrease node with given identifier to given key value
		//giving key value greater or equal to node's current has no effect
		//giving non-existing identifier has no effect
		virtual void decrease(int identifier, int key) = 0;
		~common_heap() { clear(); delete[] map; }
		size_t delete_min_steps;
		size_t decrease_steps;
	protected:
		node * min;
		//for dev purpose, traverses and outputs heap
		void traverse(node * n);
		//cuts node from heap
		node * cut(node * heap, node * node);
		//connects 2 heaps
		node * connect(node * first, node * second);
		//deallocate heap
		void clear();
		//unlinks parents' children
		void separate(node * parent);
		//adds new child to parents
		void add(node * parent, node* child);
		//removes node from list
		void remove_links(node * & node);
		bool prepare(node * & node);
		void set_new_min(node * node);
		//map of identifiers to nodes, for faster search
		node ** map;
	};
}