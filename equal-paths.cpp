#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int getHeight(Node* root);

bool checkLeafLevels(Node* curr_node, int level, int& leaf_level);

bool equalPaths(Node * root)
{
    // Add your code below

	int level = 1;
	int leaf_level = 0; /*starts off uninitialized*/

	return checkLeafLevels(root, level, leaf_level);
}

int getHeight(Node* root)
{
	// base case
	if (root == nullptr) {
		return 0;
	}

	// recursive step
	int left_height = getHeight(root->left);
	// std::cout << root->key << "; ";
	int right_height = getHeight(root->right);

	if (left_height > right_height) {
		return 1 + left_height;
	}
	else {
		return 1 + right_height;
	}
}

bool checkLeafLevels(Node* curr_node, int curr_level, int& leaf_level)
{


	// base case

	if (curr_node == nullptr)
	{
		return true;
	}

	if (curr_node->left == nullptr && curr_node->right == nullptr)
	{
		if (leaf_level == 0)
		{
			leaf_level = curr_level;
			return true;
		}
		else if (curr_level == leaf_level)
		{
			return true;
		}
		else if (curr_level != leaf_level)
		{
			return false;
		}
	}

	// recursive step
	return checkLeafLevels(curr_node->left, curr_level+1, leaf_level) && 
		   checkLeafLevels(curr_node->right, curr_level+1, leaf_level);
}
