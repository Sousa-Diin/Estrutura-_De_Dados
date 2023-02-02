#include <iostream>
using namespace std;

class Conta
{
private:
  int numero;     // São atributos
  string nome;    // privados por
  float saldo;    // default
public:
  void inicializa(string n, float s);
  void deposita(float valor);
  void consulta();
  int saque(float valor);
  inline int getNumero(){ return numero; }
  inline string getNome(){ return nome; }
  inline float getSaldo(){ return saldo; }
