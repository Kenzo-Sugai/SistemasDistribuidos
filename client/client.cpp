#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "192.168.68.103"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

class SocketClient {

    private:

        char buffer[BUFFER_SIZE] = {0};
        int sock;


    public:

        SocketClient(){

            this->sock = 0;
            struct sockaddr_in server_address;

            if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                std::cerr << "Erro ao criar o socket" << std::endl;
            }

            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(SERVER_PORT);

            if (inet_pton(AF_INET, SERVER_ADDRESS, &server_address.sin_addr) <= 0) {
                std::cerr << "Endereço inválido ou não suportado" << std::endl;
            }

            if (connect(this->sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
                std::cerr << "Falha na conexão" << std::endl;
            }

        }

        char* socketReq(const char *message){

            ssize_t sent_bytes = send(this->sock, message, strlen(message), 0);
            if (sent_bytes < 0) {
                std::cerr << "Falha ao enviar a mensagem" << std::endl;
            } else {
                std::cout << "Mensagem enviada" << std::endl;
            }

            shutdown(this->sock, SHUT_WR);

            int bytes_read = read(this->sock, buffer, BUFFER_SIZE);
            if (bytes_read > 0) {
            } else if (bytes_read == 0) {
                std::cerr << "Conexão fechada pelo servidor" << std::endl;
            } else {
                std::cerr << "Falha ao ler a resposta" << std::endl;
            }

            close(this->sock);

            return buffer;
        }
};  