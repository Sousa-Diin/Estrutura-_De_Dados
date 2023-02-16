#include<iostream>
using namespace std;

typedef int dataType;
const unsigned int capacidadeFilho = 4;
const unsigned int capacidadeChave = 3;


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
				insereNaListaVazia(v);
				mTamanho++;
			}else{
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
        node* children[capacidadeFilho];
        unsigned qtdFilhoAtual;
        bool isSheet;

        void cleanChild(){
            for(int i = 0; i < capacidadeFilho; i++){
                children[i] = NULL;
            }
        }
        // burst = explodiu 
        bool burst(){
            unsigned countKey = keys.getTamanho();
            cout << " qtd de key: " << countKey << " qtd maxima de key: " << capacidadeChave << endl;
            return countKey == capacidadeChave;
        }

    public:
        node(){
            this->parent = NULL;
            for(int i = 0; i < capacidadeFilho;i++)
                this->children[i] = NULL;
            
            this->isSheet = true;
        }

        node(dataType key){
            this->parent = NULL;
            this->keys.insereNaListaVazia(key);
            for(int i = 0; i < capacidadeFilho;i++)
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
        node* split (node* raiz){
            node* temp = raiz;
            dataType left = temp->keys.removeNoInicio();
            dataType right = temp->keys.removeNoFim();
            dataType dad = temp->keys.removeNoInicio();
            /*cout << "dad: " << dad << endl;
            cout << "left: " << left << endl;
            cout << "right: " << right << endl;*/
            delete raiz;
            temp->children[0] = new node(left);
            temp->children[1] = new node(right);
            temp->parent = new node(dad); temp->parent->isSheet = false;
            //cout << "parent: " << temp->parent->keys[0] << endl;
            return temp;
        }

        void insert(dataType key){
            if (root == NULL){
                root = new node(key);
            }else if(not root->burst() and root->keys.getTamanho()){ // se não estourou add chave
            
                if(key < root->keys.begin()){
                    root->keys.insereNoInicio(key);
                }else{
                    root->keys.insereNoFim(key);
                }
                    
            }else{
                view();
                root = split(root);
                //cout << key << " - [X]" << "Limite maximo de chaves alcançado..." << endl;
                /*Arrumar duplicidade de código*/
                if(key < root->parent->keys.begin()){
                    //insere na esquerda
                    if(key < root->children[0]->keys.begin())
                        root->children[0]->keys.insereNoInicio(key);
                    root->children[0]->keys.insereNoFim(key);
                }else{
                    // insere na direita
                    cout << "entrou na condição do filho a diretia." << endl;
                    if(key < root->children[1]->keys.begin())
                        root->children[1]->keys.insereNoInicio(key);
                    root->children[1]->keys.insereNoFim(key);
                }
                
            }
        }

        void view(){
            cout << "[";
            
            root->keys.percorreLista();
         
            cout << "]";

        }

        void mostraFilho(){
                
            cout <<"\t";
            root->parent->keys.percorreLista();
            
            cout << "\n";
            root->children[0]->keys.percorreLista();
            cout << "\t\t";
            root->children[1]->keys.percorreLista();
            
            
            cout << endl;
        }
};

int main( )
{
    Tree234 ttf;
    ttf.insert(40);
    ttf.insert(12);
    ttf.insert(60);
    ttf.insert(68);
    ttf.insert(36);
    ttf.insert(38);
    //ttf.insert(60);
    ttf.insert(48);
    //ttf.view();
    cout << endl;

    ttf.mostraFilho();
    /* code */
    //ttf.view();
    cout << endl;
    return 0;
}
