#include <stdint.h>
#include <stdio.h>

#include <assert.h>

struct Node {
	int32_t value; // this is our payload, really should be something useful, like "Customer"
	Node* left; // left and right are pointers to our two children. 
	Node* right; // either or both of left/right can be null (i.e., equal to zero)

	Node* parent; // the parent pointer points to our parent. This pointer turns out
	              // to be useful when we want to start traversing a tree (without recursion)
	              // for now, I'll ignore this component
};


void destroyTree(Node* root){

	if( !root ){ return; }

	destroyTree( root->left );
	destroyTree( root->right );
	
	delete root;

}


Node* insert(Node* root, int32_t v) {
	Node* child = new Node;
	child->value = v;
	child->left = 0;
	child->right = 0;
	child->parent = 0;

	if (root == 0) { 
		return child;
	}

	Node* parent = root;
	while (true) {
		if (v < parent->value) {
			if (parent->left == 0) { break; }
			parent = parent->left;
		} else {
			if (parent->right == 0) { break; }
			parent = parent->right;
		}
	}

	if (v < parent->value) { 
		parent->left = child;
	} else {
		parent->right = child;
	}
	child->parent = parent;

	return root;
}

Node* smallest(Node* root) {
	if (! root) { return 0; } // WTF? smallest in an empty tree????

	while (root->left != 0) {
		root = root->left;
	}

	return root;
}

Node* find(Node* root, int32_t v) {
	Node* p = root;

	while (p != 0) {
		if (p->value == v) { return p; }
		else if (v < p->value) {
			p = p->left;
		} else {
			p = p->right;
		}
	}
	return 0;
}

Node* successor(Node* p) {
	if (p == 0) { // WTF?
		return 0;
	}

	if (p->right != 0) {					// if p has a right child
		Node* s = p->right;					//
		while (s->left != 0) {				// then go the the left-most node from the right child
			s = s->left;
		}
		return s;
	} else {								// if p has no right subchild
		Node* s = p->parent;				// then p is the right-most node from the left child of it's successor
		while (s != 0 && s->left != p) {	// so go up the branch until p is no longer the right child of it's parent
			p = s;
			s = p->parent;
		}
		return s;
	}
}


Node* remove(Node* root, int32_t v) {
	Node* p = find(root, v);
	if (p == 0) { // WTF???
		return root;
	}

	if (p->right == 0) { // case A, easy case, no right child
		Node* parent = p->parent;
		if (parent == 0) {
			root = p->left;
		} 	else {
			if (p == parent->right) {
				parent->right = p->left;
			} else {
				parent->left = p->left;
			}
		}
		if (p->left) {
			p->left->parent = parent;
		}
		delete p;

	} else { // case B, hard case, possibly two children 
		Node* s = successor(p);
		p->value = s->value;
		Node* parent = s->parent;
		if (s == parent->right) {
			parent->right = s->right;
		} else {
			parent->left = s->right;
		}
		if (s->right) {
			s->right->parent = parent;
		}
		delete s;
	}
	
	return root;
}

//EDIT THIS FUNCTION!!!
uint32_t treeNodes(Node* root) {
	return 0;
}

//EDIT THIS FUNCTION!!!
uint32_t recTreeNodes(Node* root) {
	//base case: node is nullptr
	if(root == nullptr) {
		return 0;
	}
	else {
		return recTreeNodes(root.left) + 1 + recTreeNodes(root.right);
	}
}

//EDIT THIS FUNCTION!!!
uint32_t treeHeight(Node* root) { // if confusing, see "successor" fxn first
	return 0;
}

//EDIT THIS FUNCTION!!!
uint32_t recTreeHeight(Node* root){
	//base case: node == nullptr
	if (root == nullptr) {
		return 0;
	}
	else {
		uint32_t left_height = recTreeHeight(root.left);
		uint32_t right_height = recTreeHeight(root.right);
		return (left_height > right_height) ? (left_height) : (right_height)   +1;
	}
}


void printTree(Node* root) {
	char* prefix = "";

	Node* p = smallest(root);

	while (p) {
		printf("%s%d", prefix, p->value);
		prefix = ", ";
		p = successor(p);
	}
	printf("\n");
}


void printInfo(Node* root){
	printf("number of nodes in this tree (iterative):\t%d\n", treeNodes(root) );
	printf("number of nodes in this tree (recursive):\t%d\n", recTreeNodes(root) );
	printf("height of this tree (iterative)\t\t%d\n", treeHeight(root) );
	printf("height of this tree (recursive)\t\t%d\n\n", recTreeHeight(root) );
}
