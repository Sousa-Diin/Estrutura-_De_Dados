#include<iostream>
using namespace std;

typedef int dataType;
const unsigned int CAPACIDADEFILHO = 4;
const unsigned int CAPACIDADECHAVE = 3;
const unsigned int MEIO = 1;


class No {
	friend class lista;
	private:
		dataType mDado;
		dataType mRef = 1;
		No* mProximo;
	public:
		No(dataType value){
			mDado = value;
			mProximo = NULL;
			mRef = value * 2;
			//cout << "Nó criado" << endl;
		}
		
		dataType getDado(){
			return mDado;
		}
		
		dataType getRef(){
			return mRef;
		}
};

// LISTA 

class lista {
    friend class Tree234;
	private:
		unsigned mTamanho;
		No* mInicio;
		No* mFim;
        dataType begin(){
            return mInicio->mDado;
        }

        dataType ending(){
            return mFim->mDado;
        }
	public:
		lista(){
			mTamanho = 0;
			mInicio = NULL;
			mFim = NULL;
		}
		
		~lista(){
            No* aux = mInicio;
            while(aux != NULL){
                removeNoInicio();
                aux = aux->mProximo; 
            }
			
		}
		
		bool listaVazia(){
			return (mTamanho == 0);
		}
		
		void insereNaListaVazia(dataType x){
			No* novo = new No(x);
			mInicio = novo;
			mFim = novo;
			mTamanho++;
		}
		
		void insereNoInicio(dataType x){
			
			if(listaVazia()){
				insereNaListaVazia(x);
			}else{
				No* novo = new No(x);
				novo->mProximo = mInicio;
				mInicio = novo;
				mTamanho++;
			}
			
		}

        dataType removeNoInicio(){
            dataType value;
            if (listaVazia()){
                //sairComErro();
            }else{
                No* aux = mInicio;
                value = aux->mDado;
                mInicio = aux->mProximo;
                delete aux;
                mTamanho--;
                if( listaVazia()){
                    mFim = NULL;
                }
            } 
            return value;
        }

		void insereNoFim(dataType z){
			if (listaVazia()){
				insereNaListaVazia(z);
			}else{
				No* novo = new No(z);
				mFim->mProximo = novo;
				mFim = novo;
				mTamanho++;
			}
			
		}

        dataType removeNoFim(){
            dataType value;
            if (listaVazia()){
                //sairComErro();
            }else{
                No* aux = mInicio;
                No* anterior = NULL;
                while(aux->mProximo != NULL){
                    anterior = aux;
                    aux = aux->mProximo;
                }
                value = aux->mDado;
                if(anterior == NULL){
                    mInicio = NULL;
                }else{
                    anterior->mProximo = NULL;
                }
                delete mFim;
                mFim = anterior;
                mTamanho--;
            
            } 
            return value;
        }
		
		void insereNaLista(dataType v, unsigned pos){
			
			
			if (pos == 0){
				insereNoInicio(v);
				mTamanho++;
			}else if(pos == mTamanho-1){
                insereNoFim(v);
                mTamanho++;
            }
            else{
				No* aux = mInicio;
				No* novo = new No(v);
				unsigned posAux = 0;
				while(posAux < pos - 1){
					posAux++;
					aux = aux->mProximo;
				}
				novo->mProximo = aux->mProximo;
				aux->mProximo = novo;
				mTamanho++;
			}
	
		}
		
		unsigned getTamanho(){
			return mTamanho;
		}
		
		void percorreLista(){
			No* aux = mInicio;
			int posAux = 0;
			while(aux != NULL){
				cout << aux->mDado << " ";
				aux = aux->mProximo;
			}
			//cout << endl;
		}
         dataType getKey(){
            return removeNoInicio();
         }
		
		void listar(){
			No*aux = mInicio;
			//int posAux = 0;
			cout << "Listando..." << endl;
			
			while(not(aux == NULL)){
				cout << aux->mDado << " ";
				aux = aux->mProximo;
			} 
			cout << endl;
		}
		
		No* ultimoDaLista(){ // retorna um clone do nó fim [imutavél]
			return mFim == NULL ? new No(-1) :new No(mFim->mDado);
		}
		
		void getInicio(){
			cout << "Inicio: " << mInicio->mDado << endl;
		}
		
		No* buscarNaLista(dataType elemento){
			No* aux = mInicio;
			if(listaVazia()){
				//aux = NULL;
				return NULL;
			}
			while(aux != NULL){
				if (elemento == aux->mDado){
					return aux;
				}
				aux = aux->mProximo;
			}
			return NULL;
		}
		
		No* getElement(dataType buscado){
			 
			return buscarNaLista(buscado);
		}
};


class node{
    friend class Tree234;
    private:
        lista keys;
        node* parent;
        node* children[CAPACIDADEFILHO];
        unsigned qtdFilhoAtual;
        bool isSheet;

