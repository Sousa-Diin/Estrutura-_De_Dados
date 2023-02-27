#include <iostream>

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }
};

int main() {
    AVLTree tree;
    int i = 0;
    while(cin >> i != -1){
    	cout << i << endl;
    }
    tree.insert(300);
    tree.insert(250);
    tree.insert(30);
}
