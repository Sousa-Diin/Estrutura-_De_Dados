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
    void inOrderHelper(Node* node,int& cont);

public:
    BST();
    void insert(int key);
    bool search(int key);
    void inOrder();
	int sheetIsNull(Node* node);
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

void BST::inOrderHelper(Node* node, int& cont) {
	int count = 0;
    if (node == NULL) {
        return;
    }else if(node)
	count += sheetIsNull(node);
    inOrderHelper(node->left, cont);
    //std::cout << node->key << " ";
	//cout << "contagem: " << count << endl;
	cont += count;
    inOrderHelper(node->right, cont);
	
	
}

void BST::inOrder() {
	int cont = 0;
    inOrderHelper(root, cont);
	//quantidade de nó folhas
	cout << cont << endl;
}
int BST::sheetIsNull(Node* node){
	int count = 0;
	if(node == NULL)
		return 1;
	else{
		if(node->right == NULL){
			count += sheetIsNull(node->right);
		}else if(node->left == NULL){			
			count += sheetIsNull(node->left);
		}
		
	}
	return count;
}

int main(){

	BST abb;
	int num, elemento, i = 0;
	cin >> num;
	while(i < num){
		cin >> elemento;
		abb.insert(elemento);
		i++;
	}
	//utilizado pra mostrar quantidade de no folhas
	abb.inOrder();
	cout << endl;
	return 0;
}