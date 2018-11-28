#include "naive_tree.h"
#include "../stack.h"

using namespace splay_tree;

node * naive_tree::rotate_by_dir(node * current, direction dir)
{
	if (dir == L)
	{
		return right_rotation(current);
	}
	else
	{
		return left_rotation(current);
	}
}

void splay_tree::naive_tree::splay(size_t index)
{
	size_t path_length = 0;
	if (root->index != index)
	{
		stack<direction> directions;
		stack<node *> stack;
		stack.push_back(root);
		while (true)
		{
			node * current = stack.back();
			if (current->left_node != nullptr && current->index > index)
			{
				stack.push_back(current->left_node);
				directions.push_back(L);
			}
			else if (current->right_node != nullptr && current->index < index)
			{
				stack.push_back(current->right_node);
				directions.push_back(R);
			}
			else
			{
				break;
			}
		}
		path_length = stack.size();
		if (stack.size() < 2)
		{
			return;
		}
		stack.pop_back();
		node * new_root = stack.pop_back();
		direction current_dir;
		node * temp = nullptr;
		while (true)
		{
			current_dir = directions.pop_back();
			new_root = rotate_by_dir(new_root, current_dir);
			if (stack.size() > 0)
			{
				temp = stack.pop_back();
				if (directions.back() == R)
				{
					temp->right_node = new_root;
				}
				else
				{
					temp->left_node = new_root;
				}
				new_root = temp;
			}
			if (stack.size() == 0)
			{
				current_dir = directions.pop_back();
				new_root = rotate_by_dir(new_root, current_dir);
				break;
			}
		};
		root = new_root;
	}
	path_lengths.push_back(path_length);
}