#include<iostream>
using namespace std;

typedef int dataType;

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
            }else if(pos >= mTamanho){
                cout << "posicão não existe." << endl;
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
