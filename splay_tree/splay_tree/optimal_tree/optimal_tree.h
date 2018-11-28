#pragma once
#include "../tree.h"
#include "../stack.h"
#include <vector>


namespace splay_tree {
	class optimal_tree : public tree
	{
	public:
		virtual double get_average_path_length() override;
	protected:
		virtual void splay(size_t index) override;
		virtual void insert(size_t index) override;
	private:
		std::vector<size_t> frequencies;
	};
}