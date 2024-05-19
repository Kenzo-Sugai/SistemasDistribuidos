#include <iostream>
#include "Produto.cpp"
#include <vector>
#include <fstream>

using namespace std;

class Carrinho {

    private:


        int QuantidadeItens;
        vector<Produto> ListaDeProdutos;

    public:

        Carrinho(){
            
            QuantidadeItens = 0;
            
            ifstream cadastroProdutos("./utils/cadastroProdutos.json", std::ifstream::binary);
            string prods;
            cadastroProdutos >> prods;

            cout << prods;
        }

        void adicionarProduto(string Nome, int Quantidade) {

            

        }
};