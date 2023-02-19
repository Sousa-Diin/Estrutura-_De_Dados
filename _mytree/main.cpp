#include<iostream>
#include<string>
#include "lista.hpp"

using namespace std;
void menu();
void processa_dado(lista& ll, char op);


int main(){
    cout << "Ordenacão externa!" << endl;

    char op;
    lista l;
    
    do{
        menu();
        cin >> op;
        processa_dado(l, op);
        cout << "voltou para loop.\n";
    }while(op != 's');
    
    cout << "saiu do loop..\n";
    return 0;
}

void menu(){
    
    cout << "\ni - insere na lista." << "\n"
         << "e - insere em lugar especifico da lista." << "\n"
         << "r - remove no final da lista." << "\n"
         << "d - remove no inicio da lista." << "\n"
         << "a - altera dados da lista." << "\n"
         << "v - visializar dados da lista." << "\n"
         << "s - sair da execucão do sistema." << "\n"
         << endl;
}

void processa_dado(lista& ll, char op){
    int dado, pos = -1;
    switch (op)
    {
    case 'i':

        cout << "insere normal" << "\n";
        cin >> dado;
        No* search;
        ll.insereNoInicio(dado);
        cout << endl;
        break;
    case 'e':
        cout << "insere em lugar especifico" << "\n";
        cin >> dado >>
                pos;
        ll.insereNaLista(dado, pos);
        break;
    case 'r':
        cout << "remove no fim. " << "\n";
        cin >> dado;
        ll.removeNoFim();
        break;
    case 'd':
        cout << "remove no inicio" << "\n";
        cin >> dado;
        ll.removeNoInicio();
        break;
    case 'a':
        cout << "altera dados" << "\n";
        cin >> dado;
        search = ll.buscarNaLista(dado);
        if(search != NULL){
            cout << search->getRef() << endl;
            cout << search->getDado() << endl;
        }else{
            cout << "Me desculpe elemento não encontrado!" << endl;
        }
        break;
    case 'v':
        cout << "visualiza dados..." << "\n";
        ll.percorreLista();
        break;
    case 's':
        cout << "saindo do sistema..." << "\n";
        break;
    
    default:
        cout << "opcao invalida.";
        break;
    }
    //return ll.percorreLista();
}