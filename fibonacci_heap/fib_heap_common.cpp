#include "fib_heap_common.h"
#include <iostream>
#include <string>

using namespace fibonacci_heap;


void common_heap::insert(int identifier, int key)
{
	node * new_node = new node(identifier, key);
	min = merge(min, new_node);
	//dev
	traverse(min);
}


void common_heap::delete_min()
{
	std::cout << "Min is " << "(" << min->key << "," << min->identifier << ")" << std::endl;
	auto node = min;
	separate(node->child);
	if (node->next == node)
		node = node->child;
	else
	{
		node->next->previous = node->previous;
		node->previous->next = node->next;
		node = merge(node->next, node->child);
	}

	if (node != nullptr)
	{
		fibonacci_heap::node * heaps[100];
		std::fill_n(heaps, 100, nullptr);

		while (true)
		{
			if (heaps[node->degree] != nullptr)
			{
				auto heap = heaps[node->degree];
				if (heap == node)
					break;
				heaps[node->degree] = nullptr;
				if (node->key < heap->key)
				{
					heap->previous->next = heap->next;
					heap->next->previous = heap->previous;
					add(node, heap);
				}
				else
				{
					heap->previous->next = heap->next;
					heap->next->previous = heap->previous;
					if (node->next == node)
					{
						heap->next = heap->previous = heap;
						add(heap, node);
						node = heap;
					}
					else
					{
						node->previous->next = heap;
						node->next->previous = heap;
						heap->next = node->next;
						heap->previous = node->previous;
						add(heap, node);
						node = heap;
					}
				}
				continue;
			}
			else
				heaps[node->degree] = node;
			node = node->next;
		}

		auto temp = node;
		auto new_min = node;
		do
		{
			if (temp->key < new_min->key)
				new_min = temp;
			temp = temp->next;
		} while (temp != node);
		auto old_min = min;
		delete old_min;
		min = new_min;
	}
	traverse(min);
}

void common_heap::decrease(int identifier, int key)
{
	auto node = find(min, identifier);
	if (node != nullptr)
	{
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
	traverse(min);
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

void fibonacci_heap::common_heap::separate(node * node)
{
	if (node != nullptr)
	{
		auto temp = node;
		do {
			temp->marked = false;
			temp->parent = nullptr;
			temp = temp->next;
		} while (temp != node);
	}
}

void fibonacci_heap::common_heap::add(node * parent, node * child)
{
	child->previous = child->next = child;
	child->parent = parent;
	parent->degree++;
	parent->child = merge(parent->child, child);
}

void common_heap::traverse(node * n)
{
	node * copy = n;
	if (copy != nullptr) {
		do {
			std::cout << "(" << copy->key << "," << copy->identifier << ")";
			std::cout << "[";
			traverse(copy->child);
			std::cout << "]";
			copy = copy->next;
			if (copy != n) {
				std::cout << "-->";
			}
		} while (copy != n && copy->next != nullptr);
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
