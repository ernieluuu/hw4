#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);

	// my added functions
	Node<Key, Value>* readRoot() { return root_; }
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
	void clearBinaryTree(Node<Key, Value>* root);
	int getHeight(Node<Key, Value>* root) const;
	bool isNodeBalanced(Node<Key, Value>* node) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
	current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
	/*I chose to init to nullptr because if you want to instead init to
	  a new node with values set to null then you are using a new node instead of traversing
	  over existing ones. */
	current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	/*might need to change these to member by member comparisons*/

	if (rhs.current_ == nullptr)
	{
		return current_ == nullptr;
	}

	/*do you need to check key and value or is it encompassed in getItem()?*/
	return this->current_->getItem() == rhs.current_->getItem() &&
		this->current_->getLeft() == rhs.current_->getLeft() &&
		this->current_->getRight() == rhs.current_->getRight() &&
		this->current_->getParent() == rhs.current_->getParent();
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{

	if (rhs == nullptr)
	{
		return current_ != nullptr;
	}

	else
	{
		return this->current_->getItem() != rhs.current_->getItem() ||
			this->current_->getLeft() != rhs.current_->getLeft() ||
			this->current_->getRight() != rhs.current_->getRight() ||
			this->current_->getParent() != rhs.current_->getParent();
		/*corrected to rhs.current_->
		  because rhs is a ptr.
		*/
	}
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
	// If the right subtree is not empty, move to the leftmost node of the right subtree
	if (current_->getRight() != nullptr) {
		current_ = current_->getRight();
		while (current_->getLeft() != nullptr) {
			current_ = current_->getLeft();
		}
	}
	else {
		// Otherwise, move up until you find a node whose left child is the current node
		Node<Key, Value>* parent = current_->getParent();
		while (parent != nullptr && current_ == parent->getRight()) {
			current_ = parent;
			parent = parent->getParent();
		}
		current_ = parent; // Move to the parent node
	}

	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
	root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO

	clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
	// if tree is empty
	if (root_ == nullptr)
	{
		root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
		//root_ = keyValuePair;
		return;
	}

	// insertion step

	Node<Key, Value>* curr = root_;

	while (1)
	{
		// same key, then update the value
		if (keyValuePair.first == curr->getKey())
		{
			curr->setValue(keyValuePair.second);
			return;
		}

		// move to the left
		else if (keyValuePair.first < curr->getKey())
		{			
			if (curr->getLeft() == nullptr) // found the spot for insertion :)
			{
				Node<Key, Value>* insertedNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
				curr->setLeft(insertedNode);
				return;
			}
			else // continue the loop :(
			{
				curr = curr->getLeft();
				continue;
			}
		}

		// to the right now y'all
		else if (keyValuePair.first > curr->getKey())
		{
			if (curr->getRight() == nullptr)
			{
				Node<Key, Value>* insertedNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, curr);
				curr->setRight(insertedNode);
				return;
			}
			else
			{
				curr = curr->getRight();
				continue;
			}
		}
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// if empty
	if (root_ == nullptr)
	{
		// throw an error?
		return;
	}


	Node<Key, Value>* curr = internalFind(key);

	// if the node could not be found
	if (curr == nullptr)
	{
		/*throw an error here?*/
		return;
	}

	// has 2 children
	if (curr->getLeft() != nullptr && curr->getRight() != nullptr)
	{
		// swap with predecessor, then have to check again to see if the new position
		// previously predecessor has one or two children
		// if it was the root, update root_; no, because swap accounts for the root
		// swap w/ predecessor + then call remove again with the same key in it's new location
		// although, the right-most child is always either going to either have only a left child,
		// or nothing at all because if it had a right child then it wouldn't be the right most node
		Node<Key, Value>* pred = predecessor(curr);
		nodeSwap(curr, pred);
		//this->remove(key);
		/*
		cannot call it again because internalFind() will not be able to get the key.
		Instead, have it placed above 0 children and 1 child cases
		so that it will use the same curr that we already found.
		*/
	}

	// has 0 children
	if (curr->getLeft() == nullptr && curr->getRight() == nullptr)
	{
		// is root node
		if (curr == root_)
		{
			root_ = nullptr;
			delete curr;
			return;
		}

		// is a left child
		if (curr->getParent()->getLeft() == curr)
		{
			curr->getParent()->setLeft(nullptr);
		}
		else
		{
			curr->getParent()->setRight(nullptr);
		}
		delete curr;
	}

	// has a left child only
	else if (curr->getLeft() != nullptr && curr->getRight() == nullptr)
	{
		// if it is the root
		if (curr == root_)
		{
			root_ = curr->getLeft();
			root_->setParent(nullptr);
			// change root_'s ptrs to be curr's so that you don't lose curr's children
			// root_->setRight(curr->getRight());
			// could just swap and delete curr
			delete curr;
			return;
		}

		// change curr's child's parent into curr's parent
		curr->getLeft()->setParent(curr->getParent());
		// if curr is a left child
		if (curr->getParent()->getLeft() == curr)
		{
			curr->getParent()->setLeft(curr->getLeft());
		}
		else
		{
			curr->getParent()->setRight(curr->getLeft());
		}
		delete curr;
	}

	// has a right child only
	else if (curr->getLeft() == nullptr && curr->getRight() != nullptr)
	{
		// if it is the root
		if (curr == root_)
		{
			root_ = curr->getRight();
			root_->setParent(nullptr);
			// do something here
			delete curr;
			return;
		}

		curr->getRight()->setParent(curr->getParent());
		// if curr is a left child
		if (curr->getParent()->getLeft() == curr)
		{
			curr->getParent()->setLeft(curr->getRight()); // bug on this line, was initially curr->getLeft();
		}
		else
		{
			curr->getParent()->setRight(curr->getRight());
		}
		delete curr;
	}
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

	if (current == nullptr)
	{
		return current;
	}

	// divide up into has left child or has no left child

	// down one and right however many

	// has a left child
	if (current->getLeft() != nullptr)
	{
		current = current->getLeft();

		while (current->getRight() != nullptr)
		{
			current = current->getRight();
		}

		return current;
	}

	// does not have a left child
	// traverse all the way up until you reach a parent that had you as a right child
	// until current = current->getParent()->getRight()

	// does not have a left child
	else
	{
		while (current != current->getParent()->getRight())
		{
			current = current->getParent();
		}

		// found the predecessor
		return current->getParent();
	}
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// clearBinaryTree
	clearBinaryTree(root_);

	// set root = nullptr
	root_ = nullptr;
}

