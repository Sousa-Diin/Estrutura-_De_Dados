
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
        int level;
        int rightCount;
        int leftCount;
		
	public:
        noh(){
            value = -1;
            rightCount = 0;
            leftCount = 0;
            level = 0;
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
        int isSheet(){
            return (right == NULL and left == NULL );
        }

	
}; 

class BST {
	private:
		noh* root;
        void percorreInOrderAux(noh* atual,int& qtdNode);
        void percorrePreOrderAux(noh* current);
        void percorrePostOrderAux(noh* current);
		noh* insertRecAux(noh* no, Dado value);
        noh* removeRecAux(noh* oneNo, Dado value);
        noh* removeSmaller(noh* rootSub);
        noh* miniAux(noh* rootSubTree);
        noh* searchAux(Dado elemento);
        void deleteRec(noh* oneNoh);
        int countSheetAux(noh* atual);
        noh* maximoAux(noh* rootSubTree);
        void levelInOrderAux(noh* current, int level, int index);
        
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){}
		void insertRec(Dado value);
        void showSheet();
        void viewLevel(int index);
        noh* search(Dado element);
        void removeRec(Dado value);
        Dado maximo();
        Dado minimo();
        int countNodeLeft();
        int countNodeRight();
        int countNodeTree();
        int countSheet();
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
/// @brief Função que imprime os node nível a nível
/// @param current raiz
/// @param level inicia o nível, e captura o nivel de cada node e atualiza o atributo da class noh
/// @param index seta o nivel para impressão
void BST::levelInOrderAux(noh* current, int level, int index){
    
    if(current){
        
        levelInOrderAux(current->left, level+1, index);
        current->level= level; /*** atualiza o nivel de cada node***/
       
        //impressão referente a cada nivel
        if(current->level == index){
            cout << current->value  << " ";

        }
        levelInOrderAux(current->right, level+1,index);
        
    }
}

void BST::percorreInOrderAux(noh* current,int& qtdNode){
    if(current != NULL){
        percorreInOrderAux(current->left, qtdNode);
        //cout << current->value <<  " ";
        percorreInOrderAux(current->right, qtdNode);
        qtdNode += current->isSheet();
    }
}
void BST::viewLevel(int index){
    
    levelInOrderAux(root, 0, index);
    cout << endl;
}


void BST::showSheet(){
    int qtdNode = 0;
    percorreInOrderAux(root, qtdNode);
    cout << qtdNode << endl;
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
        cout << "Não encontrado " << endl;;
    } else {
        // efetua ação desejada, 
        return wanted; 
    }

	return NULL;
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
   
    } else{ 
        // nó não tem filhos à esquerda
        if (oneNo->left == NULL) {
            subTree = oneNo->right;
        // nó não tem filhos à direita
        } else if (oneNo->right == NULL) {
            subTree = oneNo->left;
        } else { 
            subTree = miniAux(oneNo->right);
            subTree->right = removeSmaller(oneNo->right); 
            subTree->left = oneNo->left;
        }
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


int BST::countNodeRight(){
    return root->rightCount;
}

int BST::countNodeLeft(){
    return root->leftCount;
}

int BST::countNodeTree(){
    return 1 + countNodeRight() + countNodeLeft();
}

int BST::countSheet(){

    return countSheetAux(root);
}
int BST::countSheetAux(noh* atual){
    int sheet = 1;
    if(atual != NULL){
        countSheetAux(atual->left);
        if(atual->isSheet()){
            sheet++;
        }
        countSheetAux(atual->right);
        
    }
    return sheet;
}


void menu(BST& abb){
    char op;
    Dado max,min = -1;

    while(cin >> op and op != 'f'){
        Dado value;
        int i = 0;
        switch(op){
            case 'i':
                //cout << "para inserir uma chave  ";
                cin >> value;
                abb.insertRec(value);

                break;
            case 'e':
                
                
                while(i < abb.countNodeTree() /2){
                    abb.viewLevel(i);
                    //cout << endl;
                    i++;
               }
                
                break;
            case 's':
                //cout << "para escrever todos os sucessores de uma chave\n";
                cin >> value;
                while(value >= abb.minimo()){
                    abb.removeRec(abb.minimo());
                }
                abb.showSheet();
                cout << endl;
                break;
            case 'q':
                cout << " Quantidade de nó da Tree: " << abb.countNodeTree() << endl;
                cout << " Quantidade de nó da SubEsq: " << abb.countNodeLeft() << endl;
                cout << " Quantidade de nó da SubDir: " << abb.countNodeRight() << endl;
                cout << " Diferença das Subárvores: " << abb.countNodeLeft() - abb.countNodeRight() << endl;

                break;
            case 'n':
                i = (abb.countNodeTree() / 2);
                if(i % 2 == 0){
                    cout << i << endl; 
                }
                    cout << i+1 << endl; 
                break;
            case 'v':
                abb.showSheet();
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

    //abb.view();
    cout << endl;

    return 0;
}