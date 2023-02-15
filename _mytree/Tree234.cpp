#include<iostream>
using namespace std;

typedef int dataType;
const unsigned int sonMax = 4;
const unsigned int keyMax = 3;


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
        node* children[sonMax];
        unsigned countKey;
        void cleanChild(){
            for(int i = 0; i < sonMax; i++){
                children[i] = NULL;
            }
        }
        // burst = explodiu 
        bool burst(){
            unsigned countKey = keys.getTamanho();
            cout << " qtd de key: " << countKey << " qtd maxima de key: " << keyMax << endl;
            return countKey == keyMax;
        }

    public:
        node(){
            this->parent = NULL;
            for(int i = 0; i < sonMax;i++)
                this->children[i] = NULL;
            this->countKey = 0;
        }

        node(dataType key){
            this->parent = NULL;
            this->keys.insereNoInicio(key);
            for(int i = 0; i < sonMax;i++)
                this->children[i] = NULL;
            this->countKey = 1;
        }

        ~node(){
            cleanChild();
            delete *children;
            delete parent;
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
            dataType left = raiz->keys.removeNoInicio();
            dataType right = raiz->keys.removeNoFim();
            dataType dad = raiz->keys.removeNoInicio();
            raiz->keys.~lista();
            raiz->parent = new node(dad);
            raiz->children[0] = new node(left);
            raiz->children[1] = new node(right);
            return raiz;
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
                root = split(root);
                cout << key << " - [X]" << "Limite maximo de chaves alcançado..." << "Removendo inicio: " << root->keys.removeNoFim() << endl;
            }
        }

        void view(){
            cout << "[";
            root->keys.percorreLista();
            cout << "]";

            cout << (root->burst()) ? "Verdadeiro" : "Falso";
        }

        void mostraFilho(){
            int pos = 0;
            while(pos < sonMax){
                
                cout << root->children[pos++]->parent-><< "|";
            }
            cout << endl;
        }
};

int main( )
{
    Tree234 ttf;
    ttf.insert(40);
    ttf.insert(12);
    ttf.insert(68);
    ttf.insert(36);
    ttf.view();
    cout << endl;

    cout << "Nos filhos: ";
    ttf.mostraFilho();
    /* code */
    ttf.view();
    return 0;
}
