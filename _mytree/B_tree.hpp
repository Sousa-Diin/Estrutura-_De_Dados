#include<iostream>
#include<string>
using namespace std;

typedef string data;

const unsigned int MAX_CHILDREN = 5;
const unsigned int MAX_KEY = (MAX_CHILDREN - 1);
const unsigned int ORDER = MAX_KEY/2;

struct people{
    friend class page;
    string name;
    int age;
    void insert(string name, int age);

};

void people::insert(string name, int age){
    this->age = age;
    this->name = name;
}

class page {

    friend class B_tree;
    private:
        page* children[MAX_CHILDREN];
        people element[MAX_KEY];
        int count_key;
    public:
        page(people p){
            for(int i = 0; i < MAX_CHILDREN; i++){
                children[i] = NULL;
            }
            element[0] = p;
            count_key = 1;
        }

        page(){
            for(int i = 0; i < MAX_CHILDREN; i++){
                children[i] = NULL;
            }

            for(int i = 0; i < MAX_KEY; i++){
                element[i] = NULL;
            }
            count_key = 0;
        }

        void view_people(){
            cout << "Nome: " 
                 <<  element[0]->name
                 << "Idade: " 
                 <<  element[0]->age
                 << endl;
        }

};

//class B_tree{};