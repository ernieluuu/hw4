#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int getHeight(Node* root);

bool equalPaths(Node * root)
{
    // Add your code below

	/*
	
	find leaves (left, right) -- left + right are both nullptr
	recurse up
	update count
	parent compares its left and right
	if false then it is all false

	alternative:
	can do a get height and then recurse down and do get height until reaching
	leaf nodes

	alternative 2:
	- go to the bottom first
	then call getHeight()
	- then it will pop into the parent node
	call getHeight()
	compare
	until you either break or reach the root

	*/

	// base case (leaf node)
	if (root->left == nullptr && root->right == nullptr)
	{
		return true;
	}

	// if get height == return true

	if (getHeight(root->left) == getHeight(root->right))
	{
		return true;
	}
	else
	{
		return false;
	}

	//return equalPaths(root->right) && equalPaths(root->left);

	/*
	
	can be parent
	can have only a left child / only a right child
	(if one of them is nullptr and the other one isn't)
	can be a leaf node
	
	*/

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
