//Hash Encadeado
#include<iostream>
using namespace std;

#define CAPACITY 11;

unsigned calculaHash (int key){
	return key % CAPACITY;
}


void createHash(unsigned cap){
	capacity = cap;
	tabela = new lista[capacity];
}

int main(){

	cout << "Chave: 34  posicão: " <<  calculaHash(34) << endl;
	cout << "Chave: 46  posicão: " <<  calculaHash(46) << endl;
	cout << "Chave: 101  posicão: " <<  calculaHash(101) << endl;
	cout << "Chave: 85 posicão: " <<  calculaHash(85) << endl;
	cout << "Chave: 55  posicão: " <<  calculaHash(55) << endl;
	cout << "Chave: 13  posicão: " <<  calculaHash(13) << endl;
	cout << "Chave: 96  posicão: " <<  calculaHash(96) << endl;

	return 0;
}

