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
        unsigned height;
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
        unsigned getHeight(noh* current);
        unsigned maxheight(unsigned rightHeight, unsigned leftHeight);
        void updateHeight(noh* currenty);
        int balanceFactor(noh* noh);
        noh* rightRotate(noh* current);
        noh* lefttRotate(noh* current);
        noh* leftRightRotation(noh* current);
        noh* righLefttRotation(noh* current);    
		
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
    int fb =0;
	if (oneNo == NULL){
		noh* myNew = new noh(oneValue);
        return myNew;
	}else if(oneValue < oneNo->value){

        oneNo->left = insertRecAux(oneNo->left, oneValue, i);
        updateHeight(oneNo->left);
        fb = balanceFactor(oneNo);
        cout << oneNo->value << "/ Fb = "  << fb << " => ";
        //cout << current->value << "/ Fb = " << " =>";
        
    }else if (oneValue > oneNo->value){

        oneNo->right = insertRecAux(oneNo->right, oneValue, i);
        fb = balanceFactor(oneNo);
        cout << oneNo->value << "/ Fb = "  << fb << " => ";
        updateHeight(oneNo->right);
    }else{
        //throw(repeat key in insertion"");
        cout << "\nERRO: \"key repeat on insertion\"\n";
    }
    i+=1;
    
    updateHeight(root);
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
        cout << current->value << "/ " << current->height << " ->";
        //updateHeight(current);
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
/// @brief node height catch 
/// @param currenty node
/// @return the current node height 
unsigned AVL::getHeight(noh* currenty){
    if(!currenty){
        return 0;
    }
    return currenty->height;
}
/// @brief Function that update the node height
/// @param current current node
void AVL::updateHeight(noh* current){
    unsigned rightHeight = getHeight(current->right);
    unsigned leftHeight = getHeight(current->left);
    current->height = 1 + maxheight(leftHeight, rightHeight);
}
/// @brief Function that verify the maximum param of height 
/// @param rightHeight right height
/// @param leftHeight left height
/// @return maximum height
unsigned AVL::maxheight(unsigned rightHeight, unsigned leftHeight){
    if(leftHeight >= rightHeight){
        return leftHeight;
    }
    return rightHeight;
}

int AVL::balanceFactor(noh* noh){
    return getHeight(noh->left) - getHeight(noh->right);
}
noh* AVL::rightRotate(noh* current){}
noh* AVL::lefttRotate(noh* current){}
noh* AVL::leftRightRotation(noh* current){}
noh* AVL::righLefttRotation(noh* current){}

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