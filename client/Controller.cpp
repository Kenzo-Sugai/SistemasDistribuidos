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

        int getQuantidadeCarrinho(){
            return carr->getQntItens();
        }

        void criarCarrinho(){

            std::string jsonUser = R"(/criarCarrinho {"usuario":")" + this->usuario + R"("})";

            const char* request = jsonUser.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(request);

            delete client;

        }

        void visualizarProdutos(){

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/produtosLista");

            json Produtos = json::parse(req);

            for (const auto& itemProduto : Produtos) {
                if(itemProduto["Estoque"] == 0) std::cout << "X---X ESGOTADO X---X" << std::endl;
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

            if(produto == "erro") return;

            produto = "/adicionarCarrinho " + produto;

            const char* produtoChar = produto.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(produtoChar);

            std::cout << req << std::endl;

            delete client;
        }

        void visualizarCarrinho(){

            std::string jsonUser = R"(/visualizarCarrinho {"usuario":")" + this->usuario + R"("})";

            const char* request = jsonUser.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(request);

            std::cout << req << std::endl;

            delete client;

        }

        void visualizarExtrato(){

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq("/visualizarExtrato");

            std::cout << req << std::endl;

            delete client;

        }

        void finalizarCompra(){

            std::string jsonUser = R"(/finalizarCompra {"usuario":")" + this->usuario + R"("})";

            const char* request = jsonUser.c_str();

            SocketClient *client = new SocketClient();
            std::string req = client->socketReq(request);

            std::cout << req << std::endl;

            carr->resetCarrinho();

            delete client;

        }





};