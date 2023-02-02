#include <iostream>
using namespace std;

typedef int Dado; 

class noh{
	friend class BST;
	private:
		Dado value;
		noh* right;
		noh* left;
	public:
        noh(){
            value = -1;
            right = NULL;
			left = NULL;
        }
		noh(Dado outroDado){
			value = outroDado;
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
        void percorrePreOrderAux(noh* current);
        void percorrePostOrderAux(noh* current);
		noh* insertRecAux(noh* no, Dado value, int& i);
        noh* searchAux(Dado elemento);
        void deleteRec(noh* oneNoh);
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){}
		void insertRec(Dado value);
        void view();
        noh* search(Dado element);
};

void BST::insertRec( Dado value){
    int i = 1;
	root = insertRecAux(root, value,i);
    //cout << "quantidade de noh: " << i << endl;
}

noh* BST::insertRecAux(noh* oneNo, Dado oneValue,int& i){
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

void BST::percorreInOrderAux(noh* current){
    if(current != NULL){
        percorreInOrderAux(current->left);
        cout << current->value << " ";
        percorreInOrderAux(current->right);
    }
}
void BST::percorrePreOrderAux(noh* current){
    if(current != NULL){
        cout << current->value << " ";
        percorrePreOrderAux(current->left);
        percorrePreOrderAux(current->right);
    }
}
void BST::percorrePostOrderAux(noh* current){
    if(current != NULL){
        percorreInOrderAux(current->left);
        percorreInOrderAux(current->right);
        cout << current->value << " ";
    }
}


void BST::view(){
    /*char order;
	cin >> order;
    switch(order){
        case '1': 
            cout << "In Pre Order: ";
            percorrePreOrderAux(root);
            break;
        case '2':
            cout << "\nIn Order: ";
            percorreInOrderAux(root);
            break;
        case '3':
            cout << "\nIn Post Order: ";
            percorrePostOrderAux(root);
            break;
    }
    */
    percorrePreOrderAux(root);
    cout << endl;
    percorreInOrderAux(root);
    cout << endl;
    percorrePostOrderAux(root);
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

void BST::deleteRec(noh* oneNoh){

}

int main() {

	BST abb;
    Dado newDado;
    while(cin >> newDado and newDado != -1){
        if(newDado > 0){
            abb.insertRec(newDado);
        }
    }
    
	cout << "Dado da árvore binaria: " << endl;
    abb.view();
    cout << endl;

    cout << "buscar na árvore binaria: " << endl;
    noh* wanted = abb.search(77);
    cout << "Noh encontrado: " << wanted->getValue() << endl;
    wanted = abb.search(101);

  return 0;
}