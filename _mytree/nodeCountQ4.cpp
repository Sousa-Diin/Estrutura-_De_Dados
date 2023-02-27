//Questão 4: Árvore binária (ABB) - Contagem de nós
// Wildes Augusto de Sousa
#include <iostream>
using namespace std;

typedef int Dado; 

class noh{
	friend class BST;
	private:
		Dado value;
        noh* left;
		noh* right;
        int rightCount;
        int leftCount;
		
	public:
        noh(){
            value = -1;
            rightCount = 0;
            leftCount = 0;
            right = NULL;
			left = NULL;
        }
		noh(Dado outroDado){
			value = outroDado;
            rightCount = 0;
            leftCount = 0;
			right = NULL;
			left = NULL;
		}
        Dado getValue(){
            return value;
        }

	
}; 

class BST {
	private:
		noh* root;
        void percorreInOrderAux(noh* atual);
		noh* insertRecAux(noh* no, Dado value);
        noh* searchAux(Dado elemento);
        
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){}
		void insertRec(Dado value);
        void showSheet();
        noh* search(Dado element);
        int countNodeLeft();
        int countNodeRight();
        int countNodeTree();
};

void BST::insertRec( Dado value){
    
	root = insertRecAux(root, value);
}

noh* BST::insertRecAux(noh* oneNo, Dado oneValue){
	if (oneNo == NULL){
		noh* myNew = new noh(oneValue);
        return myNew;
	}else if(oneValue < oneNo->value){
        
        oneNo->left = insertRecAux(oneNo->left, oneValue);
        oneNo->leftCount++;
        
    }else if (oneValue > oneNo->value){
        
        oneNo->right = insertRecAux(oneNo->right, oneValue);
        oneNo->rightCount++;
        
    }else{
        //throw(repeat key in insertion"");
        cout << "\nERRO: \"key repeat on insertion\"\n";
    }
   
    return oneNo;
}

void BST::percorreInOrderAux(noh* current){
    if(current != NULL){
        percorreInOrderAux(current->left);
        cout << current->value << " ";
        percorreInOrderAux(current->right);
    }
}

void BST::showSheet(){
   
    percorreInOrderAux(root);
    cout << endl;
}

		
noh* BST::searchAux(Dado elemento){
    noh* atual = root;
    while (atual != NULL) {
        if (atual->value == elemento) {
            return atual;
        } else if (elemento < atual->value ) {
            atual = atual->left;
        } else {
            atual = atual->right;
        }
    }
    return atual;
}
noh* BST::search(Dado element){
    noh* wanted = searchAux(element);
    if (wanted == NULL){
        cout << "Não encontrado ";
    } else {
        // efetua ação desejada, 
        return wanted; 
    }

	return NULL;
}


int BST::countNodeRight(){
    return root->rightCount;
}

int BST::countNodeLeft(){
    return root->leftCount;
}

int BST::countNodeTree(){
    return 1 + countNodeRight() + countNodeLeft();
}


void menu(BST& abb){
    unsigned int op;

    while(cin >> op and op != -1){
       
        //cout << "para inserir uma chave  ";

        abb.insertRec(op);

    }
}

int main(){
    BST abb;
    menu(abb);

    
    cout << abb.countNodeTree() << " ";
    //" Diferença das Subárvores: " 
    cout << abb.countNodeLeft() - abb.countNodeRight() << endl;
  

    return 0;
}