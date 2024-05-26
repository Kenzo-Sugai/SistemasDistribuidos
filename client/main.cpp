#include <iostream>
#include "Controller.cpp"
#include <cstdlib>
#include <ctime>  

void telaAdmin(){

    int escolha;

    std::cout << "<-----> Admin <----->" << std::endl;
    std::cout << "Escolha uma opção:" << std::endl;
    std::cout << "1. Visualizar Produtos" << std::endl;
    std::cout << "2. Visualizar Extrato" << std::endl;
    std::cout << "3. Sair" << std::endl;

    std::cin >> escolha;

    switch(escolha){

        case 1: break;
        case 2: break;
        case 3: return;

    }


}

void tela(Controller ctrl, std::string usuario){

    int escolha;

    while(true){

        std::cout << "<-----> Bem vindo ao E-Mazon <----->" << std::endl;
        std::cout << "USUARIO: " << usuario << std::endl;
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "1. Visualizar lista de Produtos" << std::endl;
        std::cout << "2. Visualizar Carrinho" << std::endl;
        std::cout << "3. Adicionar Produto ao Carrinho" << std::endl;
        std::cout << "4. Admin" << std::endl;
        std::cout << "5. Sair" << std::endl;

        std::cin >> escolha;

        switch(escolha){

            case 1: ctrl.visualizarProdutos(); break;
            case 2: break;
            case 3: ctrl.adicionarCarrinho(); break;
            case 4: telaAdmin(); break;
            case 5: return;
        }

    }

}

int main(){

    srand (time(NULL));

    int user_code = rand() % 10000;

    std::string usuario = "USUARIO-"+std::to_string(user_code);

    //Controller *ctrl = new Controller(usuario);
    Controller *ctrl = new Controller(usuario);

    ctrl->criarCarrinho();

    tela(*ctrl, usuario);

    delete ctrl;
}