#include <iostream>

using namespace std;

class Produto {

    private:

        int Id;
        string Nome;
        int Quantidade;

    public:

        Produto(string Nome, int Quantidade){

            this->Nome = Nome;
            this->Quantidade = Quantidade;

        }


};