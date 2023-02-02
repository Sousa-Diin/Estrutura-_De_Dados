#include <iostream>
using namespace std;
struct Node {
    int key;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;
    Node* insertHelper(Node* node, int key);
    Node* searchHelper(Node* node, int key);
    void inOrderHelper(Node* node);

public:
    BST();
    void insert(int key);
    bool search(int key);
    void inOrder();
};

BST::BST() {
    root = NULL;
}

Node* BST::insertHelper(Node* node, int key) {
    if (node == NULL) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (key < node->key) {
        node->left = insertHelper(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertHelper(node->right, key);
    }
    return node;
}

void BST::insert(int key) {
    root = insertHelper(root, key);
}

Node* BST::searchHelper(Node* node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchHelper(node->left, key);
    }
    return searchHelper(node->right, key);
}

bool BST::search(int key) {
    Node* result = searchHelper(root, key);
    if (result == NULL) {
        return false;
    }
    return true;
}

void BST::inOrderHelper(Node* node) {
    if (node == NULL) {
        return;
    }
    inOrderHelper(node->left);
    std::cout << node->key << " ";
    inOrderHelper(node->right);
}

void BST::inOrder() {
    inOrderHelper(root);
}

int main(){

	BST abb;
	int num;
	cout << "entre com valores na arvore: ";
	//cin >> num;
	while(cin >> num and num != -1){
		if(num != -1){
			abb.insert(num);
		}
	}
	
	
	abb.inOrder();
	cout << endl;

	return 0;
}
