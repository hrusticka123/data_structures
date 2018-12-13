#include "fib_heap_common.h"
#include <iostream>
#include <string>

using namespace fibonacci_heap;


void common_heap::insert(int identifier, int key)
{
	node * new_node = new node(identifier, key);
	min = merge(min, new_node);
	//dev
	traverse();
}


void common_heap::delete_min()
{
	std::cout << "Min is " << "(" << min->key << "," << min->identifier << ")" << std::endl;
}

void common_heap::decrease(int identifier, int key)
{
	auto node = find(min, identifier);
	if (node != nullptr)
	{
		//std::cout << "Old key: " << node->key << ", New key: " << key << std::endl;
		if (node->key < key)
			return;
		node->key = key;
		if (node->parent == nullptr || node->key < node->parent->key)
		{
			min = cut(min, node);
			auto parent = node->parent;
			node->parent = nullptr;
			while (parent != nullptr && parent->marked)
			{
				min = cut(min, parent);
				node = parent;
				parent = node->parent;
				node->parent = nullptr;
			}
			if (parent != nullptr && parent->parent != nullptr)
				parent->marked = true;
		}
	}
	//dev
	traverse();
}

node * common_heap::find(node * heap, int identifier)
{
	auto node = heap;
	if (node == nullptr)
		return nullptr;

	do {
		if (node->identifier == identifier)
			return node;
		auto to_ret = find(node->child, identifier);
		if (to_ret != nullptr)
			return to_ret;
		node = node->next;
	} while (node != heap);

	return nullptr;
}

void common_heap::reset()
{
	clear(min);
}

void common_heap::clear(node * heap)
{
	if (heap != nullptr)
	{
		auto current = heap;
		do 
		{
			auto temp = current;
			current = current->next;
			clear(temp->child);
			delete temp;
		} while (current != heap);
	}
}

void common_heap::traverse()
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

node * common_heap::cut(node * heap, node * node)
{
	if (node->next == node && node->parent != nullptr)
		node->parent->child = nullptr;
	else
	{
		node->next->previous = node->previous;
		node->previous->next = node->next;
		if (node->parent != nullptr)
			node->parent->child = node->next;
	}
	node->next = node->previous = node;
	node->marked = false;
	return merge(heap, node);
}

node * common_heap::merge(node * first, node * second)
{
	if (first == nullptr) return second;
	if (second == nullptr) return first;

	//relink new node before the current minimum
	first->previous->next = second;
	second->next = first;
	second->previous = first->previous;
	first->previous = second;
	//swap if first is bigger than new node
	first = (second->key < first->key) ? second : first;

	return first;
}
