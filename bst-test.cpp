#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"
#include <utility>
#include<stdio.h> // these are for random number generator
#include<stdlib.h> 
#include<cstdlib>

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));

	//prettyPrintBST(bt);
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

	// Specific BST Tests

	cout << "------------Testing Random Insert------------" << endl;

	BinarySearchTree<int, int> testTree;

	testTree.insert(std::make_pair(15, 15));
	testTree.insert(std::make_pair(-41, -41));
	testTree.insert(std::make_pair(-32, -32));
	testTree.insert(std::make_pair(-39, -39));
	testTree.insert(std::make_pair(73, 73));
	testTree.insert(std::make_pair(138, 138));
	testTree.insert(std::make_pair(-117, -117));
	testTree.insert(std::make_pair(147, 147));
	testTree.insert(std::make_pair(-1, -1));
	testTree.insert(std::make_pair(65, 65));

	testTree.insert(std::make_pair(5, 5));
	testTree.insert(std::make_pair(31, 31));
	testTree.insert(std::make_pair(-72, -72));
	testTree.insert(std::make_pair(-50, -50));
	testTree.insert(std::make_pair(49, 49));
	testTree.insert(std::make_pair(35, 35));
	testTree.insert(std::make_pair(79, 79));
	testTree.insert(std::make_pair(-60, -60));
	testTree.insert(std::make_pair(105, 105));
	testTree.insert(std::make_pair(-149, -149));

	testTree.insert(std::make_pair(-67, -67));
	testTree.insert(std::make_pair(-68, -68));
	testTree.insert(std::make_pair(134, 134));
	testTree.insert(std::make_pair(119, 119));
	testTree.insert(std::make_pair(58, 58));
	testTree.insert(std::make_pair(121, 121));
	testTree.insert(std::make_pair(-22, -22));
	testTree.insert(std::make_pair(46, 46));
	testTree.insert(std::make_pair(36, 36));
	testTree.insert(std::make_pair(-123, -123));

	testTree.print();

	testTree.remove(-50);

	cout << "after remove -50:" << endl;

	testTree.print();

	testTree.remove(147);

	cout << "after remove 147:" << endl;

	testTree.print();

	testTree.remove(105);

	cout << "after remove 105:" << endl;

	testTree.print();

	testTree.remove(-149);

	cout << "after remove -147:" << endl;

	testTree.print();

	cout << "------------Finished Testing------------" << endl;

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    return 0;
}
