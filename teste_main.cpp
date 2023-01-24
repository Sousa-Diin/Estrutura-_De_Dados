#include "Conta.h"
using namespace std;

void Conta::inicializa(string n, float s)
{
  nome = n;
  saldo = s;
  if (saldo < 0)
    cout << "Erro na Criação da Conta!!!" << endl;
}

void Conta::deposita(float valor)
{
  saldo = saldo + valor;
}

void Conta::consulta()
{
  cout << "Cliente: " << nome << endl;
  cout << "Saldo Atual: " << saldo << endl;
  cout << "Numero da Conta: " << numero << endl;
}

int Conta::saque(float valor)
{
  if (saldo < valor)
    return 0;
  else
  {
    saldo = saldo - valor;
    return 1;
  }
}

//E, fazendo o uso da classe Conta, no programa principal:

#include "Conta.h"

int main()
{
  Conta MinhaConta;
  Conta *OutraConta;

  MinhaConta.saldo = 10; // ERRO!!!

  MinhaConta.inicializa("Fulano", 10.25);
  OutraConta->inicializa("Beltrano", 220.00);

  MinhaConta.deposita(12.75);
  MinhaConta.consulta();
  MinhaConta.saque(15.00);
  MinhaConta.consulta();

  OutraConta->consulta();
}
