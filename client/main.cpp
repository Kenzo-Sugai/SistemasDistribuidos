#include <iostream>
#include "Carrinho.cpp"

void tela(Carrinho carrinho){

    int escolha;

    while(true){

        std::cout << "Bem vindo ao E-Mazon" << std::endl;
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "1. Visualizar Carrinho" << std::endl;
        std::cout << "2. Adicionar Produto" << std::endl;
        std::cout << "3. Remover Produto" << std::endl;
        std::cout << "4. Sair" << std::endl;

        std::cin >> escolha;

        switch(escolha){

            case 1:
                carrinho.visualizarCarrinho();
                break;
            case 2:
                return;
                break;
            case 3:
                return;
                break;
            case 4:
                return;
                break;
        }

    }

}

int main(){

    Carrinho *carrinho = new Carrinho();

    tela(*carrinho);
}