#include "helper.h"
#include "naive_tree/naive_tree.h"
#include "full_tree/full_tree.h"
#include "optimal_tree/optimal_tree.h"
#include <string>
#include <iostream>

void helper::create_tree()
{
	if (type == "full")
	{
		tree = new splay_tree::full_tree;
	}
	else if (type == "naive")
	{
		tree = new splay_tree::naive_tree;
	}
	else if (type == "optimal")
	{
		tree = new splay_tree::optimal_tree;
	}
}

helper::helper(int argc, char ** argv)
{
	if (argc == 3)
	{
		type = argv[1];
		try
		{
			std::ifstream * temp = new std::ifstream;
			temp->open(argv[2]);
			input = temp;
		}
		catch (...)
		{
			std::cout << "Incorrect input file" << std::endl;
		}
	}
	else
	{
		std::getline(std::cin, type);
		input = &std::cin;
	}
}

void helper::pre_order(splay_tree::node * n, size_t depth)
{
	if (n != nullptr)
	{
		std::cout << std::string(depth,'-') << n->index << std::endl;
		pre_order(n->left_node,++depth);
		pre_order(n->right_node,depth);
	}
	else
	{
		std::cout << std::string(depth, '-') << 0 << std::endl;
	}
}

void helper::process()
{
	char command;
	size_t index;
	while (!input->eof())
	{
		*input >> command;
		*input >> index;
		if (command == 'I')
		{
			tree->insert(index);
		}
		else if (command == 'F')
		{
			tree->find(index);
		}
		else if (command == '#')
		{
			if (tree)
			{
				std::cout << subset_size << "\t" << tree->get_average_path_length() << std::endl;
				delete tree;
			}
			subset_size = index;
			create_tree();
		}
	}
	if (tree)
	{
		std::cout << subset_size << "\t" << tree->get_average_path_length() << std::endl;
		delete tree;
	}
}
