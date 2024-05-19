#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "192.168.0.31"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

class SocketClient {

    public:

        SocketClient(){
            
            int sock = 0;
            struct sockaddr_in server_address;
            char buffer[BUFFER_SIZE] = {0};

            // Criar o socket
            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                std::cerr << "Erro ao criar o socket" << std::endl;
                return -1;
            }

            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(SERVER_PORT);

            // Converter endereço IPv4 do texto para binário
            if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0) {
                std::cerr << "Endereço inválido ou não suportado" << std::endl;
                return -1;
            }

            // Conectar ao servidor
            if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
                std::cerr << "Falha na conexão" << std::endl;
                return -1;
            }

            const char *message = "Hello";
            ssize_t sent_bytes = send(sock, message, strlen(message), 0);
            if (sent_bytes < 0) {
                std::cerr << "Falha ao enviar a mensagem" << std::endl;
            } else {
                std::cout << "Mensagem enviada" << std::endl;
            }

            // Usar shutdown para indicar que terminou de enviar
            shutdown(sock, SHUT_WR);

            // Ler a resposta do servidor
            int bytes_read = read(sock, buffer, BUFFER_SIZE);
            if (bytes_read > 0) {
                std::cout << "Resposta do servidor: " << buffer << std::endl;
            } else if (bytes_read == 0) {
                std::cerr << "Conexão fechada pelo servidor" << std::endl;
            } else {
                std::cerr << "Falha ao ler a resposta" << std::endl;
            }

            // Fechar o socket
            close(sock);
        }
}
