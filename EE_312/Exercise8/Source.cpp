
#include "BST.h"
#include <assert.h>

#include <random>
#include <time.h>

void main(void){
	Node* root = nullptr;

	root = insert(root, 4);
	printTree(root);

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 25);
	root = insert(root, 28);
	root = insert(root, 2);
	root = insert(root, 42);

	root = remove(root, 4);
	printTree(root);
	printInfo(root);

	// add your own tests here
}