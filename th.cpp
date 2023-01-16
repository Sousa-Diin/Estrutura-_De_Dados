#include <iostream>
using namespace std;

typedef int Dado;

const int p = 37;
int espalhamento(unsigned key, Dado cap){
	int h = 0;
	return  h = (p * h + key % cap);
}

class noh {

friend class tabelaHash;
private:
  Dado valor;
  unsigned chave;
  noh *proximo = NULL;

public:
  noh();
  noh(Dado v, unsigned k);
  void view();
  Dado getValor(){
	 return valor; 
  }

  unsigned getChave(){
	  return chave;
  }
};

class tabelaHash{
	private:
		noh** tabela;
		unsigned capacidade;
		Dado tamanho;
	public:
		void insere(noh* elemento, unsigned key);
		tabelaHash(Dado cap);
		~tabelaHash();
		noh* recupera(unsigned key);
		void percorre();
		Dado getTamanho();

};
noh::noh(Dado v, unsigned k) {
  valor = v;
  chave = k;
  //proximo = NULL;
}

noh::noh(){
  valor = -1;
  chave = -1;
  //proximo = NULL;
}

void noh::view() {
  cout << "Valor: " << valor << "\t";
  cout << "Chave: " << chave << endl;
}

tabelaHash::tabelaHash(Dado cap){
	capacidade = cap;
	tabela = new noh*[capacidade];
	tamanho = 0;
	for (int p = 0; p < capacidade;p++){
		tabela[p] = NULL;
	}
}

tabelaHash::~tabelaHash(){
	
}

Dado tabelaHash::getTamanho(){
	return tamanho;
}

void tabelaHash::insere(noh* elemento, unsigned int key){
	unsigned mKey = elemento->getChave();
	Dado mValue = elemento->getValor();
	
	int hash = espalhamento(mKey, capacidade);
	if(recupera(mKey) == NULL){
		if(tabela[hash] == NULL ){
			tabela[hash] = new noh;
			tabela[hash]->valor = mValue;
			tabela[hash]->chave = mKey;
			tamanho++;
		}else{
			cout << "COLIDIU: " << mKey << endl;
            noh* atual = tabela[hash];

			while(atual != NULL){
				atual = atual->proximo;
			}
			noh* novo = new noh;
            novo->chave = mKey;
            novo->valor = mValue;
            atual->proximo = novo;
			tamanho++;
		}
	}else{
        cout << "O ITEM JÁ ESTÁ NA TABELA" << endl;
    }
}

noh* tabelaHash::recupera(unsigned key){
	int hash = espalhamento(key, capacidade);

	if(tabela[hash] != NULL and  tabela[hash]->chave == key){
		 
		return tabela[hash];
	}else{
        noh* atual = tabela[hash];
        
        while (atual != NULL and atual->chave != key){
            atual = atual->proximo;
        }

        if (atual != NULL and atual->chave == key){
            noh* resul = tabela[hash];
			return resul;
        }else{
            return NULL;
        }
    }
	
}

void tabelaHash::percorre(){
    noh* atual;
    cout << "!--------------------!" << endl;
    for (int i = 0; i < capacidade; ++i){
        cout << i << ":";
        atual = tabela[i];
        while (atual != NULL){
            cout << " {CHAVE:[" << atual->chave << "] VALOR:[" << atual->valor << "]} -->";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }
    cout << "!--------------------!" << endl;
}

int main() {

	
  noh *n = new noh(18, 69);
  n->view();
	cout << espalhamento(111,6) << endl;
	cout << espalhamento(221098,6) << endl;
	cout << espalhamento(9014,6) << endl;
	cout << espalhamento(69,6) << endl;
	cout << espalhamento(4,6) << endl;

	tabelaHash th(9);
	cout << "Tamanho da Hash: " << th.getTamanho() << endl;
	th.insere(n, n->getChave());
	th.insere(new noh(100,111), 111);
	th.insere(new noh(41,221098), 221098);
	th.insere(new noh(15,9014), 9014);
	th.insere(new noh(41,221098), 221098);
	th.insere(new noh(15,73), 73);
	cout << "Tamanho da Hash: " << th.getTamanho() << endl;
	th.percorre();
}
