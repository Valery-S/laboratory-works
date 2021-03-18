#ifndef _binary_tree_
#define _binary_tree_
struct Node {
	Node* left;
	Node* right;
	Node* parent;
	int count;
	char letter;

	Node() {
		this->left = NULL;
		this->right = NULL; 
		this->parent = NULL;
	}

	Node(Node* left, Node* right) {
		this->left = left;
		this->right = right;
		this->count = left->count + right->count;
		this->parent = NULL;
	}
};
struct MyCompare {
	bool operator()(Node* left, Node* right)const {
		return (left->count < right->count);
	}
}compare;
#endif