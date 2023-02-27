#include <iostream>
using namespace std;

class noh {
public:
    int key;
    int height;
    noh* left;
    noh* right;
    int level;
    int rightCount;
    int leftCount;

    noh(int key) {
        this->key = key;
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
        this->level = 0;
    }
};

class AVL {
private:
    noh* root;

    int height(noh* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int getBalance(noh* node) {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    noh* rightRotate(noh* current) {
        noh* swap = current->left;
        noh* subtreeRight = swap->right;
        swap->right = current;
        current->left = subtreeRight;
        current->height = max(height(current->left), height(current->right)) + 1;
        swap->height = max(height(swap->left), height(swap->right)) + 1;
        return swap;
    }

    noh* leftRotate(noh* current) {
        noh* swap = current->right;
        noh* subtreeLeft = swap->left;
        swap->left = current;
        current->right = subtreeLeft;
        current->height = std::max(height(current->left), height(current->right)) + 1;
        swap->height = std::max(height(swap->left), height(swap->right)) + 1;
        return swap;
    }

    noh* insert(noh* node, int key) {
        if (node == NULL)
            return new noh(key);
        if (key < node->key){
            node->left = insert(node->left, key);
            node->leftCount++;
        }else if (key > node->key){
            node->right = insert(node->right, key);
            node->rightCount++;
        }else
            return node;
        node->height = max(height(node->left), height(node->right)) + 1;
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

    void percorreInOrdem(noh* current){
        if(current != NULL){
            percorreInOrdem(current->left);
            cout << current->key << " ";
            percorreInOrdem(current->right);
        }
    }
    /// @brief Função que imprime os node nível a nível
    /// @param current raiz
    /// @param level inicia o nível, e captura o nivel de cada node e atualiza o atributo da class noh
    /// @param index seta o nivel para impressão
    void levelInOrderAux(noh* current, int level, int index){
        
        if(current){
            
            levelInOrderAux(current->left, level+1, index);
            current->level= level; /*** atualiza o nivel de cada node***/
        
            //impressão referente a cada nivel
            if(current->level == index){
                cout << current->key << " ";

            }
            levelInOrderAux(current->right, level+1,index);
            
        }
    }


public:
    AVL() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void view(){
        percorreInOrdem(root);
        cout << endl;
    }

    void viewLevel(int index){
    
        levelInOrderAux(root, 0, index);
    cout << endl;
}


int countNodeRight(){
    return root->rightCount;
}

int countNodeLeft(){
    return root->leftCount;
}

int countNodeTree(){
    return 1 + countNodeRight() + countNodeLeft();
}

};

int main() {
    AVL tree;
    int i = 0;
    while(cin >> i and i != -1){
    	
        tree.insert(i);
        tree.insert(i);
        tree.insert(i);
        //tree.view();
    }
    tree.view();
    i = 0;
    while(i < tree.countNodeTree() /2){
        tree.viewLevel(i);
        //cout << endl;
        i++;
    }
}
