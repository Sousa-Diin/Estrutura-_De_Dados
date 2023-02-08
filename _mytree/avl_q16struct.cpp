/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa dado na forma chave/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>

using namespace std;

struct dado {
    unsigned chave;
    string nome;
    unsigned long long int cpf;
};


ostream& operator<<(ostream& saida, const dado& e) {
    saida << "Nome: " << e.nome << " | CPF: "  << e.cpf <<  " | Cod: " << e.chave ;
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.chave >> e.nome >> e.cpf;
    return entrada;
}

typedef unsigned int tipoChave; // tipo da chave usada na comparação


class noh {
    friend class avl;
    private:
        dado elemento;
        noh* left;
        noh* right;
        unsigned height;
        int rightCount;
        int leftCount;
    public:
        noh(const dado& umDado):
            elemento(umDado),  left(NULL), right(NULL), height(1) { }
        ~noh() { }
        int fatorBalanceamento();
        unsigned getHeight(){
            return height;
        }
};

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        void imprimeAutorizadosAux(noh* atual, bool impar);
        
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* umNoh, tipoChave chave);
        // métodos para manutenção do balanceamento
        
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* node);
        void imprimirEsq(const std::string& prefixo, const noh* node, bool temIrmao);
        int height(noh* node);
        int getBalance(noh* node);
        noh* rightRotate(noh* current);
        noh* leftRotate(noh* current);
        // funções auxiliares para remoção
        
        noh* removeSmaller(noh* rootSub);
        noh* miniAux(noh* rootSubTree);
        void updateHeight(noh* currenty);
        unsigned getHeight(noh* current);
        unsigned maxheight(unsigned rightHeight, unsigned leftHeight);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void remove(tipoChave chave);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        void imprimeAutorizados(int dia);
        bool verificaAutorizado(tipoChave chave, int dia);
        dado minimo();
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    //#WARNING implemente
}

/// @brief node height catch 
/// @param currenty node
/// @return the current node height 
unsigned avl::getHeight(noh* currenty){
    if(!currenty){
        return 0;
    }
    return currenty->height;
}
/// @brief Function that update the node height
/// @param current current node
void avl::updateHeight(noh* current){
    unsigned rightHeight = getHeight(current->right);
    unsigned leftHeight = getHeight(current->left);
    current->height = 1 + maxheight(leftHeight, rightHeight);
}
/// @brief Function that verify the maximum param of height 
/// @param rightHeight right height
/// @param leftHeight left height
/// @return maximum height
unsigned avl::maxheight(unsigned rightHeight, unsigned leftHeight){
    if(leftHeight >= rightHeight){
        return leftHeight;
    }
    return rightHeight;
}

void avl::insere(const dado& umDado) {
    
    raiz = insereAux(raiz, umDado);
}


int avl::height(noh* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários

int avl::getBalance(noh* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore

noh* avl::rightRotate(noh* current) {
    noh* swap = current->left;
    noh* subtreeRight = swap->right;
    swap->right = current;
    current->left = subtreeRight;
    current->height = max(height(current->left), height(current->right)) + 1;
    swap->height = max(height(swap->left), height(swap->right)) + 1;
    return swap;
}

// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore

noh* avl::leftRotate(noh* current) {
    noh* swap = current->right;
    noh* subtreeLeft = swap->left;
    swap->left = current;
    current->right = subtreeLeft;
    current->height = std::max(height(current->left), height(current->right)) + 1;
    swap->height = std::max(height(swap->left), height(swap->right)) + 1;
    return swap;
}


// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* node, const dado& key) {
  if (node == NULL)
            return new noh(key);
        if (key.chave < node->elemento.chave){
            node->left = insereAux(node->left, key);
            updateHeight(node->left);
            node->leftCount++;
        }else if (key.chave > node->elemento.chave){
            node->right = insereAux(node->right, key);
            updateHeight(node->right);
            node->rightCount++;
        }else
            return node;
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);
        if (balance > 1 && key.chave < node->left->elemento.chave)
            return rightRotate(node);
        if (balance < -1 && key.chave > node->right->elemento.chave)
            return leftRotate(node);
        if (balance > 1 && key.chave > node->left->elemento.chave) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key.chave < node->right->elemento.chave) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
   noh* atual = raiz;
    while (atual != NULL) {
        if (atual->elemento.chave == chave) {
            return atual;
        } else if (chave < atual->elemento.chave ) {
            atual = atual->left;
        } else {
            atual = atual->right;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
dado avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}


// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeSmaller(noh* rootsub){
    if (rootsub->left == NULL) {
        return rootsub->right;
    } else {
        rootsub->left =  removeSmaller(rootsub->left);
    return rootsub;
    } 

}

