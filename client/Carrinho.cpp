#include <iostream>
//#include "../include/nlohmann/json.hpp"
#include "Produto.cpp"
#include "Client.cpp"
#include "include/nlohmann/json.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using json = nlohmann::json;

class Carrinho {

    private:

        int QuantidadeItens;
        std::vector<Produto> ListaDeProdutos;

    public:

        Carrinho(){
            
            QuantidadeItens = 0;
            //std::cout << prods;

        }

        void adicionarProduto(int ProductId, int Quantidade) {

            std::string ProdutoNome = "prods[ProductId];";

            Produto *novoProduto = new Produto(ProdutoNome, Quantidade);

            ListaDeProdutos.push_back(*novoProduto);

        }

        void removerProduto(){
            std::cout << "Produto removido" << std::endl;
        }

        void visualizarCarrinho(){
            std::cout << "enviando requisicao para o servidor" << std::endl;
            SocketClient *client = new SocketClient();

            std::string produtosJson = std::string(client->socketReq("/produtosLista"));

            std::cout << produtosJson << std::endl;

            json Doc{json::parse(produtosJson)};

            std::string nomeProduto{Doc["Prod-00001"]["Nome"]};

            Doc.at("Prod-00001");

            std::cout << "*" << std::endl;

        }
};