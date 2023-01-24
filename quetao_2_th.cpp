#include <iostream>
#include <string.h>
#include <cstring>
#include <string>
using namespace std;

typedef string Dado;
/* PARA TESTES
5
Casa Edifício de formatos e tamanhos variados, ger. de um ou dois andares, quase sempre destinado à habitação.
Aniversário Diz-se de ou dia em que se completa um ou mais anos em que se deu determinado acontecimento.
Carta Mensagem, manuscrita ou impressa, a uma pessoa ou a uma organização, para comunicar-lhe algo.
Exonerado  Libertar ou libertar-se de uma obrigação ou de um dever.
Concomitantemente Que acompanha ou coexiste. Que acontece ou se faz ao mesmo tempo.
Carta
Casa
Boneca
-1
*/

int fhash(Dado str, unsigned cap); // gera a chave hash


class noh {
  friend class lista;
  friend class thash;

private:
  Dado chave;
  Dado valor;
  noh *proximo;

public:
  noh(Dado mValor, Dado mChave);
  noh();
  Dado getValor();
  Dado getChave();
};

noh::noh(Dado mValor, Dado mChave) {
  valor = mValor;
  chave = mChave;
  proximo = NULL;
}
Dado noh::getValor() { 
	return valor;
}
Dado noh::getChave() { 
	return chave;
}
noh::noh(){
  valor = " ";
  chave = " ";
  proximo = NULL;
}

class lista {
private:
  noh *fim;
  noh *inicio;
  int tamanho;
  bool listaVazia();
  void insereNoFim(Dado valor, Dado chave);
  void insereListaVazia(Dado valor, Dado chave);
  //Dado gerarChave(Dado &no);// Gera e retorna a chave, e retorna por parametro o valor


public:
  lista();
  ~lista();
  void insereNaLista(Dado valor, Dado chave);
  void percorreLista();
  int getTamanho();
  noh* removeNaLista(Dado chave); 
  noh* buscaNaLista(Dado chave);
  lista(const lista& umaLista);
};

lista::lista(){
	inicio = NULL;
	fim = NULL;
	tamanho = 0;
}

/*lista::lista(const lista& umaLista){
	cout << "Contrutor de copia" << endl;
	inicio = umaLista.inicio;
	fim = umaLista.fim;
	tamanho = umaLista.tamanho;
}*/

lista::~lista(){
	
}
void lista::insereNoFim(Dado valor, Dado chave){
	noh* novo = new noh(valor, chave);

	fim->proximo = novo;
	fim = novo;
	tamanho++;
}
bool lista::listaVazia(){
	return getTamanho() == 0;
}
void lista::insereListaVazia(Dado valor, Dado chave){
	if (listaVazia()){
		noh* novo = new noh(valor, chave);
		inicio = novo;
		fim = novo;
		tamanho++;
	}else{
		insereNoFim(valor, chave);
	}
	
}
int lista::getTamanho(){
	return tamanho;
}

void lista::insereNaLista(Dado valor, Dado chave){
	insereListaVazia(valor, chave);
}

void lista::percorreLista(){
	noh* aux = inicio;
	while(aux != NULL){
		cout << aux->getValor() << "\n";
		aux = aux->proximo;
	}
	cout << endl;
}

noh* lista::buscaNaLista(Dado chave){
	noh* buscado = inicio;
	while(buscado != NULL){
		if(buscado->getChave() == chave){
			return new noh(buscado->getValor(),buscado->getChave());
		}
		buscado = buscado->proximo;
	}
	return NULL;
}


class thash {
private:
  int tamanho;
  int capacidade;
  lista* tabela;
  Dado gerarChave(Dado &no);// Gera e retorna a chave, e retorna por parametro o valor

public:
	thash(int cap);
	~thash();
	void insereElemento(Dado elemento);
	void remove(Dado chave);
	int getTamanho();
	int getCap();
	bool tHashVazia();
    noh* busca(Dado chave);
	string recupera(string chave);
	void percorreHash();
  
};
thash::thash(int cap){
	capacidade = cap;
	tabela = new lista[cap];
	tamanho = 0;
	/*for(int i = 0; i < cap; i++){
		tabela[i] = NULL;
	}*/
}
thash::~thash(){
	delete [] tabela;
}

