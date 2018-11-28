#pragma once
#include "../tree.h"

namespace splay_tree {
	class full_tree : public tree
	{
	protected:
		virtual void splay(size_t index) override;
	};
}