/**
* A helper function to delete each node in a tree.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearBinaryTree(Node<Key, Value>* root)
{
	// base case
	if (root == nullptr)
	{
		return;
	}

	clearBinaryTree(root->getLeft());
	clearBinaryTree(root->getRight());

	// delete a node
	delete root;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
	// go to the leftest node until nullptr

	// if tree is empty
	if (root_ == nullptr)
	{
		// throw an error?
		return nullptr;
	}

	Node<Key, Value>* curr = root_;

	while (1)
	{
		if (curr->getLeft() == nullptr)
		{
			return curr;
		}
		curr = curr->getLeft();
	}
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

	Node<Key, Value>* curr = root_;

	while (curr != nullptr)
	{
		if (curr->getKey() == key)
		{
			return curr;
		}
		else if (curr->getKey() > key)
		{
			curr = curr->getLeft();
			continue;
		}
		else if (curr->getKey() < key)
		{
			curr = curr->getRight();
			continue;
		}
	}
	return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	return isNodeBalanced(root_);

	// check the heights of left + right

	// use the iterator to check each node? nope.

	// may need to add helper function that takes in an argument

	// call it on left_ and right_

}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isNodeBalanced(Node<Key, Value>* node) const
{
	if (node == nullptr)
	{
		return true;
	}

	int lh = getHeight(node->getLeft()); // left height
	int rh = getHeight(node->getRight()); // right height

	if (lh - rh <= 1 && lh - rh >= -1)
	{
		return isNodeBalanced(node->getLeft()) && isNodeBalanced(node->getRight());
	}
	else
	{
		return false;
	}
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value>* root) const
{
	// base case
	if (root == nullptr) {
		return 0;
	}

	// recursive step
	int left_height = getHeight(root->getLeft());
	// std::cout << root->key << "; ";
	int right_height = getHeight(root->getRight());

	if (left_height > right_height) {
		return 1 + left_height;
	}
	else {
		return 1 + right_height;
	}
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
