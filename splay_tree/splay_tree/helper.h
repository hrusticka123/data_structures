#pragma once

#include <fstream>
#include "tree.h"

class helper
{
public:
	helper(int argc, char ** argv);
	void process();
	splay_tree::tree * tree = nullptr;
	std::istream * input = nullptr;
	std::string type = "";
private:
	void pre_order(splay_tree::node * n,size_t depth);
	void create_tree();
	size_t subset_size;
};