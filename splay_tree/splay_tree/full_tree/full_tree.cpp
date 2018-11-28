#include "full_tree.h"

using namespace splay_tree;

void full_tree::splay(size_t index)
{
	node * temp_root = new node(index);
	node * temp_left = temp_root;
	node * temp_right = temp_root;

	size_t path_length = 0;
	while (true) {
		path_length++;
		if (index < root->index) {
			if (root->left_node == nullptr) break;
			if (index < root->left_node->index) {
				root = right_rotation(root);
				if (root->left_node == nullptr) break;
			}
			temp_right->left_node = root;        
			temp_right = root;
			root = root->left_node;
		} 
		else if (index > root->index) 
		{
			if (root->right_node == nullptr) break;
			if (index > root->right_node->index) {
				root = left_rotation(root);
				if (root->right_node == nullptr) break;
			}
			temp_left->right_node = root;   
			temp_left = root;
			root = root->right_node;
		}
		else {
			break;
		}
	}
	temp_left->right_node = root->left_node;
	temp_right->left_node = root->right_node;
	root->left_node = temp_root->right_node;
	root->right_node = temp_root->left_node;
	path_lengths.push_back(path_length);
}
