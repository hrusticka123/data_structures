#include "fib_heap_common.h"
#include <iostream>

using namespace fibonacci_heap;

void common_heap::insert(int identifier, int key)
{
	//create new single node and connect it to min
	node * new_node = new node(identifier, key);
	min = connect(min, new_node);
	//insert node to map
	map[identifier] = new_node;
	//dev
	if (DEV) 
	{
		traverse(min); 
		std::cout << std::endl;
	}
}

void common_heap::delete_min()
{
	if (min == nullptr)
		return;
	//dev
	if (DEV) std::cout << "Min is " << "(" << min->identifier << "," << min->key << ")" << std::endl;
	//temp node
	auto node = min;

	//remove node's children references to its parent
	separate(node);

	//check if the node is able to be processed
	if (!prepare(node))
		return;

	dyn_array degrees;
	while (true)
	{
		//there is no node of current degree yet, add it and go to next
		if (degrees[node->degree] == nullptr)
		{
			degrees[node->degree] = node;
			node = node->next;
		}
		//we have such node
		else
		{
			auto current = degrees[node->degree];
			//finding original node in the degrees array ends the cycle
			if (current == node)
				break;
			degrees[node->degree] = nullptr;
			
			remove_links(current);
			//if current has greater key, add it as node's child
			if (node->key < current->key)
				add(node, current);
			else
			{
				//last in its layer
				if (node->next == node)
					//make current the only one in its layer
					current->next = current->previous = current;
				else
				{
					//link node with current
					node->previous->next = node->next->previous = current;
					current->previous = node->previous;
					current->next = node->next;
				}
				add(current, node);
				node = current;
			}
			delete_min_steps++;
		}
	}
	set_new_min(node);

	//dev
	if (DEV)
	{
		traverse(min);
		std::cout << std::endl;
	}
}

void common_heap::clear()
{
	//using stack instead of recursive deallocation to avoid stack overflow
	stack s;
	s.push_back(min);
	while (!s.empty())
	{
		auto heap = s.pop_back();
		auto current = heap;
		do
		{
			auto temp = current;
			current = current->next;
			if (temp->child != nullptr)
				s.push_back(temp->child);
			delete temp;
		} while (current != heap);
	}
	
	min = nullptr;
}

void common_heap::separate(node * parent)
{
	//take parents first child
	auto child = parent->child;
	if (child != nullptr)
	{
		auto temp = child;
		//unmark and unlink all its children
		do {
			temp->mark = false;
			temp->parent = nullptr;
			temp = temp->next;
		} while (temp != child);
	}
}

void common_heap::add(node * parent, node * child)
{
	child->previous = child->next = child;
	child->parent = parent;
	parent->degree++;
	parent->child = connect(parent->child, child);
}

void common_heap::remove_links(node * & node)
{
	node->next->previous = node->previous;
	node->previous->next = node->next;
}

bool common_heap::prepare(node *& node)
{
	//single node in layer
	if (node->next == node)
	{
		node = node->child;
		//if there is no child, heap is singleton, reset whole heap
		if (node == nullptr)
		{
			clear();
			return false;
		}
	}
	// multiple nodes in layer, remove its links and connect its next to child
	else
	{
		remove_links(node);
		node = connect(node->next, node->child);
	}
	return true;
}

void common_heap::set_new_min(node * node)
{
	//looking for new minimum
	//swap if lesser until last in node's layer
	auto temp = node;
	auto new_min = node;
	do
	{
		if (temp->key < new_min->key)
			new_min = temp;
		temp = temp->next;
	} while (temp != node);
	//set new minimum
	map[min->identifier] = nullptr;
	delete min;
	min = new_min;
}

//WARNING - recursive implementation
//this might end in stack overflow on deep heaps
void common_heap::traverse(node * n)
{
	node * copy = n;
	if (copy != nullptr) {
		do {
			std::cout << "(" << copy->identifier << "," << copy->key << ")";
			std::cout << "[";
			traverse(copy->child);
			std::cout << "]";
			copy = copy->next;
			if (copy != n) {
				std::cout << "-->";
			}
		} while (copy != n && copy->next != nullptr);
	}
}

node * common_heap::cut(node * heap, node * node)
{
	//node is the last in layer and has a parent
	if (node->next == node && node->parent != nullptr)
	{
		node->parent->child = nullptr;
		node->parent->degree--;
	}
	else
	{
		remove_links(node);
		//there is still parent, set its child to the next one
		if (node->parent != nullptr)
		{
			node->parent->degree--;
			node->parent->child = node->next;
		}
	}
	//make single node in layer and unmark
	node->next = node->previous = node;
	node->mark = false;
	return connect(heap, node);
}

node * common_heap::connect(node * first, node * second)
{
	//check either
	if (first == nullptr) return second;
	if (second == nullptr) return first;

	//swap if second is smaller
	if (first->key > second->key) {
		auto temp = first;
		first = second;
		second = temp;
	}

	//link them
	auto first_next = first->next;
	auto second_previous = second->previous;
	first->next = second;
	second->previous = first;

	first_next->previous = second_previous;
	second_previous->next = first_next;

	return first;
}

node * & dyn_array::operator[](size_t pos)
{
	if (pos >= size)
	{
		size_t new_size = size;
		while (pos >= new_size)
			new_size *= 2;
		auto new_arr = new node*[new_size];
		std::fill_n(new_arr + size, new_size - size, nullptr);
		delete[] arr;
		arr = new_arr;
		size = new_size;
	}
	return arr[pos];
}

void fibonacci_heap::stack::push_back(node * node)
{
	if (++top >= size)
	{
		auto new_arr = new fibonacci_heap::node * [size * 2];
		memcpy(new_arr, arr, size * sizeof(fibonacci_heap::node*));
		delete[] arr;
		arr = new_arr;
		size *= 2;
	}
	arr[top] = node;
}

node * fibonacci_heap::stack::pop_back()
{
	if (top - 1 >= -1)
		return arr[top--];
	return nullptr;
}

bool fibonacci_heap::stack::empty()
{
	return top == -1;
}
