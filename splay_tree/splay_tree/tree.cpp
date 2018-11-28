#include "tree.h"

using namespace splay_tree;

node::~node()
{
	if (left_node) delete left_node;
	if (right_node) delete right_node;
}

void splay_tree::tree::insert(size_t index)
{
	if (root == nullptr)
	{
		root = new node(index);
	}
	else
	{
		node ** travers = &root;
		while (true)
		{
			if (*travers == nullptr)
			{
				*travers = new node(index);
				break;
			}
			if ((*travers)->index == index)
			{
				break;
			}
			else if ((*travers)->index < index)
			{
				travers = &(*travers)->right_node;
			}
			else
			{
				travers = &(*travers)->left_node;
			}
		}
		splay(index);
	}
}

void splay_tree::tree::find(size_t index)
{
	splay(index);
}

double splay_tree::tree::get_average_path_length()
{
	size_t size = path_lengths.size();
	if (size == 0)
		return 0;
	double result = 0;
	while (path_lengths.size() > 0)
	{
		result += path_lengths.pop_back();
	}
	return result / size;
}

tree::~tree()
{
	stack<node *> stack;
	stack.push_back(root);
	while (stack.size() != 0)
	{
		node * current = stack.pop_back();
		if (current == nullptr)
		{
			continue;
		}
		if (current->left_node != nullptr)
		{
			stack.push_back(current->left_node);
			current->left_node = nullptr;
		}
		else if (current->right_node != nullptr)
		{
			stack.push_back(current->right_node);
			current->right_node = nullptr;
		}
		else
		{
			delete current;
		}
	}
	root = nullptr;
}

node * splay_tree::tree::left_rotation(node * current)
{
	node * to_return = current->right_node;
	if (current->right_node == nullptr) return current;
	current->right_node = to_return->left_node;
	to_return->left_node = current;
	return to_return;
}

node * splay_tree::tree::right_rotation(node * current)
{
	node * to_return = current->left_node;
	if (current->left_node == nullptr) return current;
	current->left_node = to_return->right_node;
	to_return->right_node = current;
	return to_return;
}
