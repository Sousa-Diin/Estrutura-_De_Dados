//Pratica em tabela hash 13/01/23
#include<iostream>
using namespace std;


typedef int Dado;

class No {
	friend class lista;
	friend class tabelaHash;
	private:
		Dado mDado;
		Dado mRef = 1;
		No* mProximo;
	public:
		No(Dado value){
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

class lista {
	friend class tabelaHash;
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
		
		void insereNaListaVazia(Dado x){
			No* novo = new No(x);
			mInicio = novo;
			mFim = novo;
			mTamanho++;
		}
		
		void insereNoInicio(Dado x){
			
			if(listaVazia()){
				insereNaListaVazia(x);
			}else{
				No* novo = new No(x);
				novo->mProximo = mInicio;
				mInicio = novo;
				mTamanho++;
			}
			
		}
		
		void insereNoFim(Dado z){
			if (listaVazia()){
				insereNaListaVazia(z);
			}else{
				No* novo = new No(z);
				mFim->mProximo = novo;
				mFim = novo;
				mTamanho++;
			}
			
		}
		
		void insereNaLista(Dado v, unsigned pos){
			
			
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
			Dado posAux = 0;
			while(aux != NULL){
				cout << aux->mDado << " ";
				aux = aux->mProximo;
			}
			cout << endl;
		}
		
		void listar(){
			No*aux = mInicio;
			//int posAux = 0;
			//cout << "Listando..." << endl;
			
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
		
		Dado buscarNaLista(Dado elemento){
			No* aux = mInicio;
			if(listaVazia()){
				//aux = NULL;
				return -1;
			}
			while(aux != NULL){
				if (elemento == aux->mDado){
					return aux->getDado();
				}
				aux = aux->mProximo;
			}
			return -1;
		}
		
		/*No* getElement(Dado buscado){
			 
			return buscarNaLista(buscado);
		}*/
		
		string buscar(Dado chave){
			
			No* aux = mInicio;
			//Dado posAux = 0;
			while(aux != NULL){
				if(chave == aux->mDado){
					return "ENCONTRADO";
				}
				aux = aux->mProximo;
			}
			return "NAOENCONTRADO";
		}
};

class tabelaHash {
	private:
		unsigned mCapacidade;
		lista* mTabela; //vetor de lista
		unsigned int mTamanho;
		
		Dado calcularHash(Dado chave){
			return chave % mCapacidade;
		}
		
		lista* criarLista(){
			lista* mLista;
			return mLista;
		}
	
	public:
		tabelaHash(unsigned cap){
			mCapacidade = cap;
			mTabela = new lista[mCapacidade];
			mTamanho = 0;
		}
		
		tabelaHash(){
			mCapacidade = 7;
			mTabela = new lista[mCapacidade];
			mTamanho = 0;
		}
		
		unsigned getTamanho(){
			return mTamanho;
		}
		
		unsigned getCapacidade(){
			return mCapacidade;
		}
		
		void insereElemento(No valor, Dado chave){
			Dado posicao = calcularHash(chave);
			lista* l = criarLista();
			
			mTabela[posicao]= *l;
			
			if(l->buscar(valor.mDado) == "NAOENCONTRADO"){
				l->insereNoFim(valor.mDado);
				mTamanho++;
			}
			else{
				cerr << "ITEM JÁ ESTÁ NA TABELA!" << endl;
				cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
			}
			
			//cout << posicao << ":\t";
			mTabela[posicao].listar();
		}
		
		bool buscarChave(Dado chave){
			Dado posicao = calcularHash(chave);
			if(chave == mTabela[posicao].buscarNaLista(chave)){
				return true;
			}
			return false;
		}
};

int main(){
	tabelaHash* t_hash = new tabelaHash(5);
	cout << " Tamanho da Tabela Hash: " << t_hash->getTamanho() << endl;
	cout << " Capacidade da Tabela Hash: " << t_hash->getCapacidade() << endl;
	
	No* novo = new No(18);
	t_hash->insereElemento(*novo, novo->getDado());
	*novo = 25;
	t_hash->insereElemento(*novo, novo->getDado());
	*novo = 27;
	t_hash->insereElemento(*novo, novo->getDado());
	/**novo = 21;
	t_hash->insereElemento(*novo, novo->getDado());
	*novo = 3;
	t_hash->insereElemento(*novo, novo->getDado());
	*/
	cout << " Tamanho da Tabela Hash: " << t_hash->getTamanho() << endl;
	Dado buscado;
	cout << "entre com achave para busca: ";
	cin >> buscado;
	
	if (t_hash->buscarChave(buscado) == true){
		cout << "Elemento encontrado." << endl;
	}else{
		cout << "Elemento não encontrado." << endl;
	}
	//cout << t_hash->buscarChave(buscado) << endl;
	return 0;
}
