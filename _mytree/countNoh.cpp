//Questão 1: Contagem dos nós folha de uma Árvore Binária de Busca (ABB)
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
		noh* insertRecAux(noh* no, Dado value);
        void levelInOrderAux(noh* current, int level, int index);
        
		
	public:
		 BST(){
            root = NULL;
         }
		~BST(){}
		void insertRec(Dado value);
        void showSheet();
        void viewLevel(int index);
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
/// @brief Walks the subtrees and catches quatity of node
/// @param current root
/// @param qtdNode catches quatity of node
void BST::percorreInOrderAux(noh* current,int& qtdNode){
    if(current != NULL){
        percorreInOrderAux(current->left, qtdNode);
        //cout << current->value <<  " ";
        percorreInOrderAux(current->right, qtdNode);
        qtdNode += current->isSheet();
    }
}
/// @brief Show all the node of the level 
/// @param index seta the level 
void BST::viewLevel(int index){
    
    levelInOrderAux(root, 0, index);
    cout << endl;
}

/// @brief View quantity of Node
void BST::showSheet(){
    int qtdNode = 0;
    percorreInOrderAux(root, qtdNode);
    cout << qtdNode << endl;
    cout << endl;
}
/// @brief Função que executa tarefa expecifica da questao 1 do Dredd 
/// @param abb Benary Search Tree
void menu(BST& abb){
    
    Dado value;
    int qtd;
    cin >> qtd;
    while(qtd > 0){
        //cout << "para inserir uma chave  ";
        cin >> value;
        abb.insertRec(value);
        qtd--;

    }
    abb.showSheet();
}

int main(){
    BST abb;
    menu(abb);
    cout << endl;

    return 0;
}