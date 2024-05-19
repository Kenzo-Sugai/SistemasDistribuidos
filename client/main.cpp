#include <iostream>
#include "Carrinho.cpp"

using namespace std;

void tela(){

    int escolha;

    while(true){

        cout << "Bem vindo ao E-Mazon" << endl;
        cout << "Escolha uma opção:" << endl;
        cout << "1. Visualizar Carrinho" << endl;
        cout << "2. Adicionar Produto" << endl;
        cout << "3. Remover Produto" << endl;
        cout << "4. Sair" << endl;

        cin >> escolha;

        switch(escolha){

            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                return;
                break;
        }

    }

}

int main(){

    Carrinho *carrinho = new Carrinho();

    tela();
}