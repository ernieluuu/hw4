#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
	// AVLNode<Key, Value>* findAVLNode(const Key& k) const; // static cast it instead
	void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n); // where p is the parent of n
	void removeFix(AVLNode<Key, Value>* n, int8_t diff);

	/*rotate function will determine isZigZig or isZigZag, and then perform rotations accordingly.*/
	void rotate(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom);
	void rotateRight(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom);
	void rotateLeft(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
	// if empty tree
	if (this->root_ == nullptr)
	{
		this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
		return;
	}

	// call the old insert function (scoped using ::)
	this->BinarySearchTree<Key, Value>::insert(new_item); // this returns a BST node instead of an AVL node
														  // so we must static_cast it to an AVL node later.

	AVLNode<Key, Value>* new_node = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));

	if (new_node == nullptr)
	{
		std::cout << "Error: could not find the inserted node." << std::endl;
		return;
	}

	if (new_node->getParent()->getBalance() != 0)
	{
		new_node->getParent()->setBalance(0);
		return;
	}
	else
	{
		// set parent's balance
		// if it was left, -1
		// if it was right, +1
		// (stay consistent, I chose to think of it like a numberline: left = negative)
		if (new_node == new_node->getParent()->getLeft())
		{
			new_node->getParent()->setBalance(-1);
		}
		else 
		{
			new_node->getParent()->setBalance(1);
		}
	}
	insertFix(new_node->getParent(), new_node);

	return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
