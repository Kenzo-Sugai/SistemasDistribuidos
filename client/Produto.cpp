#include <iostream>
#pragma once

class Produto {

    private:

        std::string Id;
        std::string Nome;
        std::string Descricao;
        float Preco;
        int Estoque;
        int Quantidade;

    public:

        Produto() : Preco(0.0f), Estoque(0) {}
        Produto(const std::string& id, const std::string& nome, const std::string& descricao, float preco, int estoque)
        : Id(id), Nome(nome), Descricao(descricao), Preco(preco), Estoque(estoque) {}


        std::string getNome(){

            return this->Nome;

        }

        std::string getQuantidade(){

            return std::to_string(this->Quantidade);
        }

        int getEstoque(){

            return this->Estoque;
        }

        void adicionarQuantidade(int Quantidade){

            if(this->Quantidade += Quantidade < 0){
                return;
            }

            this->Quantidade += Quantidade;

        }


};