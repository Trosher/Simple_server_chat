#include "client.h"

int main(int argc, const char* argv[]) {
    int client;

    struct sockaddr_in server_address;
    
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        std::cerr 
            << "CLIENT ERROR: " 
            << "Sockets cannot be generated. Error code - " 
            << client 
            << "\n";
        
            return -1;
    } 

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
    
    std::cout
        << "\n=> Client socket created.";

    int ret = connect(client, 
              reinterpret_cast<const struct sockaddr*>(&server_address),
              sizeof(server_address));
    if (ret == 0) {
        std::cout 
            << "=> Connection to server "
            << inet_ntoa(server_address.sin_addr)
            << " with port number: "
            << DEFAULT_PORT
            << std::endl;
    }

    char buffer[BUFFER_SIZE];
    std::cout 
        << "Waiting for srver confirmation...\n";
    recv(client, buffer, BUFFER_SIZE, 0);
    std::cout
        << "=> Connection established.\n"
        << "Enter "
        << EXIT_SYMBOL
        << " for close the connection\n";

    while(true) {
        std::cout 
            << "Client: ";
        std::cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, BUFFER_SIZE, 0);
        if (is_client_connection_close(buffer))
            break;
        
        std::cout 
            << "Server: ";
        recv(client, buffer, BUFFER_SIZE, 0);
        std::cout
            << buffer;
        if(is_client_connection_close(buffer))
            break;
        
        std::cout 
            << std::endl;
    }
    close(ret);
    close(client);
    std::cout 
            << "\n Have a nice day!"
            << std::endl;
    
    return 0;
}

bool is_client_connection_close(const char* msg) {
    for (int i = 0; i < strlen(msg); ++i) {
        if (msg[i] == EXIT_SYMBOL) {
            return true;
        }
    }
    return false;
}