/*
else, propogate the updating of height all the way up to the root node
you should be able to calculate this ( + or - ) based on if it is a
left or right child
e.g. I can determine that left child is always +1 whereas right child
is always -1 on the overarching score.

insertFix, you keep recursing until the parent's updated balance is either 0
(when your height change doesn't affect them anymore)
or when it is +-2
in that case you call the rotations.
--> insertFix: recurse until you rotate or hit an updated '0'
*/

	// update p->parent's balance by -1 (if parent was a left child)
	// and +1 in the other case
	// if falls out of range, rotate.
	// return

	// when p is the root node
	if (p->getParent() == nullptr)
	{
		return;
	}

	int8_t g_balance = p->getParent()->getBalance(); // grandparent's balance

	// p is a left child
	if (p->getParent()->getLeft() == p)
	{
		// case 1: adding one to the left height balances the tree
		if (g_balance == 1)
		{
			p->getParent()->setBalance(0);
			return;
		}
		// case 2: keep propogating the height change, recurse on p and the parent of p
		else if (g_balance == 0)
		{
			p->getParent()->setBalance(-1);
			insertFix(p->getParent(), p);
		}
		// case 3: found the inbalance, now we rotate
		else if (g_balance == -1)
		{
			p->getParent()->setBalance(-2); // set new balance, rotations will correct this to 0
			rotate(p, p->getParent(), n);
		}
	}
	// p is a right child
	else
	{
		if (g_balance == -1)
		{
			p->getParent()->setBalance(0);
			return;
		}
		else if (g_balance == 0)
		{
			p->getParent()->setBalance(1);
		}
		else if (g_balance == 1)
		{
			p->getParent()->setBalance(2);
			rotate(p, p->getParent(), n);
		}
	}

	return;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	if (this->root_ == nullptr)
	{
		return;
	}

	AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

	// node could not be found
	if (curr == nullptr)
	{
		return;
	}

	// has 2 children
	// swap with predecessor + continue with remove on the curr node (in it's new location)
	if (curr->getLeft() != nullptr && curr->getRight() != nullptr)
	{
		AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr));
		nodeSwap(curr, pred);
	}

	// has 0 children
	if (curr->getLeft() == nullptr && curr->getRight() == nullptr)
	{
		if (curr == this->root_)
		{
			delete curr;
			this->root_ = nullptr;
		}
		else if (curr == curr->getParent()->getLeft())
		{ // is a left child
			curr->getParent()->setLeft(nullptr);
			removeFix(curr->getParent(), 1);
		}
		else
		{ // is a right child
			curr->getParent()->setRight(nullptr);
			removeFix(curr->getParent(), -1);
		}
	}
	// has a left child only
	else if (curr->getLeft() != nullptr && curr->getRight() == nullptr)
	{
		if (curr == this->root_)
		{
			this->root_ = curr->getLeft();
			this->root_->setParent(nullptr);
		}
		else if (curr == curr->getParent()->getLeft())
		{ // curr is a left child
			curr->getLeft()->setParent(curr->getParent());
			curr->getParent()->setLeft(curr->getLeft());
			removeFix(curr->getParent(), 1);
		}
		else
		{ // curr is a right child
			curr->getLeft()->setParent(curr->getParent());
			curr->getParent()->setRight(curr->getLeft());
			removeFix(curr->getParent(), -1);
		}
	}
	// has a right child only
	else if (curr->getLeft() == nullptr && curr->getRight() != nullptr)
	{
		if (curr == this->root_)
		{
			this->root_ = curr->getRight();
			this->root_->setParent(nullptr);
		}
		else if (curr == curr->getParent()->getLeft())
		{ // curr is a left child
			curr->getRight()->setParent(curr->getParent());
			curr->getParent()->setLeft(curr->getRight());
			removeFix(curr->getParent(), 1);
		}
		else
		{
			curr->getRight()->setParent(curr->getParent());
			curr->getParent()->setRight(curr->getRight());
			removeFix(curr->getParent(), -1);
		}
	}
	delete curr;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff)
{
	if (n == nullptr)
	{
		return;
	}

	// compute next recursive call
	AVLNode<Key, Value>* p = n->getParent();
	int8_t ndiff;
	// if p != nullptr
	if (n == p->getLeft())
	{
		ndiff = 1;
	}
	else
	{
		ndiff = -1;
	}

	/*left child is taller*/
	// Case 1
	if (n->getBalance() + diff == -2)
	{
		AVLNode<Key, Value>* c = n->getLeft(); // the taller of the children
		// 1a.
		if (c->getBalance() == -1)
		{ // zig-zig
			rotateRight(c, n, c->getLeft());
			n->setBalance(0);
			c->setBalance(0);
			removeFix(c->getParent(), ndiff);
		}
		// 1b. 
		else if (c->getBalance() == 0)
		{ // also zig-zig
			rotateRight(c, n, c->getLeft());
			n->setBalance(-1);
			c->setBalance(1);
			return;
		}
		// 1c. 
		else if (c->getBalance() == 1)
		{ // zig-zag
			AVLNode<Key, Value>* g = c->getRight(); // right child of c
			int8_t g_prev_bal = g->getBalance();
			rotateLeft(g, c, g->getRight());
			rotateRight(g, n, c);
			if (g_prev_bal == 1)
			{
				n->setBalance(0); // slides say '0' but i think it might be -1, draw it out
				c->setBalance(-1);
				g->setBalance(0);
			}
			else if (g_prev_bal == 0)
			{
				n->setBalance(0);
				c->setBalance(0);
				g->setBalance(0);
			}
			else if (g_prev_bal == -1)
			{
				n->setBalance(1);
				c->setBalance(0);
				g->setBalance(0);
			}
			// g is the top node now
			removeFix(g->getParent(), ndiff);
		}
	}
	// Case 2
	else if (n->getBalance() + diff == -1)
	{
		n->setBalance(-1);
		return;
	}
	// Case 3
	else if (n->getBalance() + diff == 0)
	{
		removeFix(n->getParent(), ndiff);
	}
	/*right child is taller*/
	else if (n->getBalance() + diff == 1)
	{
		n->setBalance(1);
		return;
	}
	else if (n->getBalance() + diff == 2)
	{
		AVLNode<Key, Value>* c = n->getRight(); // the taller of the children
		// a. zig-zig
		if (c->getBalance() == 1)
		{
			rotateLeft(c, n, c->getRight());
			n->setBalance(0);
			c->setBalance(0);
			removeFix(c->getParent(), ndiff);
		}
		// b. zig-zig
		else if (c->getBalance() == 0)
		{
			rotateLeft(c, n, c->getRight());
			n->setBalance(1);
			c->setBalance(-1);
			return;
		}
		// c. zig-zag
		else if (c->getBalance() == -1)
		{
			AVLNode<Key, Value>* g = c->getLeft(); // grandchild of n
			int8_t g_prev_bal = g->getBalance();
			rotateRight(g, c, g->getLeft());
			rotateLeft(g, n, c);
			if (g_prev_bal == 1)
			{
				n->setBalance(0);
				c->setBalance(1);
				g->setBalance(0);
			}
			else if (g_prev_bal == 0)
			{
				n->setBalance(0);
				c->setBalance(0);
				g->setBalance(0);
			}
			else if (g_prev_bal == -1)
			{
				n->setBalance(-1);
				c->setBalance(0);
				g->setBalance(0);
			}
			// g is top node now
			removeFix(g->getParent(), ndiff);
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotate(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom)
{
	// case 1: zig-zig
	// right rotation (left children)
	if (bottom == middle->getLeft() && middle == top->getLeft())
	{
		rotateRight(middle, top, bottom);
	}
	// left rotation (right children)
	else if (bottom == middle->getRight() && middle == top->getRight())
	{
		rotateLeft(middle, top, bottom);
	}
	// case 2: zig-zag
	else if (bottom == middle->getRight() && middle == top->getLeft())
	{
		rotateLeft(bottom, middle, bottom->getRight()); // FIXME: these lines are error prone, make sure it's the right way
		rotateRight(bottom, top, middle); // after the first rotation, middle becomes bottom, bottom becomes middle
	}
	else if (bottom == middle->getLeft() && middle == top->getRight())
	{
		rotateRight(bottom, middle, bottom->getLeft());
		rotateLeft(bottom, top, middle);
	}

	// TODO: check if any of them are nullptr (so you don't dereference them in below functions)?
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom)
{
	// ptrs:
	// bottom keeps the same ptrs
	// middle's left doesn't change (bottom), right becomes top
	// top's left becomes middle's old right
	// top's right remains the same
	AVLNode<Key, Value>* mid_old_right = middle->getRight();
	middle->setRight(top);
	top->setLeft(mid_old_right);

	// parents:
	// middle's parent becomes top's parent
	// top's parent becomes middle
	// change mid_old_right's parent to top
	middle->setParent(top->getParent());
	top->setParent(middle);
	mid_old_right->setParent(top);

	// balances:
	int8_t new_top_balance = top->getBalance() + 2;
	int8_t new_mid_balance = middle->getBalance() + 1;
	top->setBalance(new_top_balance);
	middle->setBalance(new_mid_balance);

	return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* middle, AVLNode<Key, Value>* top, AVLNode<Key, Value>* bottom)
{
	// ptrs:
	// top's right becomes middle's original left
	// middle's left becomes top
	AVLNode<Key, Value>* mid_old_left = middle->getLeft();
	middle->setLeft(top);
	top->setRight(mid_old_left);

	// parents:
	// middle's parent becomes top's old parent
	// top's parent becomes middle
	// mid_old_left's parent becomes top
	middle->setParent(top->getParent());
	top->setParent(middle);
	mid_old_left->setParent(top);

	// balances:
	int8_t new_top_balance = top->getBalance() - 2;
	int8_t new_mid_balance = middle->getBalance() - 1;
	top->setBalance(new_top_balance);
	middle->setBalance(new_mid_balance);

	return;
}


#endif
