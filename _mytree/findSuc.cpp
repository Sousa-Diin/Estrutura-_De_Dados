//Questão 2: Encontre o sucessor em uma Árvore Binária de Busca (ABB)
// Wildes Augusto de Sousa
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
        noh* removeRecAux(noh* oneNo, Dado value);
        noh* removeSmaller(noh* rootSub);
        noh* miniAux(noh* rootSubTree);
        noh* searchAux(Dado elemento);
        void deleteRec(noh* oneNoh);
        noh* maximoAux(noh* rootSubTree);
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){}
		void insertRec(Dado value);
        void view();
        noh* search(Dado element);
        void removeRec(Dado value);
        Dado maximo();
        Dado minimo();
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


noh* BST::removeRecAux(noh* oneNo, Dado value){
   if (oneNo == NULL){
        cout << "ERRO: ";
   }
    noh* subTree = oneNo;
    // valor menor que nó atual, vai para subárvore esquerda
    if ( value < oneNo->value ) {
    oneNo->left = removeRecAux(oneNo->left, value);
    // valor maior que nó atual, vai para subárvore direita
    }else if( value > oneNo->value ) {
    oneNo->right = removeRecAux(oneNo->right, value);
    // valor é igual ao armazenado no nó atual, 
    // que deve ser apagado
    } else{ // oneNo é removido neste senão
        // nó não tem filhos à esquerda
        if (oneNo->left == NULL) {
            subTree = oneNo->right;
        // nó não tem filhos à direita
        } else if (oneNo->right == NULL) {
            subTree = oneNo->left;
        } else { // nó tem dois filhos  
            // podemos trocar pelo antecessor ou sucessor
            subTree = miniAux(oneNo->right);
        // troca o sucessor por seu filho à direita
            subTree->right = removeSmaller(oneNo->right);  
        // filho à esquerda de umNoh torna-se filho à esquerda 
        // do sucessor
            subTree->left = oneNo->left;
        }
        // ponteiros ajustados, apagamos o nó
        delete oneNo;

    }
   
    return subTree;
}

void BST::removeRec(Dado value){
   root = removeRecAux(root, value);
}

noh* BST::removeSmaller(noh* rootsub){
    if (rootsub->left == NULL) {
        return rootsub->right;
    } else {
        rootsub->left =  removeSmaller(rootsub->left);
    return rootsub;
    } 

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


Dado BST::maximo(){
    if (root == NULL) {
        //geraErro(“Árvore vazia”);
    } else {
        noh* nohMaximo = maximoAux(root);
        return nohMaximo->value;
    }
}
noh* BST::maximoAux(noh* rootSubTree){
    while (rootSubTree->right != NULL) {
        rootSubTree = rootSubTree->right;
    }
    return rootSubTree;
}


void menu(BST& abb){
    char op;
    Dado max,min = -1;

    while(cin >> op and op != 'f'){
        Dado value;
        switch(op){
            case 'i':
                //cout << "para inserir uma chave  ";
                cin >> value;
                abb.insertRec(value);

                break;
            case 'e':
                cout << "para escrever o conteúdo da árvore\n";
                break;
            case 's':
                //cout << "para escrever todos os sucessores de uma chave\n";
                
                max = abb.maximo();
                min = abb.minimo();
                cout << " Maximo: " << max << endl;
                cout << " Minimo: " << min << endl;
                break;
            case 'f':
                cout << "para finalizar a execução do programa\n";
                break;

        }
    }
}

int main(){
    BST abb;
    menu(abb);

    abb.view();
    cout << endl;

    abb.removeRec(12);

    abb.view();
    cout << endl;
    return 0;
}