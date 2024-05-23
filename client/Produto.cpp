#include <iostream>

class Produto {

    private:

        int Id;
        std::string Nome;
        int Quantidade;

    public:

        Produto(std::string Nome, int Quantidade){

            this->Nome = Nome;
            this->Quantidade = Quantidade;

        }

        std::string getName(){

            return this->Nome;

        }

        void aumentarQuantidade(int Quantidade){

            this->Quantidade += Quantidade;

        }


};