void thash::insereElemento(Dado elemento){
	
	Dado chave = gerarChave(elemento);
	int nhash = fhash(chave, capacidade);
	
	//cout << "[Chave gerada]: " << chave << " [Valor gerado]: " << elemento << endl;
	//cout << "hash gerada: " << nhash << endl;

	lista* nova;	
	
	if (tabela[nhash].buscaNaLista(chave) == NULL){
	    tabela[nhash].insereNaLista(elemento, chave);
		nova = &tabela[nhash];
		tamanho++;
    }else{
		cout << "Tamanho da Th dentro da funcao: " << tamanho << endl;
		cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
	}
}

int thash::getTamanho(){
	return tamanho;
}

int thash::getCap(){
	return capacidade;
}

bool thash::tHashVazia(){
	return  getTamanho() == 0;
}
void thash::remove(Dado chave){
	
}
noh* thash::busca(Dado chave){
	if(tHashVazia()){
		cout << "ERRO: 'Tabela Vazia'" << endl;
	}else{
		int nhash = fhash(chave, capacidade);
		noh* elemento = tabela[nhash].buscaNaLista(chave);
		if(elemento == NULL){
			cout << "ITEM NÃO ENCONTRADO" << endl;
		}else{
			return elemento;
		}
	}
	return NULL;
}

void thash::percorreHash(){
		cout << "_______________________________________________________________\n";
	for(int i = 0; i< capacidade; i++){
		cout << "Posição " << i << ": ";
		tabela[i].percorreLista();
		cout << endl;
		//tam += thash->getTamanho();
	}
	cout << "\n_______________________________________________________________\n";
}
Dado thash::gerarChave(Dado &no){ 
	int tam = no.length();
	Dado  rfrase;
	
	char frase[tam];
	char* palavra;
	string str;
	
	for (int i = 0; i < tam;i++){
		 frase[i] = no[i];
		
	}
	
	//memcpy (frase, no, (sizeof(no)+1));
	
	int j = 0;
	for (int i = 0; i < tam;i++){
		if (frase[i] != ' '){
			j++;
		}else{
			i = tam;
		}
	}	
	palavra = new char[j];
	no.erase(0, j+1);
	 strncat (palavra, frase, j);
	//cout << "primeira frase: " << palavra << endl;
	return palavra;

}
/****** Prototipo funcoes auxiliares********/
 
lista fteste(thash &l); // Uso didatico 


/******FUNCAO MAIN******/
int main(){
	
	thash th(23);
	lista p_buscada = fteste(th);
	cout << "\n\nPalavras buscadas: " << "\n";
		  p_buscada.percorreLista();

	cout << "Impressão da Tabela Hash:\\n  "<< endl;
	th.percorreHash();
	/*
	Dado mElemento;
	cout << "Capacidade  " << th.getCap() << endl;
	cout << th.getTamanho() << endl;
	getline(cin, mElemento);
	th.insereElemento(mElemento);
	cout << "saiu da funcao inserir " << endl;
	th.busca("Aniversário");
	
	cout << th.getTamanho() << endl;
	//Aniversário Diz-se de ou dia em que se completa um ou mais anos em que se deu determinado acontecimento.
	th.percorreHash();
	*/
	return 0;
}	

lista fteste(thash &th){
	int  qtd, i = 0;
	string palavra,
		   busca, 
		   buscado;
	cin >> qtd;
	
	while(i <= qtd){
		cin.ignore();
		getline(cin, palavra);
		th.insereElemento(palavra);
		i++;
	}

	lista nova;
	bool run = true;
	while(palavra!= "-1" and run){
		Dado chave,valor;
		getline(cin, palavra);
		bool condicao = chave == palavra;
		
		if(palavra != "-1"){
		
			chave = th.busca(palavra)->getChave();
			valor = th.busca(palavra)->getValor();
		
		}else{
			run = false;
		}
		cout <<"[" << chave <<"] => " << condicao ? valor : "NULL";
	}
	return nova; // retorna uma lista das palavras buscadas
}

int fhash(Dado str, unsigned cap){
	int tstr = str.length(), checksum = 0;
	char c = ' ';
	for (int i = 0; i < tstr; i++){
		c = str[i];
		checksum += c;
	}
	return checksum % cap;
}
