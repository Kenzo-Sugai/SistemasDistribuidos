#include <iostream>
#include "include/nlohmann/json.hpp"
#include "Produto.cpp"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using json = nlohmann::json;

class Carrinho {

    private:

        std::string usuario;
        std::map<std::string, Produto> Produtos;
        int qntItens;

    public:

        Carrinho(std::string usuario){
            
            this->usuario = usuario;

            this->qntItens = 0;
        }

        int getQntItens(){
            return this->qntItens;
        }

        void resetCarrinho(){
            this->qntItens = 0;
        }

        std::string adicionarProduto(std::map<std::string, Produto> listaProdutos) {

            std::string id;
            int quantidade;

            std::cout << "Qual Produto gostaria de adicionar ao Carrinho?" << std::endl;
            
            while(true){
                std::cout << "Id: "; std::cin >> id;
                if(listaProdutos[id].getNome() == ""){
                    std::cout << "Produto inexistente" << std::endl;
                }
                else break;
            }

            std::cout << "Quantidade que gostaria de comprar?" << std::endl;

            int estoque = listaProdutos[id].getEstoque();

            while(true){
                std::cout << "Quantidade disponível: " << std::to_string(estoque) << std::endl;
                std::cout << "Quantidade:"; std::cin >> quantidade;

                if(quantidade > estoque || estoque == 0){
                    std::cout << "ERRO: Quantidade indisponível" << std::endl;
                    return "erro";
                }
                else break;
            }

            std::string response = 
                R"({"id":")" + id + 
                R"(","quantidade":)" + std::to_string(quantidade) +  
                R"(,"usuario":")" + this->usuario + R"("})";

            this->qntItens++;

            return response;

        }
};