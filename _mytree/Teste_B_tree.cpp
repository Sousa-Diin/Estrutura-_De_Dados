#include<iostream>
#include<string>
#include "B_tree.hpp"

using namespace std;
void menu();
void processa_dado(page& p, char op);


int main(){
    cout << "Ordenacão externa!" << endl;

    char op;
    page p1;
    
    do{
        menu();
        cin >> op;
        processa_dado(p1, op);
        cout << "voltou para loop.\n";
    }while(op != 's');
    
    cout << "saiu do loop..\n";
    return 0;
}

void menu(){
    
    cout << "\ni - insere um node na pagina." << "\n"
         << "e - insere em lugar especifico da page." << "\n"
         << "r - remove no final da page." << "\n"
         << "d - remove no inicio da page." << "\n"
         << "a - altera dados da page." << "\n"
         << "v - visializar dados da page." << "\n"
         << "s - sair da execucão do sistema." << "\n"
         << endl;
}

void processa_dado(page& p, char op){
    int dado, pos = -1;
    switch (op)
    {
    case 'i':

        cout << "insere normal" << "\n";
        cin >> dado;
        people a;
        a.insert("Wildes Sousa", 28);
        
        //p(&a);
        //p1("Eliane Aparecida",29);
        cout << endl;
        break;
    case 'e':
        cout << "insere em lugar especifico" << "\n";
        cin >> dado >>
                pos;
       
        break;
    case 'r':
        cout << "remove no fim. " << "\n";
        cin >> dado;

        break;
    case 'd':
        cout << "remove no inicio" << "\n";
        cin >> dado;
        
        break;
    case 'a':
        cout << "altera dados" << "\n";
        cin >> dado;

        break;
    case 'v':
        cout << "visualiza dados..." << "\n";
        p.view_people();
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