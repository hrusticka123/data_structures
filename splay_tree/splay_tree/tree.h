#pragma once
#include "stack.h"

namespace splay_tree {
	class node
	{
	public:
		~node();
		size_t index;
		node(size_t index) : index(index) {};
		node * left_node = nullptr;
		node * right_node = nullptr;
	};

	class tree
	{
	public:
		virtual void insert(size_t index);
		void find(size_t index);
		virtual double get_average_path_length();
		node * root = nullptr;
		~tree();
	protected:
		node * left_rotation(node * current);
		node * right_rotation(node * current);
		virtual void splay(size_t index) = 0;
		stack<size_t> path_lengths;
	};
}