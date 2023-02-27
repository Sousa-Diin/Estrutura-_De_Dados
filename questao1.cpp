#include <iostream>

using namespace std;

//const int UMPRIMO = 37;


int funcaoHash(int s, int M) {
   
    
    return s % M;
}

class noh{
friend class tabelaHash;
private:
    int chave;
    int valor;
    noh* proximo = NULL;
public:
    noh();
};

class tabelaHash{
private:
    noh** elementos;
    int capacidade;
	int tamanho;
public:
    tabelaHash(int cap = 101);
    ~tabelaHash();
    void insere(int chave, int valor);
    int recupera(int chave);
    void altera (int chave, int valor);
    void remove (int chave);
    void percorre ();
	int getTamanho();
};

noh::noh(){
    chave = -1;
    valor = -1;
}

tabelaHash::tabelaHash(int cap){
    elementos = new noh*[cap];
    capacidade = cap;
	tamanho = 0;
    for (int i = 0; i < cap; i++){
        elementos[i] = NULL;
    }
}

tabelaHash::~tabelaHash(){
    for (int i = 0; i < capacidade; ++i){
        noh* atual = elementos[i];
        while(atual != NULL){
            noh* aux = atual;
            atual = atual->proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

void tabelaHash::insere(int chave, int valor){
    int hash = funcaoHash(chave,capacidade);
    if (recupera(chave) == -1){
        if (elementos[hash] == NULL){
            elementos[hash] = new noh;
            elementos[hash]->chave = chave;
            elementos[hash]->valor = valor;
			tamanho++;
        }else{
            cout << "COLIDIU: " << chave << endl;
            
			while(elementos[hash]->proximo != NULL){
            	
				if(elementos[hash]->chave == -1){
					
				}
				elementos[hash] = elementos[hash]->proximo;
           	}
			
            noh* novo = new noh;
            novo->chave = chave;
            novo->valor = valor;
            elementos[hash]->proximo = novo;
			tamanho++;
        }
    }else{
        //cout << "O ITEM JÁ ESTÁ NA TABELA" << endl;
    }
}

int tabelaHash::recupera(int chave){
    int hash = funcaoHash(chave,capacidade);
    if (elementos[hash] != NULL and elementos[hash]->chave == chave){
        return elementos[hash]->valor;
    }else{
        noh* atual = elementos[hash];
        
        while (atual != NULL and atual->chave != chave){
            atual = atual->proximo;
        }

        if (atual != NULL and atual->chave == chave){
            return atual->valor;
        }else{
           return -1;
        }
    }

}

void tabelaHash::altera(int chave, int valor){
    int hash = funcaoHash(chave,capacidade);
    if (elementos[hash] != NULL and elementos[hash]->chave == chave){
        elementos[hash]->valor = valor;
    }else{
        noh* atual = elementos[hash];
        while(atual != NULL and atual->chave != chave){
            atual = atual->proximo;
        }
        if (atual != NULL and atual->chave == chave){
            atual->valor = valor;
        }else{
            cerr << "ERRO NA ALTERAÇÃO" << endl;
        }
    }
}

void tabelaHash::remove(int chave){
    int hash = funcaoHash(chave,capacidade);
    if (elementos[hash] != NULL and elementos[hash]->chave == chave){
        noh* aux = elementos[hash];
        elementos[hash] = elementos[hash]->proximo;
        delete aux;
    } else {
        noh* atual = elementos[hash];
        noh* anterior;
        while (atual != NULL and atual->chave != chave){
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual != NULL and atual->chave == chave){
            anterior->proximo = atual->proximo;
            delete atual;
        } else {
            //cerr << "ERRO NA REMOÇÃO" << endl;
        }
    }
}

void tabelaHash::percorre(){
    noh* atual;
   // cout << "!--------------------!" << endl;
    for (int i = 0; i < capacidade; ++i){
        //cout << i << ":";
        atual = elementos[i];
        while (atual != NULL){
            cout <<  atual->valor << " ";
            atual = atual->proximo;
        }
        //cout << "NULL" << endl;
    }
}

int main(){
    tabelaHash th, thA;
	int i = 0, v, re, re1;
	while(i < 10){
		cin >> v;
		th.insere (v,v);
		i++;
	}
   
	i = 0;
	while(i < 3){
		cin >> v;
		th.remove(v);
		i++;
	}
	i =0;
	//cout << endl;
	//th.percorre(); 
	while(i < 2){
		cin >> v;
		re = th.recupera(v);
		if(re != -1){
			re = 1;
		}
		cout << re << endl;
		
		i++;
	}
	
	th.percorre(); 
	i =0;
	thA = th;
	while(i < 3){
		
		cin >> v;
		th.insere(v,v);
		i++;
	}
    //th.remove (55);
	
    //thA.percorre();
	
    
    
    return 0;
}
