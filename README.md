# Projeto de Sistemas Distribuidos - Client/Server e-Commerce

## Descrição

Um e-commerce, tipo Amazon e Mangazine Luiza com comunicação cliente e servidor. Totalmente estruturado na arquitetura em camadas boundary, control 
e entity.

## Como executar?

O projeto foi desenvolvido em duas linguagens, Java e C++. Você terá que possuir os dois compiladores para que o projeto funcione.

Para Java, é recomendado utilizar a IDEA IntelliJ, o projeto foi totalmente desenvolvido por ela e é fácil de encontrar as importações de bibliotecas etc.
Para C++, é recomendado possuir o mingw para compilar. Entratanto, acredito que possa funcionar pelo CLion. 

IMPORTANTE: Para C++ é essencial possuir uma máquina linux, pois as bibliotecas são totalmente arquitetadas para o sistema operacional. Não é possível rodar o código no windows.
Segue alguma soluções possíveis para executar o código:
  1. Utilizar WSL.
  2. Utilizar uma máquina virtual com linux
  3. Trocar as bibliotecas Socket no Client.cpp para que o windows reconheça.

## Bibliotecas externas

Para o Servidor (Java) é necessário instalar nas conmfigurações o json-simple-1.1.1.jar para que reconheça objetos json.
Para o Client (C++) já está incluido localmente no código a biblioteca nlohmann::json, que server para também reconhecer objetos json.
