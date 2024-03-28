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
	/*

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

	*/

	cout << "------------Testing AVL Tree------------" << endl;

	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(std::make_pair(1, 9));
	testTree.insert(std::make_pair(2, 8));

	testTree.print();

	cout << "------------Finished Specific Test------------" << endl;

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
