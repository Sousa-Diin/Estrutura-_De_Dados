#include <iostream>
using namespace std;

void menu(){
    char op;

    while(cin >> op and op != 'f'){
        
        switch(op){
            case 'i':
                cout << "para inserir uma chave\n";
                break;
            case 'e':
                cout << "para escrever o conteúdo da árvore\n";
                break;
            case 's':
                cout << "para escrever todos os sucessores de uma chave\n";
                break;
            case 'f':
                cout << "para finalizar a execução do programa\n";
                break;

        }
    }
}
