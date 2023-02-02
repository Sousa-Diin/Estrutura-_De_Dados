//Questão 6: Árvore Binária de Busca com Contadores
// Wildes Augusto de Sousa

//Questão 2: Encontre o sucessor em uma Árvore Binária de Busca (ABB)
// Wildes Augusto de Sousa
#include <iostream>
using namespace std;

typedef int Dado; 

class noh{
	friend class BST;
	private:
		Dado value;
        Dado count;
		noh* right;
		noh* left;
	public:
        noh(){
            value = -1;
            count = 0;
            right = NULL;
			left = NULL;
        }
		noh(Dado outroDado){
			value = outroDado;
            count = 0;
			right = NULL;
			left = NULL;
		}
        
        Dado getValue(){
            return value;
        }
         Dado getRepetition(){
            return count;
        }
        Dado setRepetition(){
            return count--;
        }
        bool isRepetetion(){
            return count > 0;
        }
	
}; 

class BST {
	private:
		noh* root;
        void percorreInOrderAux(noh* atual, int nivel);
		noh* insertRecAux(noh* no, Dado value);
        noh* removeRecAux(noh* oneNo, Dado value);
        noh* miniAux(noh* rootSubTree);
        void destroi(noh* oneNo);
        noh* searchAux(Dado elemento);
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){ destroi(root);}
		void insertRec(Dado value);
        void view();
        noh* search(Dado element);
        void removeRec(Dado value);
        Dado minimo();
        noh* deleteNode(noh* root, int data);
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
        
    }else if (oneValue > oneNo->value){

        oneNo->right = insertRecAux(oneNo->right, oneValue);
        
    }else{
        //cout << "\nERRO: \"key repeat on insertion\"\n";
        //Conta quantidades de insercoes repetidas
        oneNo->count++;
    }

    return oneNo;
}

void BST::percorreInOrderAux(noh* current, int nivel){
    if(current){
        percorreInOrderAux(current->left, nivel +1);
       
        cout << current->value << "(" << current->count+1 << ")/" << nivel << " ";
      
        percorreInOrderAux(current->right, nivel+1);
    }
}


void BST::view(){
  
    percorreInOrderAux(root, 0);
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
        //cout << "Não encontrado ";
    } else {
        // efetua ação desejada, 
        return wanted; 
    }

	return NULL;
}

noh* BST::deleteNode(noh* root, int data) {
  if (root == NULL) {
    return root;
  } else if (data < root->value) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->value) {
    root->right = deleteNode(root->right, data);
  } else {
    // Case 1: No child
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      root = nullptr;
    }
    // Case 2: One child
    else if (root->left == nullptr) {
      noh* temp = root;
      root = root->right;
      delete temp;
    } else if (root->right == nullptr) {
      noh* temp = root;
      root = root->left;
      delete temp;
    }
    // Case 3: Two children
    else {
      noh* temp = miniAux(root->right);
      root->value = temp->value;
      root->right = deleteNode(root->right, temp->value);
    }
  }
  return root;
}
void BST::removeRec(Dado value){
   root = deleteNode(root, value);
   //cout << "entra na removeRec oK" << endl;
}

noh* BST::miniAux(noh* rootSubTree){
    while (rootSubTree->left != NULL) {
        rootSubTree = rootSubTree->left;
    }
    return rootSubTree;
}

Dado BST::minimo(){
    if (root == NULL) {
        //geraErro(“Árvore vazia”);
    } else {
        noh* nohMinimo = miniAux(root);
        return nohMinimo->value;
    }
}


void BST::destroi(noh* oneNo){
    if (oneNo) {
        destroi(oneNo->left);
        destroi(oneNo->right);
    } 
    delete oneNo;
}


void insertAux(BST& abb, int qtd){
    int i = 0;
    Dado value;
    while(i < qtd){
        cin >> value;
        abb.insertRec(value);
        i++;
    }
    abb.view();
}

void removeAux(BST& abb, int qtd){
    int i = 0;
    Dado value;
    noh* search;
    
    while(i++ < qtd){
        
        cin >> value;
        search = abb.search(value);
        
        if(search->isRepetetion()){
            search->setRepetition();
            
        }else {
            abb.removeRec(value);
        }
        
       // i++; ERRO "ao decrementar duplicação" STATUS corrigido 02/02/23
    }
    abb.view();
}


int main(){
    BST abb;
    insertAux(abb,10);
    removeAux(abb,5);
    insertAux(abb,10);
    removeAux(abb,5);
    //CORREÇÂO at 02/2023 ERRO na function removeAux
    return 0;
}
