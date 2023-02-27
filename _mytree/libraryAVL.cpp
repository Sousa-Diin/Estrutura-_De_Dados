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
using namespace std;
#include <stdexcept>

typedef string tipoChave;

struct dado {
    unsigned chave;
    string nomeLivro;
    string localizacao;
    int quantidadeDisponivel;
};

ostream& operator<<(ostream& saida, const dado& e) {
    saida << "(" << e.chave << "," << e.nomeLivro << "," << e.localizacao << "," << e.quantidadeDisponivel << ")";
    return saida;
}

istream& operator>>(istream& entrada, dado& e) {
    entrada >> e.chave >> e.nomeLivro >> e.localizacao >> e.quantidadeDisponivel;
    return entrada;
}

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
};

int noh::fatorBalanceamento() {
    cout << "#WARNING implemente" << endl;
    return 0;
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        void percorreEmOrdemAux(noh* atual, int nivel);
        
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const dado& umDado);
        noh* removeAux(noh* oneNo, tipoChave value);
     
        // busca, método iterativo
        noh* buscaAux(tipoChave chave);
        noh* buscaAuxlocale(tipoChave chave);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);
        int levantamentoAux(noh* umNoh, string local);
        int height(noh* node);
        int getBalance(noh* node);
        noh* rightRotate(noh* current);
        noh* leftRotate(noh* current);
        // funções auxiliares para remoção
        
        noh* removeSmaller(noh* rootSub);
        noh* miniAux(noh* rootSubTree);
        
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();
        // inserção e remoção são recursivos
        void insere(const dado& umDado);
        void removeRec(tipoChave chave);
        dado minimo();
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        dado busca(tipoChave chave);
        dado buscaLocale(tipoChave chave);
        // efetua levantamento de quantos livros existem em um dado local
       int levantamento(string local);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    cout << "#WARNING implemente destrutor" << endl;
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
            node->leftCount++;
        }else if (key.chave > node->elemento.chave){
            node->right = insereAux(node->right, key);
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
        if (atual->elemento.nomeLivro == chave) {
            return atual;
        } else if (chave < atual->elemento.nomeLivro ) {
            atual = atual->left;
        } else {
            atual = atual->right;
        }
    }
    return atual;
}

noh* avl::buscaAuxlocale(tipoChave chave) {
    noh* atual = raiz;
    while (atual != NULL) {
        if (atual->elemento.localizacao == chave) {
            return atual;
        } else if (chave < atual->elemento.localizacao ) {
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
dado avl::buscaLocale(tipoChave chave) {
    noh* resultado = buscaAuxlocale(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}
int avl::levantamentoAux(noh* umNoh, tipoChave local){
    int qtd = 0;
    if(umNoh != NULL){
        levantamentoAux(umNoh->left, local);
        while(local == umNoh->elemento.localizacao){
            qtd += umNoh->elemento.quantidadeDisponivel;
        }  
        levantamentoAux(umNoh->right, local);
    }

    return qtd;
}

int avl::levantamento(string local){
    
    return levantamentoAux(raiz, local);
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
void avl::removeRec(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* oneNo, tipoChave value){
   if (oneNo == NULL){
        std::cout << "ERRO: ";
   }
    noh* subTree = oneNo;
    // valor menor que nó atual, vai para subárvore esquerda
    if ( value < oneNo->elemento.nomeLivro ) {
    oneNo->left = removeAux(oneNo->left, value);
    // valor maior que nó atual, vai para subárvore direita
    }else if( value > oneNo->elemento.nomeLivro ) {
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
void avl::percorreEmOrdemAux(noh* atual, int nivel) {
    if(atual != NULL){
        percorreEmOrdemAux(atual->left, nivel);
        percorreEmOrdemAux(atual->right, nivel);

    }

}

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != NULL )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.nomeLivro << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->left , meuNoh->right==NULL );
        imprimirDir( prefixo + "    " , meuNoh->right );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != NULL )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.chave << "," << meuNoh->elemento.nomeLivro << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->left, meuNoh->right==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->right );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != NULL )
    {
        std::cout << "(" << this->raiz->elemento.chave << "," << this->raiz->elemento.nomeLivro << ")" << std::endl;
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
    string local;
    int quantidade;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe chave, nome do livro, localização, quantidade disponível
                    std::cin >> umDado.chave;
                    std::cin >> umDado.nomeLivro;
                    std::cin >> umDado.localizacao;
                    cin >> umDado.quantidadeDisponivel;
                    arvore.insere(umDado);
                    break;
                case 'r': // Remover recursivamente
                    cin >> chave;
                    arvore.removeRec(chave);
                    break;
                case 'b': // Buscar
                    cout << "inserindo";
                    cin >> chave; // ler a chave
                    umDado = arvore.busca(chave); // escrever o nome do livro
                    cout << "Elemento buscado: " << umDado.nomeLivro << endl;
                    break;
                case 'l': // Levantamento por local
                    cin >> local; // ler o local
                    quantidade = arvore.levantamento(local);
                    cout << "Levantamento do local " << local << ": " << quantidade << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
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
