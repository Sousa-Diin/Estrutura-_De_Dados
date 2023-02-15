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
		
		int getDado(){
			return mDado;
		}
		
		int getRef(){
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
	public:
		lista(){
			mTamanho = 0;
			mInicio = NULL;
			mFim = NULL;
		}
		
		~lista(){
			
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
			cout << endl;
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
        dataType keys[keyMax];
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
            this->keys[0] = key;
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
        /// @brief Função que dividi o vetor de chaves qcaso atinja a capacidade maxima
        void split (){
            
        }

        void insert(dataType key){
            if (root == NULL){
                root = new node(key);
            }else if(not root->burst()){
            
                root->keys[root->countKey++] = key;
            }else{
                cout << key << " - [X]" << "Limite maximo de chaves alcançado..." << endl;
            }
        }

        void view(){
            cout << "[";
            for(int i = 0; i < keyMax; i++)
               cout << root->keys[i] << " ";
            cout << "]";

            cout << (root->burst()) ? "Verdadeiro" : "Falso";
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
    /* code */
    return 0;
}
