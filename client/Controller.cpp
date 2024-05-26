#include <iostream>
#include "Client.cpp"
#include "include/nlohmann/json.hpp"
#include "Carrinho.cpp"
#include "Produto.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using json = nlohmann::json;

class Controller {

    private:

        std::string usuario;
        std::string jsonUser;
        Carrinho *carr;

    public:

        Controller(std::string usuario){

            this->usuario = usuario;
            this->jsonUser = R"({"usuario":")" + this->usuario + R"("})";

            this->carr = new Carrinho(usuario);

            
        }

        void criarCarrinho(){

            std::string jsonUser = R"(/criarCarrinho {"usuario":")" + this->usuario + R"("})";

            const char* request = jsonUser.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(request);

            delete client;

        }

        void visualizarProdutos(){

            //std::cout << "enviando requisicao para o servidor" << std::endl;
            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/produtosLista");

            json Produtos = json::parse(req);

            for (const auto& itemProduto : Produtos) {
                std::cout << "Produto: " << itemProduto["Id"] << std::endl;
                std::cout << "Nome: " << itemProduto["Nome"] << std::endl;
                std::cout << "Descricao: " << itemProduto["Descricao"] << std::endl;
                std::cout << "Preco: " << itemProduto["Preco"] << std::endl;
                std::cout << "Estoque: " << itemProduto["Estoque"] << std::endl;
                std::cout << std::endl;
            }

            delete client;

        }

        std::map<std::string, Produto> getProdutos(){

            //std::cout << "enviando requisicao para o servidor" << std::endl;
            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/produtosLista");

            json listaProdutos = json::parse(req);

            std::map<std::string, Produto> Produtos;

            for (const auto& itemProduto : listaProdutos) {

                std::string Id = itemProduto["Id"];
                std::string Nome = itemProduto["Nome"];
                std::string Descricao = itemProduto["Descricao"];
                float Preco = itemProduto["Preco"];
                int Estoque = itemProduto["Estoque"];

                Produto prod(Id, Nome, Descricao, Preco, Estoque);

                Produtos[Id] = prod;
            }

            delete client;

            return Produtos;

        }

        void adicionarCarrinho(){

            std::map<std::string, Produto> listaProdutos = getProdutos();

            std::string produto = carr->adicionarProduto(listaProdutos);

            produto = "/adicionarCarrinho " + produto;

            const char* produtoChar = produto.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(produtoChar);

            std::cout << req <<std::endl;

            delete client;
        }

        void visualizarCarrinho(){

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/visualizarCarrinho");

            std::cout << req <<std::endl;

            delete client;

        }

        void finalizarCompra(){

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/finalizarCompra");

            delete client;
        }




};