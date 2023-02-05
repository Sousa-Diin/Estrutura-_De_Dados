// Starting AVL tree implementation from BST tree 
// Date: 04/02/2023
// Wildes .A. Sousa
#include <iostream>
using namespace std;

typedef int Dado; 

class noh{
	friend class AVL;
	private:
		Dado value;
        Dado height;
		noh* right;
		noh* left;
	public:
        noh(){
            value = -1;
            height = 1;
            right = NULL;
			left = NULL;
        }
		noh(Dado outroDado){
			value = outroDado;
            height = 1;
			right = NULL;
			left = NULL;
		}
        Dado getValue(){
            return value;
        }

	
}; 

class AVL {
	private:
		noh* root;
        void percorreInOrderAux(noh* atual);
        void percorrePreOrderAux(noh* current);
        void percorrePostOrderAux(noh* current);
		noh* insertRecAux(noh* no, Dado value, int& i);
        noh* searchAux(Dado elemento);
        int getHeight(noh* currenty);
        int balanceFactor(noh* noh);
        noh* rightRotate(noh* currenty);
        noh* lefttRotate(noh* currenty);
        noh* leftRightRotation(noh* currenty);
        noh* righLefttRotation(noh* currenty);    
		
	public:
		 AVL(){
            root = NULL;
         }
		~AVL(){}
		void insertRec(Dado value);
        void showSheet();
        noh* search(Dado element);
};

void AVL::insertRec( Dado value){
    int i = 1;
	root = insertRecAux(root, value,i);
    //cout << "quantidade de noh: " << i << endl;
}

noh* AVL::insertRecAux(noh* oneNo, Dado oneValue,int& i){
	if (oneNo == NULL){
		noh* myNew = new noh(oneValue);
        return myNew;
	}else if(oneValue < oneNo->value){

        oneNo->left = insertRecAux(oneNo->left, oneValue, i);
        
    }else if (oneValue > oneNo->value){

        oneNo->right = insertRecAux(oneNo->right, oneValue, i);
        
    }else{
        //throw(repeat key in insertion"");
        cout << "\nERRO: \"key repeat on insertion\"\n";
    }
    i+=1;
    return oneNo;
}

void AVL::percorreInOrderAux(noh* current){
    if(current != NULL){
        percorreInOrderAux(current->left);
        cout << current->value << " ";
        percorreInOrderAux(current->right);
    }
}
void AVL::percorrePreOrderAux(noh* current){
    if(current != NULL){
        cout << current->value << " ";
        percorrePreOrderAux(current->left);
        percorrePreOrderAux(current->right);
    }
}
void AVL::percorrePostOrderAux(noh* current){
    if(current != NULL){
        percorreInOrderAux(current->left);
        percorreInOrderAux(current->right);
        cout << current->value << " ";
    }
}


void AVL::showSheet(){

    percorrePreOrderAux(root);
    cout << endl;
    percorreInOrderAux(root);
    cout << endl;
    percorrePostOrderAux(root);
}

		
noh* AVL::searchAux(Dado elemento){
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
noh* AVL::search(Dado element){
    noh* wanted = searchAux(element);
    if (wanted == NULL){
        cout << "Não encontrado ";
    } else {
        // efetua ação desejada, 
        return wanted; 
    }

	return NULL;
}

int AVL::getHeight(noh* currenty){}
int AVL::balanceFactor(noh* noh){}
noh* AVL::rightRotate(noh* currenty){}
noh* AVL::lefttRotate(noh* currenty){}
noh* AVL::leftRightRotation(noh* currenty){}
noh* AVL::righLefttRotation(noh* currenty){}

int wanted(AVL& abb, int search){
    noh* wanted = abb.search(search);
    if(wanted == NULL)
        cout << "elemento não pertence à árvore." << endl;
    return wanted->getValue();
}

int main() {

	AVL avl;
    Dado newDado;
    while(cin >> newDado and newDado != -1){
        if(newDado > 0){
            avl.insertRec(newDado);
        }
    }
    
	cout << "Dado da árvore binaria: " << endl;
    avl.showSheet();
    cout << endl;

    cout << "buscar na árvore binaria: " << endl;
    cin >> newDado;
    cout << wanted(avl,newDado) << endl;
   

  return 0;
}