noh* avl::miniAux(noh* rootSubTree){
    while (rootSubTree->left != NULL) {
        rootSubTree = rootSubTree->left;
    }
    return rootSubTree;
}
// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
dado avl::minimo(){
    if (raiz == NULL) {
        
    }
    noh* nohMinimo = miniAux(raiz);
    return nohMinimo->elemento;
    
}
// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* oneNo, tipoChave value){
   if (oneNo == NULL){
        std::cout << "ERRO: ";
   }
    noh* subTree = oneNo;
    // valor menor que nó atual, vai para subárvore esquerda
    if ( value < oneNo->elemento.chave ) {
    oneNo->left = removeAux(oneNo->left, value);
    // valor maior que nó atual, vai para subárvore direita
    }else if( value > oneNo->elemento.chave ) {
    oneNo->right = removeAux(oneNo->right, value);
   
    } else{ 
        // nó não tem filhos à esquerda
        if (oneNo->left == NULL) {
            subTree = oneNo->right;
        // nó não tem filhos à direita
        } else if (oneNo->right == NULL) {
            subTree = oneNo->left;
        } else { 
            subTree = miniAux(oneNo->right);
            subTree->right = removeSmaller(oneNo->right); 
            subTree->left = oneNo->left;
        }
        delete oneNo;

    }
   
    return subTree;
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::imprimeAutorizadosAux(noh* atual, bool impar) {
    //#WARNING implemente
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::imprimeAutorizados(int dia) {
    imprimeAutorizadosAux(this->raiz, dia % 2);
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
bool avl::verificaAutorizado(tipoChave chave, int dia) {
   // #WARNING implemente
   return false;    
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
void avl::percorreEmOrdemAux(noh* atual, int nivel) {
  if(atual != NULL){
    percorreEmOrdemAux(atual->left, nivel+1);

    percorreEmOrdemAux(atual->right, nivel+1);
  }
}


ostream& operator<<(ostream& output, avl& arvore) {
    // arvore.percorreEmOrdemAux(arvore.raiz,0);
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* node)
{
    if( node != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << node->elemento.chave << "," << node->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , node->left , node->right==nullptr );
        imprimirDir( prefixo + "    " , node->right );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* node, bool temIrmao)
{
    if( node != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << node->elemento.chave << "," << node->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , node->left, node->right==nullptr );
        imprimirDir( prefixo + "│   " , node->right );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.chave << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->left, this->raiz->right==nullptr );
        imprimirDir( " " , this->raiz->right );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

int main() {
    avl arvore;
    tipoChave chave;
    dado umDado;
    int dia = 0;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, quantidade, valor
                    std::cin >> umDado.chave;
                    std::cin >> umDado.nome;
                    std::cin >> umDado.cpf;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.remove(chave);
                    break;
                case 'b': // Buscar
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever o valor
                    cout << umDado << endl;
                    break;
                case 'e': // Escrever arvore no formato tree
                    cout << arvore ;
                    break;
                case 'l': // lista os autorizados 
                    cin >> dia;
                    arvore.imprimeAutorizados(dia);
                    break;     
                case 'v': // Verifica se funcionario esta autorizado
                    cin >> chave >> dia;
                    if ( arvore.verificaAutorizado(chave, dia) )
                        cout << "Autorizado." << endl;
                    else
                        cout << "Não autorizado." << endl;
                    break;     
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}