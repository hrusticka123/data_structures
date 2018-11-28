#pragma once
#include "../tree.h"

enum direction { L, R };

namespace splay_tree {
	class naive_tree : public tree
	{
	protected:
		virtual void splay(size_t index) override;
	private:
		node * rotate_by_dir(node * current, direction dir);
	};
}