        void cleanChild(){
            for(int i = 0; i < CAPACIDADEFILHO; i++){
                children[i] = NULL;
            }
        }
        // burst = explodiu 
        bool burst(){
            unsigned countKey = keys.getTamanho();
            cout << " qtd de key: " << countKey << " qtd maxima de key: " << CAPACIDADECHAVE << endl;
            return countKey == CAPACIDADECHAVE;
        }

    public:
        node(){
            this->parent = NULL;
            for(int i = 0; i < CAPACIDADEFILHO;i++)
                this->children[i] = NULL;
            
            this->isSheet = true;
        }

        node(dataType key){
            this->parent = NULL;
            this->keys.insereNaListaVazia(key);
            for(int i = 0; i < CAPACIDADEFILHO;i++)
                this->children[i] = NULL;
            //this->countKey = 1;
            this->isSheet = true;
        }

        ~node(){
            cleanChild();
            delete *children;
            delete parent;
        }
        void cleanKey(node* umNoh){
            
            umNoh->keys.~lista();
            
        }



};


class Tree234 {
    private:
        node* root;
    public: 
        Tree234(){
            root = NULL;
        }

        ~Tree234(){

        }
        /// @brief Função que dividi a lista de chaves caso atinja a capacidade maxima
        dataType split (node* raiz){
            node* temp = raiz;
            dataType left = temp->keys.removeNoInicio();
            dataType right = temp->keys.removeNoFim();
            dataType itemPromovido = temp->keys.removeNoInicio();
            /*cout << "dad: " << dad << endl;
            cout << "left: " << left << endl;
            cout << "right: " << right << endl;*/
            //delete root;
            temp->children[0] = new node(left);
            temp->children[1] = new node(right);
            temp->parent = new node(itemPromovido); temp->parent->isSheet = false;
            root = temp;
            //cout << "parent: " << temp->parent->keys[0] << endl;
            return itemPromovido;
        }


        void insereEmNohFolhaNaoCheio(node* oneNoh, dataType key){
            if(oneNoh->keys.listaVazia()){
                cout << "entrou na lista vazia..." <<endl;
                oneNoh->keys.insereNoInicio(key);
            }else if(key < oneNoh->keys.begin()){
                cout << "entrou na insere no inicio..." <<endl;
                oneNoh->keys.insereNoInicio(key);
            }else if(key > oneNoh->keys.ending()){
                cout << "entrou na insere no final..." <<endl;
                oneNoh->keys.insereNoFim(key);
            }else{
                cout << "entrou na insere no meio..." <<endl;
                oneNoh->keys.insereNaLista(key, MEIO);
            }
        
        }

        void insereEmNohIntermediarioNaoCheio(node* oneNoh,node*novoNoh, dataType itemPromovido){
            unsigned pos = oneNoh->keys.mTamanho - 1;
            //while(pos >= 0 and oneNoh->keys)
        }

        void insert(dataType key){
            if (root == NULL){
                root = new node(key);
            }else if(not root->burst()){ // se não estourou add chave
                insereEmNohFolhaNaoCheio(root, key);
                    
            }else{
                view();
                dataType itemPromovido = 0;
            
                itemPromovido = split(root);
                cout << "Item Promovido: " << itemPromovido << endl;
                //root = oneNoh;
                cout << "\n"<< key << " - [X]" << "Limite maximo de chaves alcançado..." << endl;
                /*Arrumar duplicidade de código*/
                if(key < root->parent->keys.begin()){ //Se nova chave for menor
                    //insere na esquerda
                    cout << "tenta dividir";
                    if(key < root->children[0]->keys.begin())
                        insereEmNohFolhaNaoCheio(root->children[0], key);
                }else{
                    // insere na direita
                    cout << "entrou na condição do filho a diretia." << endl;
                  if(key < root->children[1]->keys.begin())
                        insereEmNohFolhaNaoCheio(root->children[1], key);
                }
            }
        }

        void view(){
            cout << "[";
            
            root->keys.percorreLista();
         
            cout << "]";

        }

        void mostraFilho(){
            if(root->children != NULL){
                cout <<"\t";
                root->parent->keys.percorreLista();
                
                cout << "\n";
                root->children[0]->keys.percorreLista();
                cout << "\t\t";
                root->children[1]->keys.percorreLista();
            }    
            
            cout << endl;
        }
};

int main( )
{
    Tree234 ttf;
    int e;
    char start;
    do{
        cin >> start;
        switch(start){
            case 'i':
                cin >> e;               
                ttf.insert(e);
                break;
            case 'v':
                ttf.mostraFilho();
            break;
            case 'f':
                cout << "saindo...." << endl;
            break;
        }
        

    }while(start != 'f');
   
    

    ttf.view();
    cout << endl;

    
    /* code */
    //ttf.view();
    cout << endl;
    return 0;
}
